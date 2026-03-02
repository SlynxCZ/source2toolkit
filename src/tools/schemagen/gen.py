import json
import os
from datetime import datetime

INPUT_FILE = "mmdump.json"

OUTPUT_ROOT = "../../schema"
CLASSES_DIR = os.path.join(OUTPUT_ROOT, "classes")
ENUMS_DIR = os.path.join(OUTPUT_ROOT, "enums")
STRUCTS_DIR = os.path.join(OUTPUT_ROOT, "structs")

DATE = datetime.now().strftime("%d.%m.%Y")

def ensure_dirs():
    os.makedirs(CLASSES_DIR, exist_ok=True)
    os.makedirs(ENUMS_DIR, exist_ok=True)
    os.makedirs(STRUCTS_DIR, exist_ok=True)


def fix_type(t: str) -> str:
    mapping = {
        "int8": "int8_t",
        "uint8": "uint8_t",
        "int16": "int16_t",
        "uint16": "uint16_t",
        "int32": "int",
        "uint32": "uint32_t",
        "int64": "int64_t",
        "uint64": "uint64_t",
        "float32": "float",
        "float64": "double",
        "bool": "bool",
        "char": "char",
        "CUtlString": "std::string",
    }
    return mapping.get(t, t)


def is_struct(defn):
    traits = defn.get("traits", {})
    flags = traits.get("flags", [])
    return "has_virtual_members" not in flags


def get_base(defn, defs):
    baseclasses = defn.get("baseclasses", [])
    if not baseclasses:
        return ""
    ref = baseclasses[0]["ref_idx"]
    return defs[ref]["name"]

def parse_type(subtype, defs):
    t = subtype.get("type")

    if t == "ref":
        ref = subtype["ref_idx"]
        return defs[ref]["name"]

    if t == "ptr":
        return parse_type(subtype["subtype"], defs) + "*"

    if t == "fixed_array":
        inner = parse_type(subtype["subtype"], defs)
        count = subtype["count"]
        return f"std::array<{inner}, {count}>"

    if t == "atomic":
        return subtype["name"]

    if t == "bitfield":
        return "uint32_t"

    return "unknown"

def generate_field(member, defs):
    name = member["name"]
    subtype = member["traits"]["subtype"]

    t = fix_type(parse_type(subtype, defs))

    # pointer
    if t.endswith("*"):
        t = t[:-1]
        return f"    SCHEMA_FIELD_POINTER({t}, {name});"

    return f"    SCHEMA_FIELD({t}, {name});"

def generate_class(defn, defs):
    name = defn["name"]
    base = get_base(defn, defs)

    code = []
    code.append("//")
    code.append(f"// Created by Michal Přikryl on {DATE}.")
    code.append("// Copyright (c) 2025 slynxcz. All rights reserved.")
    code.append("//")
    code.append("#pragma once")
    code.append('#include "schema/schema.h"')
    code.append("")

    if base:
        code.append(f"class {name} : public {base}")
    else:
        code.append(f"class {name}")

    code.append("{")
    code.append("public:")
    code.append(f"    DECLARE_SCHEMA_CLASS({name})")
    code.append("")

    members = defn.get("traits", {}).get("members", [])
    for m in members:
        try:
            code.append(generate_field(m, defs))
        except Exception:
            # fallback if parsing fails
            code.append(f"    // failed to parse field: {m.get('name')}")

    code.append("};")

    return "\n".join(code)

def generate_enum(defn):
    name = defn["name"]

    code = []
    code.append("//")
    code.append(f"// Generated on {DATE}")
    code.append("//")
    code.append("#pragma once")
    code.append("")
    code.append(f"enum {name}")
    code.append("{")

    for field in defn["traits"]["fields"]:
        code.append(f"    {field['name']} = {field['value']},")

    code.append("};")

    return "\n".join(code)

def save(path, code):
    with open(path, "w", encoding="utf-8") as f:
        f.write(code)

def main():
    ensure_dirs()

    with open(INPUT_FILE, "r", encoding="utf-8") as f:
        data = json.load(f)

    defs = data["defs"]

    for defn in defs:
        t = defn.get("type")
        name = defn.get("name")

        if not name:
            continue

        # CLASS
        if t == "class":
            members = defn.get("traits", {}).get("members", [])

            # skip empty
            if not members:
                continue

            code = generate_class(defn, defs)

            if is_struct(defn):
                out = os.path.join(STRUCTS_DIR, f"{name}.h")
            else:
                out = os.path.join(CLASSES_DIR, f"{name}.h")

            save(out, code)

        # ENUM
        elif t == "enum":
            code = generate_enum(defn)
            out = os.path.join(ENUMS_DIR, f"{name}.h")
            save(out, code)

    print("Schema generation done.")


if __name__ == "__main__":
    main()