# Source2Toolkit

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)
[![Build Status](https://img.shields.io/github/actions/workflow/status/SlynxCZ/source2toolkit/build.yml?branch=main)](https://github.com/SlynxCZ/source2toolkit/actions)
[![Website](https://img.shields.io/badge/Website-source2toolkit.net-blue)](https://www.source2toolkit.net)
[![Discord](https://img.shields.io/discord/335290997317697536?color=7289da&logo=discord&logoColor=white)](https://discord.gg/CXeUtHbxzH)

**Source2Toolkit** is the ultimate scripting layer for Source 2 games built on top of Metamod:Source.  
Low-level power. High-level simplicity.

Build anything from simple plugins to advanced engine hooks with full access to Source 2 internals.

👉 **Get started quickly:** https://www.source2toolkit.net

---

## Why Source2Toolkit?

Designed for both beginners and hardcore engine hackers.

- **High-Level API** – Clean abstractions for rapid development  
- **Low-Level Access** – Full control over memory, hooks and engine internals  
- **Metamod Ready** – Built specifically for Metamod:Source  
- **Schema System** – Work with entities like native engine code  
- **Zero Overhead** – Near-native execution speed  

---

## Features

- **Commands** – Register console & chat commands  
- **Custom HUD** – Panorama layouts with per-player state and click callbacks  
- **ConVars** – Read, modify and replicate variables  
- **Entity System** – Schema-based entity access  
- **Events & GameEvents** – Pre/Post hook support with typed data  
- **Memory** – Direct memory access & manipulation  
- **Hooks** – KHook: virtual, vtable and function detours, one engine shared with Metamod  
- **Schema System** – Access SDK classes, offsets and fields  
- **Scheduler** – Timers and next-frame execution  
- **Tracing** – Raycasts and collision queries  
- **GameConfig** – Signature & offset management  
- **Dynamic Libraries** – Extend functionality with external modules  
- **Crash Handler** – Breakpad minidumps, local symbolization and Discord crash reports  

---

## Hooking

Source2Toolkit hooks with **KHook**, Metamod:Source's own detour library, on the
one engine Metamod runs for the whole server. The toolkit gets it at load like
any Metamod plugin and hands the same engine to its own plugins
(`TOOLKIT_KHOOK_INTERFACE`, filled in by `TOOLKIT_SAVEVARS()`), so every hook
-- Metamod's, the toolkit's, every plugin's -- can call through each other's
originals. Two independent engines patching the same address cannot do that.

A hook is an object holding the member function, the context and the Pre/Post
callbacks; it is attached to an instance (`Add`) or to a whole vtable
(`AddGlobal`), and taken down in its destructor:

```cpp
KHook::Virtual<ISource2Server, void, bool, bool, bool>* m_hGameFrame =
    new KHook::Virtual(&ISource2Server::GameFrame, this, nullptr, &MyPlugin::Hook_GameFrame);
m_hGameFrame->Add(g_pSource2Server);
```

Anything a signature scan finds is hookable too -- `KHook::Member` for a
function with a `this`, `KHook::Function` otherwise:

```cpp
KHook::Member<CBaseEntity, int64_t, CTakeDamageInfo*, CTakeDamageResult*>* m_hTakeDamageOld =
    new KHook::Member(this, &MyPlugin::Hook_TakeDamageOld, nullptr);
m_hTakeDamageOld->Configure(ADDR_TAKE_DAMAGE_OLD());
```

Handlers return `KHook::Return<T>` (`Ignore`, `Override`, `Supersede`, plus the
value). The toolkit's own listener callbacks return the same type -- `Action` is
an alias of `KHook::Action` -- and their timing is a plain `bool post`:
`false` runs before the original, `true` after.

---

## Custom HUD

`custom_hud_layout` entities put a panorama layout on top of the game HUD. The
layout is authored as a `.vxml` under `panorama/layout/custom_game/`, and the
server drives it per player -- CSS classes, dialog variables and whether the
player's mouse is captured are all per-player state on one shared entity.

```cpp
CCSCustomHudLayout* pLayout = CCSCustomHudLayout::Create("my_panel", "plugin_custom_hud");

pLayout->SetHasClass("dialog", "Dismissed", false, player);
pLayout->SetDialogVariableString("MyLabel", "CustomText", "Hello", player);
pLayout->SetInputCaptureEnabled(true, player);
```

Clicks arrive as a user message that only the core sees, so callbacks are
registered on the layout and routed back to whichever plugin created it. The
`id` attribute of the clicked panel is what identifies the button:

```cpp
pLayout->AddClickCallback([](CCSPlayerController* player, CCSCustomHudLayout* pLayout, const char* pszButtonId)
{
    if (!V_strcmp(pszButtonId, "dismiss_button"))
    {
        pLayout->SetHasClass("dialog", "Dismissed", true, player);
        pLayout->SetInputCaptureEnabled(false, player);
    }
});
```

Callbacks are dropped when the layout entity dies, when the level changes, or
when the plugin that registered them unloads -- a handler must not outlive the
library it lives in.

---

## Crash Handler

The core ships its own crash handler on both Linux and Windows, a port of
[AcceleratorLocal](https://github.com/FUNPLAY-pro-CS2/AcceleratorLocal) and
[AcceleratorCS2](https://github.com/Source2ZE/AcceleratorCS2) — nothing is
uploaded to Throttle, everything is processed on the server.

When the server crashes, a minidump plus a `.txt` with the map, game path,
command line and full console history is written to
`addons/source2toolkit/dumps/`. On the next start the core:

1. Detects the unprocessed crash from the previous session.
2. Re-processes the minidump and **symbolizes third-party (`addons/`) modules
   in-process** — on Linux with the bundled Breakpad, straight from the
   ELF/DWARF on disk, so no `llvm-symbolizer` or `addr2line` is needed inside a
   bare steamrt container; on Windows through DbgHelp, from the PDB next to
   the DLL. Frames resolve to `function @ file:line`.
3. Prints the crash stack with the **suspected culprit** (the first `addons/`
   frame) to the server console.
4. Sends the report to a **Discord webhook** through the Steam HTTP API, with
   the crash `.txt` attached.

```
Server crashed: SIGSEGV /SEGV_MAPERR @ 0x67

#0 some_plugin.stx + 0x1dcc0 (CBadClass::DoStuff() @ badclass.cpp:39)
#1 some_plugin.stx + 0x1db86 (some_command_callback(CCommandContext const&, CCommand const&) @ commands.cpp:56)
#2 libtier0.so + 0x15f682
#3 libengine2.so + 0x3ecb4e

Suspected culprit: some_plugin.stx -> CBadClass::DoStuff() @ badclass.cpp:39
```

Configured in `addons/source2toolkit/configs/core.json`:

```json
"CrashHandlerEnabled": true,
"CrashDiscordWebhook": ""
```

Leave the webhook empty to keep the dumps local only.

- **Crash-loop protection:** if the server crashes twice in a row without ever
  finishing startup, the pending dump is left unprocessed so the reporting
  itself can never keep the server down.
- **Symbols:** plugins you want fully symbolized must be deployed with debug
  info — on Linux built with `-g` / RelWithDebInfo and not stripped, on
  Windows with the `.pdb` deployed next to the `.dll` / `.stx`. Without them
  the report falls back to symtab function names (Linux), and for stripped
  binaries to `module + offset`.
- **Windows:** the handler catches access violations, illegal instructions,
  stack overflows, heap corruption and `Sys_Error` through a vectored
  exception handler ahead of Valve's own, exactly like AcceleratorCS2. Any
  .NET runtime in the process (CounterStrikeSharp) needs the server started
  with `-DoNotPreloadDLLs`, or its managed binaries trip the handler at boot.
- Reports are queued until the Steam API activates, then sent — a report
  generated at boot is never lost.
- Do not run Accelerator or AcceleratorLocal next to the toolkit; two
  exception handlers fight over the same signals.

---

## Supported Games

- **Counter-Strike 2**

---

## Quick Start

👉 Full documentation: https://www.source2toolkit.net

### Prerequisites

- CMake 3.18+
- C++20 compatible compiler  
- Installed Metamod:Source  

---

## Building Source2Toolkit

```bash
git clone --recurse-submodules https://github.com/SlynxCZ/source2toolkit.git
cd source2toolkit

docker compose -f docker/docker-compose.yml up
```

## Documentation

- Docs: https://www.source2toolkit.net  
- Getting Started: https://www.source2toolkit.net/docs
- API Reference: https://www.source2toolkit.net/docs

---

## License

This project is licensed under the GNU General Public License v3.0, with a
linking exception for Valve's engines and games and a dual-licensing exception
for derivative works. See [LICENSE_INFO.txt](LICENSE_INFO.txt) for the terms
and [LICENSE](LICENSE) for the full GPLv3 text.

---

<div align="center">
  <strong>Everything you need to build Source2Toolkit plugins. Nothing more.</strong>
</div>