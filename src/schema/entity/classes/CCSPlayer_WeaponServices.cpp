/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
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
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
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
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */

#include "CBasePlayerWeapon.h"
#include "schema/entity/classes/CCSPlayer_WeaponServicesImpl.h"
#include "source2toolkit/schema/entity/classes/IBasePlayerWeapon.h"

#include "source2toolkit/utils/virtual.h"

#include "core/addresses.h"
#include "core/gameconfig.h"
#include "core/shared.h"

void CCSPlayer_WeaponServices::DropWeapon(IBasePlayerWeapon *pWeapon, Vector *pVecTarget, Vector *pVelocity)
{
    auto* raw = pWeapon ? static_cast<CBasePlayerWeapon*>(pWeapon->GetOriginal()) : nullptr;
    static int offset = shared::g_pGameConfig->GetOffset("CCSPlayer_WeaponServices_DropWeapon");
    CALL_VIRTUAL(void, offset, this, raw, pVecTarget, pVelocity);
}

void CCSPlayer_WeaponServices::SelectWeapon(IBasePlayerWeapon* pWeapon, int unk1)
{
    static int offset = shared::g_pGameConfig->GetOffset("CCSPlayer_WeaponServices_SelectWeapon");
    auto* raw = pWeapon ? static_cast<CBasePlayerWeapon*>(pWeapon->GetOriginal()) : nullptr;
    CALL_VIRTUAL(void, offset, this, raw, unk1);
}
ICSPlayer_WeaponServices* CCSPlayer_WeaponServices::ToInterface() { return new CCSPlayer_WeaponServicesImpl(this); }
ICSPlayer_WeaponServices* ICSPlayer_WeaponServices::FromRaw(CEntityInstance*) { return nullptr; }

ICSPlayer_WeaponServices* ICSPlayer_WeaponServices::FromOriginal(CCSPlayer_WeaponServices* p)
{ return CCSPlayer_WeaponServices::FromOriginal(p); }
