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

#ifndef _INCLUDE_CAK47IMPL_H
#define _INCLUDE_CAK47IMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IAK47.h"
#include "schema/entity/classes/CAK47.h"
#include "CCSWeaponBaseGunImpl.h"

class CAK47Impl : public CCSWeaponBaseGunImpl, public IAK47
{

public:
    explicit CAK47Impl(CAK47* p) : CCSWeaponBaseGunImpl(p) {}

private:
    CAK47* Real() { return static_cast<CAK47*>(m_pReal); }
    CAK47* Real() const { return static_cast<CAK47*>(m_pReal); }

public:
    CAK47* GetOriginal() const override { return Real(); }
};

inline IAK47* CAK47::ToInterface() { return new CAK47Impl(this); }
inline IAK47* IAK47::FromOriginal(CAK47* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CAK47IMPL_H
