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
- **ConVars** – Read, modify and replicate variables  
- **Entity System** – Schema-based entity access  
- **Events & GameEvents** – Pre/Post hook support with typed data  
- **Memory** – Direct memory access & manipulation  
- **Hooks** – SourceHook engine: virtual, DVP, manual and inline hooks  
- **Schema System** – Access SDK classes, offsets and fields  
- **Scheduler** – Timers and next-frame execution  
- **Tracing** – Raycasts and collision queries  
- **GameConfig** – Signature & offset management  
- **Dynamic Libraries** – Extend functionality with external modules  

---

## Hooking

Source2Toolkit runs its **own SourceHook engine**, separate from the one
Metamod hands out. Every hook the core places and every hook a plugin places
land on that single instance, which is what makes `SH_CALL` and
`SH_GET_INLINEHOOK_ORIGINAL` able to see through each other's handler chains.
Two independent engines patching the same address cannot do that.

Plugins receive the engine exactly the way Metamod exposes its own — the
`TOOLKIT_EXPOSE` / `TOOLKIT_SAVEVARS` macros define and fill `g_SHPtr` and
`g_PLID` for you, so the stock `SH_` macros work with no extra setup:

```cpp
SH_DECL_HOOK3_void(IServerGameDLL, GameFrame, SH_NOATTRIB, 0, bool, bool, bool);

m_iGameFrameHookID = SH_ADD_HOOK(IServerGameDLL, GameFrame, g_pSource2Server,
                                 SH_MEMBER(this, &MyPlugin::Hook_GameFrame), true);
```

Inline hooks work on raw addresses, so anything a signature scan finds is
hookable — no vtable required:

```cpp
SH_DECL_INLINEHOOK2(FilterMessage, INetworkMessageProcessingPreFilterCustom,
                    bool, const CNetMessage*, INetChannel*);

m_iHookID = SH_ADD_INLINEHOOK(FilterMessage, pAddress,
                              SH_MEMBER(this, &MyPlugin::Hook_FilterMessage), false);
```

Handlers return `META_RES` (`MRES_IGNORED`, `MRES_HANDLED`, `MRES_OVERRIDE`,
`MRES_SUPERCEDE`) and register with `META_MODE` (`MMODE_PRE` / `MMODE_POST`,
or the `SHMODE_` aliases) — the same vocabulary as Metamod.

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

This project is licensed under the GNU General Public License v3.0.

---

<div align="center">
  <strong>Everything you need to build Source2Toolkit plugins. Nothing more.</strong>
</div>