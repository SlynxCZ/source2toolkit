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
 * Copyright (C) 2023-2026 Source2ZE
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

Detouring library the toolkit and its plugins hook with -- virtual, vtable and
function detours on the one engine Metamod:Source runs. By Benoist "Kenzzer"
André, shipped as part of Metamod:Source.

## CounterStrikeSharp

We've used and modified parts of CounterStrikeSharp for schema
generation (schemagen).

## SwiftlyS2

We've used SwiftlyS2 as a reference for signatures and virtual
function indexes, cross-checking our own gamedata against theirs.
