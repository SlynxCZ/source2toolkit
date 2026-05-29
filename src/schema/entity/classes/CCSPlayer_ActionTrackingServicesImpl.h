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

#ifndef _INCLUDE_CCSPLAYER_ACTIONTRACKINGSERVICESIMPL_H
#define _INCLUDE_CCSPLAYER_ACTIONTRACKINGSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayer_ActionTrackingServices.h"
#include "schema/entity/classes/CCSPlayer_ActionTrackingServices.h"
#include "CPlayerPawnComponentImpl.h"

class CCSPlayer_ActionTrackingServicesImpl : public CPlayerPawnComponentImpl, public virtual ICSPlayer_ActionTrackingServices
{

public:
    explicit CCSPlayer_ActionTrackingServicesImpl(CCSPlayer_ActionTrackingServices* p) : CPlayerPawnComponentImpl(p) {}

private:
    CCSPlayer_ActionTrackingServices* Real() { return static_cast<CCSPlayer_ActionTrackingServices*>(m_pReal); }
    CCSPlayer_ActionTrackingServices* Real() const { return static_cast<CCSPlayer_ActionTrackingServices*>(m_pReal); }

public:
    CCSPlayer_ActionTrackingServices* GetOriginal() const override { return Real(); }
    CHandle<CBasePlayerWeapon>& LastWeaponBeforeC4AutoSwitch() override { return Real()->m_hLastWeaponBeforeC4AutoSwitch(); }
    void LastWeaponBeforeC4AutoSwitchUpdated() override { Real()->m_hLastWeaponBeforeC4AutoSwitch.NetworkStateChanged(); }
    bool& IsRescuing() override { return Real()->m_bIsRescuing(); }
    void IsRescuingUpdated() override { Real()->m_bIsRescuing.NetworkStateChanged(); }
    ::WeaponPurchaseTracker_t& WeaponPurchasesThisMatch() override { return Real()->m_weaponPurchasesThisMatch(); }
    void WeaponPurchasesThisMatchUpdated() override { Real()->m_weaponPurchasesThisMatch.NetworkStateChanged(); }
    ::WeaponPurchaseTracker_t& WeaponPurchasesThisRound() override { return Real()->m_weaponPurchasesThisRound(); }
    void WeaponPurchasesThisRoundUpdated() override { Real()->m_weaponPurchasesThisRound.NetworkStateChanged(); }
};

inline ICSPlayer_ActionTrackingServices* CCSPlayer_ActionTrackingServices::ToInterface() { return new CCSPlayer_ActionTrackingServicesImpl(this); }
inline ICSPlayer_ActionTrackingServices* ICSPlayer_ActionTrackingServices::FromRaw(CEntityInstance*) { return nullptr; }
inline ICSPlayer_ActionTrackingServices* ICSPlayer_ActionTrackingServices::FromOriginal(CCSPlayer_ActionTrackingServices* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSPLAYER_ACTIONTRACKINGSERVICESIMPL_H
