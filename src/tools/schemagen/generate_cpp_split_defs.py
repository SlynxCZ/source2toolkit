import os
import re

INPUT_FILE = "generated/defs.h"
OUTPUT_DIR = "../../schema/sdk"

COMMON_INCLUDES = [
    '#pragma once',
    '',
    '#include "ehandle.h"',
    '#include "schema/clientframe.h"',
    '#include "schema/entityio.h"',
    '#include "schema/netmessages.h"',
    '#include "schema/schema.h"',
    ''
]

BUILTIN_TYPES = {
    "float", "float32", "float64",
    "double",
    "int8", "int16", "int32", "int64",
    "uint8", "uint16", "uint32", "uint64",
    "bool", "char",
    "Vector", "QAngle", "Color",
    "CHandle", "CUtlString", "CUtlSymbolLarge",
    "CEntityIOOutput"
}

def ensure_dir(path):
    os.makedirs(path, exist_ok=True)


def normalize_type(type_name):
    type_name = type_name.strip()
    type_name = re.sub(r'<.*>', '', type_name)
    type_name = type_name.replace("*", "").strip()
    return type_name


def extract_types(content):
    types = {}

    # class + struct
    pattern = r'(class|struct)\s+(\w+)(?:\s*:\s*public\s+([^{]+))?\s*\{.*?\};'
    for match in re.finditer(pattern, content, re.DOTALL):
        kind = match.group(1)
        name = match.group(2)
        parents_raw = match.group(3)

        parents = []
        if parents_raw:
            parents = [p.strip().replace("public ", "") for p in parents_raw.split(",")]

        types[name] = {
            "kind": kind,
            "text": match.group(0),
            "parents": parents
        }

    # enum
    enum_pattern = r'enum\s+(class\s+)?(\w+)\s*\{.*?\};'
    for match in re.finditer(enum_pattern, content, re.DOTALL):
        name = match.group(2)

        types[name] = {
            "kind": "enum",
            "text": match.group(0),
            "parents": []
        }

    return types


def collect_dependencies(type_name, type_info, all_types):
    includes = set()

    # parents
    for parent in type_info["parents"]:
        parent = normalize_type(parent)
        if parent in all_types and parent != type_name:
            includes.add(parent)

    # SCHEMA_FIELD
    pattern = r'SCHEMA_FIELD(?:_POINTER)?\(([^,]+),'
    for match in re.finditer(pattern, type_info["text"]):
        raw_type = match.group(1)
        dep = normalize_type(raw_type)

        if dep in all_types and dep != type_name:
            includes.add(dep)

    return sorted(includes)


def write_type_file(type_name, type_info, all_types, generated):
    if type_name in generated:
        return

    file_path = os.path.join(OUTPUT_DIR, f"{type_name}.h")

    deps = collect_dependencies(type_name, type_info, all_types)

    with open(file_path, "w", encoding="utf-8") as f:

        for line in COMMON_INCLUDES:
            f.write(line + "\n")

        for dep in deps:
            f.write(f'#include "{dep}.h"\n')

        if deps:
            f.write("\n")

        f.write(type_info["text"])
        f.write("\n")

    generated.add(type_name)

    for dep in deps:
        write_type_file(dep, all_types[dep], all_types, generated)


def main():
    ensure_dir(OUTPUT_DIR)

    with open(INPUT_FILE, "r", encoding="utf-8") as f:
        content = f.read()

    all_types = extract_types(content)
    generated = set()

    for name, info in all_types.items():
        if info["kind"] == "class":
            write_type_file(name, info, all_types, generated)

    print(f"Generated {len(generated)} types into {OUTPUT_DIR}")


if __name__ == "__main__":
    main()