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

#ifndef _INCLUDE_CENVENTITYMAKERIMPL_H
#define _INCLUDE_CENVENTITYMAKERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IEnvEntityMaker.h"
#include "schema/entity/classes/CEnvEntityMaker.h"
#include "CPointEntityImpl.h"

class CEnvEntityMakerImpl : public CPointEntityImpl, public IEnvEntityMaker
{

public:
    explicit CEnvEntityMakerImpl(CEnvEntityMaker* p) : CPointEntityImpl(p) {}

private:
    CEnvEntityMaker* Real() { return static_cast<CEnvEntityMaker*>(m_pReal); }

public:
    Vector& EntityMins() override { return Real()->m_vecEntityMins(); }
    void EntityMinsUpdated() override { Real()->m_vecEntityMins.NetworkStateChanged(); }
    Vector& EntityMaxs() override { return Real()->m_vecEntityMaxs(); }
    void EntityMaxsUpdated() override { Real()->m_vecEntityMaxs.NetworkStateChanged(); }
    CHandle<CBaseEntity>& CurrentInstance() override { return Real()->m_hCurrentInstance(); }
    void CurrentInstanceUpdated() override { Real()->m_hCurrentInstance.NetworkStateChanged(); }
    CHandle<CBaseEntity>& CurrentBlocker() override { return Real()->m_hCurrentBlocker(); }
    void CurrentBlockerUpdated() override { Real()->m_hCurrentBlocker.NetworkStateChanged(); }
    Vector& BlockerOrigin() override { return Real()->m_vecBlockerOrigin(); }
    void BlockerOriginUpdated() override { Real()->m_vecBlockerOrigin.NetworkStateChanged(); }
    QAngle& PostSpawnDirection() override { return Real()->m_angPostSpawnDirection(); }
    void PostSpawnDirectionUpdated() override { Real()->m_angPostSpawnDirection.NetworkStateChanged(); }
    float& PostSpawnDirectionVariance() override { return Real()->m_flPostSpawnDirectionVariance(); }
    void PostSpawnDirectionVarianceUpdated() override { Real()->m_flPostSpawnDirectionVariance.NetworkStateChanged(); }
    float& PostSpawnSpeed() override { return Real()->m_flPostSpawnSpeed(); }
    void PostSpawnSpeedUpdated() override { Real()->m_flPostSpawnSpeed.NetworkStateChanged(); }
    bool& PostSpawnUseAngles() override { return Real()->m_bPostSpawnUseAngles(); }
    void PostSpawnUseAnglesUpdated() override { Real()->m_bPostSpawnUseAngles.NetworkStateChanged(); }
    CUtlSymbolLarge& Template() override { return Real()->m_iszTemplate(); }
    void TemplateUpdated() override { Real()->m_iszTemplate.NetworkStateChanged(); }
    CEntityIOOutput& OutputOnSpawned() override { return Real()->m_pOutputOnSpawned(); }
    void OutputOnSpawnedUpdated() override { Real()->m_pOutputOnSpawned.NetworkStateChanged(); }
    CEntityIOOutput& OutputOnFailedSpawn() override { return Real()->m_pOutputOnFailedSpawn(); }
    void OutputOnFailedSpawnUpdated() override { Real()->m_pOutputOnFailedSpawn.NetworkStateChanged(); }
};

#endif // _INCLUDE_CENVENTITYMAKERIMPL_H
