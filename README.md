# Source2Toolkit

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)
[![Build Status](https://img.shields.io/github/actions/workflow/status/SlynxCZ/source2toolkit/build.yml?branch=main)](https://github.com/SlynxCZ/source2toolkit/actions)
[![Website](https://img.shields.io/badge/Website-source2toolkit.net-blue)](https://www.source2toolkit.net)
[![Discord](https://img.shields.io/discord/335290997317697536?color=7289da&logo=discord&logoColor=white)](https://discord.gg/CXeUtHbxzH)

> **Branch: `khook`.** This is the KHook line, kept as the state of the toolkit
> before the SourceHook migration. It receives the same cleanup and fixes as
> `main`, but keeps `KHook` as the hooking library and the `Action` / `Mode`
> enums. If you want SourceHook — virtual, DVP, manual **and** inline hooks
> through the stock `SH_` macros — use `main`.

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
- **Hooks** – Inline, virtual, command and event hooks  
- **Schema System** – Access SDK classes, offsets and fields  
- **Scheduler** – Timers and next-frame execution  
- **Tracing** – Raycasts and collision queries  
- **GameConfig** – Signature & offset management  
- **Dynamic Libraries** – Extend functionality with external modules  

---

## Hooking

Source2Toolkit hooks through **KHook**, a SafetyHook-based detouring library.
A hook is an object you build from the function you want and the callbacks that
should run around it — pass `nullptr` for the side you do not need:

```cpp
m_pClientCommand = new KHook::Virtual(&IServerGameClients::ClientCommand, this,
                                      &Virtuals::Hook_ClientCommand, nullptr);

m_pClientCommand->Add(g_pSource2GameClients);
```

`AddGlobal` attaches to a whole vtable instead of one instance, which is how
the toolkit reaches classes it has no pointer to — `CServerSideClient`,
`CGameEventManager`, `CEntityDebugGameSystem`:

```cpp
m_pSendNetMessage->AddGlobal((CServerSideClientBase*)&m_pCServerSideClientVTable);
```

Functions with no vtable at all are hooked by signature with `KHook::Function`:

```cpp
m_pFilterMessage = new KHook::Function(this, &Inlines::Hook_FilterMessage, nullptr);
m_pFilterMessage->Configure(addresses::toolkitAddresses.FilterMessage.RCast<...>());
```

Handlers take the hooked object as their first parameter and return
`KHook::Return<T>`. The toolkit's own listener callbacks use its `Action` enum
(`Ignore`, `Override`, `Supersede`) and `Mode` (`Pre`, `Post`).

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