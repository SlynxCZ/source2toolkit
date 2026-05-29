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

#ifndef _INCLUDE_CFUNCSHATTERGLASSIMPL_H
#define _INCLUDE_CFUNCSHATTERGLASSIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IFuncShatterglass.h"
#include "schema/entity/classes/CFuncShatterglass.h"
#include "CBaseModelEntityImpl.h"

class CFuncShatterglassImpl : public CBaseModelEntityImpl, public IFuncShatterglass
{

public:
    explicit CFuncShatterglassImpl(CFuncShatterglass* p) : CBaseModelEntityImpl(p) {}

private:
    CFuncShatterglass* Real() { return static_cast<CFuncShatterglass*>(m_pReal); }
    CFuncShatterglass* Real() const { return static_cast<CFuncShatterglass*>(m_pReal); }

public:
    CFuncShatterglass* GetOriginal() const override { return Real(); }
    matrix3x4_t& MatPanelTransform() override { return Real()->m_matPanelTransform(); }
    void MatPanelTransformUpdated() override { Real()->m_matPanelTransform.NetworkStateChanged(); }
    matrix3x4_t& MatPanelTransformWsTemp() override { return Real()->m_matPanelTransformWsTemp(); }
    void MatPanelTransformWsTempUpdated() override { Real()->m_matPanelTransformWsTemp.NetworkStateChanged(); }
    CUtlVector<uint32_t>& ShatterGlassShards() override { return Real()->m_vecShatterGlassShards(); }
    void ShatterGlassShardsUpdated() override { Real()->m_vecShatterGlassShards.NetworkStateChanged(); }
    Vector2D& PanelSize() override { return Real()->m_PanelSize(); }
    void PanelSizeUpdated() override { Real()->m_PanelSize.NetworkStateChanged(); }
    float& LastShatterSoundEmitTime() override { return Real()->m_flLastShatterSoundEmitTime(); }
    void LastShatterSoundEmitTimeUpdated() override { Real()->m_flLastShatterSoundEmitTime.NetworkStateChanged(); }
    float& LastCleanupTime() override { return Real()->m_flLastCleanupTime(); }
    void LastCleanupTimeUpdated() override { Real()->m_flLastCleanupTime.NetworkStateChanged(); }
    float& InitAtTime() override { return Real()->m_flInitAtTime(); }
    void InitAtTimeUpdated() override { Real()->m_flInitAtTime.NetworkStateChanged(); }
    float& GlassThickness() override { return Real()->m_flGlassThickness(); }
    void GlassThicknessUpdated() override { Real()->m_flGlassThickness.NetworkStateChanged(); }
    float& SpawnInvulnerability() override { return Real()->m_flSpawnInvulnerability(); }
    void SpawnInvulnerabilityUpdated() override { Real()->m_flSpawnInvulnerability.NetworkStateChanged(); }
    bool& BreakSilent() override { return Real()->m_bBreakSilent(); }
    void BreakSilentUpdated() override { Real()->m_bBreakSilent.NetworkStateChanged(); }
    bool& BreakShardless() override { return Real()->m_bBreakShardless(); }
    void BreakShardlessUpdated() override { Real()->m_bBreakShardless.NetworkStateChanged(); }
    bool& Broken() override { return Real()->m_bBroken(); }
    void BrokenUpdated() override { Real()->m_bBroken.NetworkStateChanged(); }
    bool& GlassNavIgnore() override { return Real()->m_bGlassNavIgnore(); }
    void GlassNavIgnoreUpdated() override { Real()->m_bGlassNavIgnore.NetworkStateChanged(); }
    bool& GlassInFrame() override { return Real()->m_bGlassInFrame(); }
    void GlassInFrameUpdated() override { Real()->m_bGlassInFrame.NetworkStateChanged(); }
    bool& StartBroken() override { return Real()->m_bStartBroken(); }
    void StartBrokenUpdated() override { Real()->m_bStartBroken.NetworkStateChanged(); }
    uint8_t& InitialDamageType() override { return Real()->m_iInitialDamageType(); }
    void InitialDamageTypeUpdated() override { Real()->m_iInitialDamageType.NetworkStateChanged(); }
    CUtlSymbolLarge& DamagePositioningEntityName01() override { return Real()->m_szDamagePositioningEntityName01(); }
    void DamagePositioningEntityName01Updated() override { Real()->m_szDamagePositioningEntityName01.NetworkStateChanged(); }
    CUtlSymbolLarge& DamagePositioningEntityName02() override { return Real()->m_szDamagePositioningEntityName02(); }
    void DamagePositioningEntityName02Updated() override { Real()->m_szDamagePositioningEntityName02.NetworkStateChanged(); }
    CUtlSymbolLarge& DamagePositioningEntityName03() override { return Real()->m_szDamagePositioningEntityName03(); }
    void DamagePositioningEntityName03Updated() override { Real()->m_szDamagePositioningEntityName03.NetworkStateChanged(); }
    CUtlSymbolLarge& DamagePositioningEntityName04() override { return Real()->m_szDamagePositioningEntityName04(); }
    void DamagePositioningEntityName04Updated() override { Real()->m_szDamagePositioningEntityName04.NetworkStateChanged(); }
    CUtlVector<Vector>& InitialDamagePositions() override { return Real()->m_vInitialDamagePositions(); }
    void InitialDamagePositionsUpdated() override { Real()->m_vInitialDamagePositions.NetworkStateChanged(); }
    CUtlVector<Vector>& ExtraDamagePositions() override { return Real()->m_vExtraDamagePositions(); }
    void ExtraDamagePositionsUpdated() override { Real()->m_vExtraDamagePositions.NetworkStateChanged(); }
    CUtlVector<Vector4D>& InitialPanelVertices() override { return Real()->m_vInitialPanelVertices(); }
    void InitialPanelVerticesUpdated() override { Real()->m_vInitialPanelVertices.NetworkStateChanged(); }
    CEntityIOOutput& OnBroken() override { return Real()->m_OnBroken(); }
    void OnBrokenUpdated() override { Real()->m_OnBroken.NetworkStateChanged(); }
    uint8_t& SurfaceType() override { return Real()->m_iSurfaceType(); }
    void SurfaceTypeUpdated() override { Real()->m_iSurfaceType.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIMaterial2>& MaterialDamageBase() override { return Real()->m_hMaterialDamageBase(); }
    void MaterialDamageBaseUpdated() override { Real()->m_hMaterialDamageBase.NetworkStateChanged(); }
};

inline IFuncShatterglass* CFuncShatterglass::ToInterface() { return new CFuncShatterglassImpl(this); }
inline IFuncShatterglass* IFuncShatterglass::FromOriginal(CFuncShatterglass* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CFUNCSHATTERGLASSIMPL_H
