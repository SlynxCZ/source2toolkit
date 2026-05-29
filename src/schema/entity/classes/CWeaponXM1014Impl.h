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

#ifndef _INCLUDE_CWEAPONXM1014IMPL_H
#define _INCLUDE_CWEAPONXM1014IMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IWeaponXM1014.h"
#include "schema/entity/classes/CWeaponXM1014.h"
#include "CCSWeaponBaseShotgunImpl.h"

class CWeaponXM1014Impl : public CCSWeaponBaseShotgunImpl, public IWeaponXM1014
{

public:
    explicit CWeaponXM1014Impl(CWeaponXM1014* p) : CCSWeaponBaseShotgunImpl(p) {}

private:
    CWeaponXM1014* Real() { return static_cast<CWeaponXM1014*>(m_pReal); }
    CWeaponXM1014* Real() const { return static_cast<CWeaponXM1014*>(m_pReal); }

public:
    CWeaponXM1014* GetOriginal() const override { return Real(); }
};

inline IWeaponXM1014* CWeaponXM1014::ToInterface() { return new CWeaponXM1014Impl(this); }
inline IWeaponXM1014* IWeaponXM1014::FromOriginal(CWeaponXM1014* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CWEAPONXM1014IMPL_H
