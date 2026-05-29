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

#ifndef _INCLUDE_CINFOWORLDLAYERIMPL_H
#define _INCLUDE_CINFOWORLDLAYERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IInfoWorldLayer.h"
#include "schema/entity/classes/CInfoWorldLayer.h"
#include "CBaseEntityImpl.h"

class CInfoWorldLayerImpl : public CBaseEntityImpl, public IInfoWorldLayer
{

public:
    explicit CInfoWorldLayerImpl(CInfoWorldLayer* p) : CBaseEntityImpl(p) {}

private:
    CInfoWorldLayer* Real() { return static_cast<CInfoWorldLayer*>(m_pReal); }
    CInfoWorldLayer* Real() const { return static_cast<CInfoWorldLayer*>(m_pReal); }

public:
    CInfoWorldLayer* GetOriginal() const override { return Real(); }
    CEntityIOOutput& OutputOnEntitiesSpawned() override { return Real()->m_pOutputOnEntitiesSpawned(); }
    void OutputOnEntitiesSpawnedUpdated() override { Real()->m_pOutputOnEntitiesSpawned.NetworkStateChanged(); }
    CUtlSymbolLarge& WorldName() override { return Real()->m_worldName(); }
    void WorldNameUpdated() override { Real()->m_worldName.NetworkStateChanged(); }
    CUtlSymbolLarge& LayerName() override { return Real()->m_layerName(); }
    void LayerNameUpdated() override { Real()->m_layerName.NetworkStateChanged(); }
    bool& WorldLayerVisible() override { return Real()->m_bWorldLayerVisible(); }
    void WorldLayerVisibleUpdated() override { Real()->m_bWorldLayerVisible.NetworkStateChanged(); }
    bool& EntitiesSpawned() override { return Real()->m_bEntitiesSpawned(); }
    void EntitiesSpawnedUpdated() override { Real()->m_bEntitiesSpawned.NetworkStateChanged(); }
    bool& CreateAsChildSpawnGroup() override { return Real()->m_bCreateAsChildSpawnGroup(); }
    void CreateAsChildSpawnGroupUpdated() override { Real()->m_bCreateAsChildSpawnGroup.NetworkStateChanged(); }
    uint32_t& LayerSpawnGroup() override { return Real()->m_hLayerSpawnGroup(); }
    void LayerSpawnGroupUpdated() override { Real()->m_hLayerSpawnGroup.NetworkStateChanged(); }
};

inline IInfoWorldLayer* CInfoWorldLayer::ToInterface() { return new CInfoWorldLayerImpl(this); }
inline IInfoWorldLayer* IInfoWorldLayer::FromOriginal(CInfoWorldLayer* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CINFOWORLDLAYERIMPL_H
