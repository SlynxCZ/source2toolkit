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

#ifndef _INCLUDE_CCSWEAPONBASEGUNIMPL_H
#define _INCLUDE_CCSWEAPONBASEGUNIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSWeaponBaseGun.h"
#include "schema/entity/classes/CCSWeaponBaseGun.h"
#include "CCSWeaponBaseImpl.h"

class CCSWeaponBaseGunImpl : public CCSWeaponBaseImpl, public ICSWeaponBaseGun
{

public:
    explicit CCSWeaponBaseGunImpl(CCSWeaponBaseGun* p) : CCSWeaponBaseImpl(p) {}

private:
    CCSWeaponBaseGun* Real() { return static_cast<CCSWeaponBaseGun*>(m_pReal); }
    CCSWeaponBaseGun* Real() const { return static_cast<CCSWeaponBaseGun*>(m_pReal); }

public:
    CCSWeaponBaseGun* GetOriginal() const override { return Real(); }
    int32_t& ZoomLevel() override { return Real()->m_zoomLevel(); }
    void ZoomLevelUpdated() override { Real()->m_zoomLevel.NetworkStateChanged(); }
    int32_t& BurstShotsRemaining() override { return Real()->m_iBurstShotsRemaining(); }
    void BurstShotsRemainingUpdated() override { Real()->m_iBurstShotsRemaining.NetworkStateChanged(); }
    int32_t& SilencedModelIndex() override { return Real()->m_silencedModelIndex(); }
    void SilencedModelIndexUpdated() override { Real()->m_silencedModelIndex.NetworkStateChanged(); }
    bool& InPrecache() override { return Real()->m_inPrecache(); }
    void InPrecacheUpdated() override { Real()->m_inPrecache.NetworkStateChanged(); }
    bool& NeedsBoltAction() override { return Real()->m_bNeedsBoltAction(); }
    void NeedsBoltActionUpdated() override { Real()->m_bNeedsBoltAction.NetworkStateChanged(); }
    int32_t& RevolverCylinderIdx() override { return Real()->m_nRevolverCylinderIdx(); }
    void RevolverCylinderIdxUpdated() override { Real()->m_nRevolverCylinderIdx.NetworkStateChanged(); }
    bool& SkillReloadAvailable() override { return Real()->m_bSkillReloadAvailable(); }
    void SkillReloadAvailableUpdated() override { Real()->m_bSkillReloadAvailable.NetworkStateChanged(); }
    bool& SkillReloadLiftedReloadKey() override { return Real()->m_bSkillReloadLiftedReloadKey(); }
    void SkillReloadLiftedReloadKeyUpdated() override { Real()->m_bSkillReloadLiftedReloadKey.NetworkStateChanged(); }
    bool& SkillBoltInterruptAvailable() override { return Real()->m_bSkillBoltInterruptAvailable(); }
    void SkillBoltInterruptAvailableUpdated() override { Real()->m_bSkillBoltInterruptAvailable.NetworkStateChanged(); }
    bool& SkillBoltLiftedFireKey() override { return Real()->m_bSkillBoltLiftedFireKey(); }
    void SkillBoltLiftedFireKeyUpdated() override { Real()->m_bSkillBoltLiftedFireKey.NetworkStateChanged(); }
};

inline ICSWeaponBaseGun* CCSWeaponBaseGun::ToInterface() { return new CCSWeaponBaseGunImpl(this); }
inline ICSWeaponBaseGun* ICSWeaponBaseGun::FromOriginal(CCSWeaponBaseGun* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSWEAPONBASEGUNIMPL_H
