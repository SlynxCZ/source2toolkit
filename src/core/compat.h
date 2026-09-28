/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
 * AlliedModders LLC. All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
 * AlliedModders LLC give you permission to link the code of this program
 * (as well as its derivative works) to "Counter-Strike 2," "Source 2,"
 * "Steam," and any Game MODs or server software running on software by
 * Valve Corporation. You must obey the GNU General Public License in all
 * respects for all other code used.
 *
 * Additionally, this exception applies to all derivative works unless
 * otherwise stated in LICENSE.txt.
 *
 * Authors:
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */
#pragma once

/**
 * Older revisions of the toolkit's interfaces, still served.
 *
 * An interface's name carries its revision ("IToolkitMenus002"); the C++ name
 * stays. The rule: any change to an existing interface -- a slot changed, a
 * slot appended -- bumps the revision, and the core keeps serving the old one
 * through an adapter until the next major version. A plugin built against
 * the old header then loads with a warning instead of being refused.
 *
 * To add one when bumping IToolkitX from 00N to 00N+1:
 *   1. copy the old header to src/core/compat/IToolkitX00N.h, renaming the
 *      class to IToolkitX_00N (the current header keeps the real name);
 *   2. write compat/IToolkitX00N.cpp: a class deriving from IToolkitX_00N
 *      that forwards every method to the current manager;
 *   3. list it in compat.cpp's table under "IToolkitX00N".
 * The factory (PluginApi::ToolkitFactory) does the rest.
 */
namespace compat
{
    /// The adapter serving `iface` (the full string, revision included), or
    /// null when this core keeps none for it.
    void* Find(const char* iface);
}
