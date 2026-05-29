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

#ifndef _INCLUDE_CPLAYER_WEAPONSERVICESIMPL_H
#define _INCLUDE_CPLAYER_WEAPONSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPlayer_WeaponServices.h"
#include "schema/entity/classes/CPlayer_WeaponServices.h"
#include "CPlayerPawnComponentImpl.h"

class CPlayer_WeaponServicesImpl : public CPlayerPawnComponentImpl, public virtual IPlayer_WeaponServices
{

public:
    explicit CPlayer_WeaponServicesImpl(CPlayer_WeaponServices* p) : CPlayerPawnComponentImpl(p) {}

private:
    CPlayer_WeaponServices* Real() { return static_cast<CPlayer_WeaponServices*>(m_pReal); }
    CPlayer_WeaponServices* Real() const { return static_cast<CPlayer_WeaponServices*>(m_pReal); }

public:
    CPlayer_WeaponServices* GetOriginal() const override { return Real(); }
    CUtlVector<CHandle<CBasePlayerWeapon>>& MyWeapons() override { return Real()->m_hMyWeapons(); }
    void MyWeaponsUpdated() override { Real()->m_hMyWeapons.NetworkStateChanged(); }
    CHandle<CBasePlayerWeapon>& ActiveWeapon() override { return Real()->m_hActiveWeapon(); }
    void ActiveWeaponUpdated() override { Real()->m_hActiveWeapon.NetworkStateChanged(); }
    CHandle<CBasePlayerWeapon>& LastWeapon() override { return Real()->m_hLastWeapon(); }
    void LastWeaponUpdated() override { Real()->m_hLastWeapon.NetworkStateChanged(); }
    uint16_t* Ammo() override { return Real()->m_iAmmo(); }
    bool& PreventWeaponPickup() override { return Real()->m_bPreventWeaponPickup(); }
    void PreventWeaponPickupUpdated() override { Real()->m_bPreventWeaponPickup.NetworkStateChanged(); }
};

inline IPlayer_WeaponServices* CPlayer_WeaponServices::ToInterface() { return new CPlayer_WeaponServicesImpl(this); }
inline IPlayer_WeaponServices* IPlayer_WeaponServices::FromRaw(CEntityInstance*) { return nullptr; }
inline IPlayer_WeaponServices* IPlayer_WeaponServices::FromOriginal(CPlayer_WeaponServices* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPLAYER_WEAPONSERVICESIMPL_H
