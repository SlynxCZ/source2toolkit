# Acknowledgements

## CS2Fixes

We've cherrypicked certain reverse-engineered implementations and
adapted parts of the codebase (including custom cherry-picks and
adjustments for our use case). CS2Fixes is and will always be a great
repository for reverse engineering work in CS2.

``` cpp
/**
 * =============================================================================
 * CS2Fixes
 * Copyright (C) 2023-2025 Source2ZE
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 */
```

## EntityIO

We've implemented EntityIO support based on publicly available research
and custom cherry-picked implementations, adapting them to fit our
architecture and use cases.

## Metamod:Source

We've taken inspiration from Metamod:Source for the plugin manager
system, interface sharing, and GameDLL communication model.

## HL2SDK

HL2SDK is a repository maintained by AlliedModders. We've used it as a
reference for engine structures, interfaces, and general Source/Source2
interoperability concepts.

## Nlohmann/json

JSON library used on the native side.

## KHook

Detouring library used for centralized hooking. KHook is a spiritual
successor to SourceHook and is built on top of SafetyHook.

## CounterStrikeSharp

We've used and modified parts of CounterStrikeSharp for schema
generation (schemagen).
