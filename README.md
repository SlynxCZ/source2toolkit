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
- **Sounds** – Per-player sound events, instant stop, per-player volume channels, hook & rewrite of game sounds  
- **Tracing** – Raycasts and collision queries  
- **Transmit** – Per-player entity visibility: hide players and entities, owner-following, a CheckTransmit hook  
- **GameConfig** – Signature & offset management  
- **Dynamic Libraries** – Extend functionality with external modules  
- **Crash Handler** – Breakpad minidumps, local symbolization and Discord crash reports  

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
