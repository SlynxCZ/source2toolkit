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

#ifndef _INCLUDE_CBASEMODELENTITYIMPL_H
#define _INCLUDE_CBASEMODELENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBaseModelEntity.h"
#include "schema/entity/classes/CBaseModelEntity.h"
#include "CBaseEntityImpl.h"

class CBaseModelEntityImpl : public CBaseEntityImpl, public IBaseModelEntity
{

public:
    explicit CBaseModelEntityImpl(CBaseModelEntity* p) : CBaseEntityImpl(p) {}

private:
    CBaseModelEntity* Real() { return static_cast<CBaseModelEntity*>(m_pReal); }

public:
    CRenderComponent*& CRenderComponent() override { return Real()->m_CRenderComponent(); }
    void CRenderComponentUpdated() override { Real()->m_CRenderComponent.NetworkStateChanged(); }
    CHitboxComponent& CHitboxComponent() override { return Real()->m_CHitboxComponent(); }
    void CHitboxComponentUpdated() override { Real()->m_CHitboxComponent.NetworkStateChanged(); }
    CChoreoComponent*& ChoreoComponent() override { return Real()->m_pChoreoComponent(); }
    void ChoreoComponentUpdated() override { Real()->m_pChoreoComponent.NetworkStateChanged(); }
    HitGroup_t& DestructiblePartInitialStateDestructed0() override { return Real()->m_nDestructiblePartInitialStateDestructed0(); }
    void DestructiblePartInitialStateDestructed0Updated() override { Real()->m_nDestructiblePartInitialStateDestructed0.NetworkStateChanged(); }
    HitGroup_t& DestructiblePartInitialStateDestructed1() override { return Real()->m_nDestructiblePartInitialStateDestructed1(); }
    void DestructiblePartInitialStateDestructed1Updated() override { Real()->m_nDestructiblePartInitialStateDestructed1.NetworkStateChanged(); }
    HitGroup_t& DestructiblePartInitialStateDestructed2() override { return Real()->m_nDestructiblePartInitialStateDestructed2(); }
    void DestructiblePartInitialStateDestructed2Updated() override { Real()->m_nDestructiblePartInitialStateDestructed2.NetworkStateChanged(); }
    HitGroup_t& DestructiblePartInitialStateDestructed3() override { return Real()->m_nDestructiblePartInitialStateDestructed3(); }
    void DestructiblePartInitialStateDestructed3Updated() override { Real()->m_nDestructiblePartInitialStateDestructed3.NetworkStateChanged(); }
    HitGroup_t& DestructiblePartInitialStateDestructed4() override { return Real()->m_nDestructiblePartInitialStateDestructed4(); }
    void DestructiblePartInitialStateDestructed4Updated() override { Real()->m_nDestructiblePartInitialStateDestructed4.NetworkStateChanged(); }
    int32_t& DestructiblePartInitialStateDestructed0_PartIndex() override { return Real()->m_nDestructiblePartInitialStateDestructed0_PartIndex(); }
    void DestructiblePartInitialStateDestructed0_PartIndexUpdated() override { Real()->m_nDestructiblePartInitialStateDestructed0_PartIndex.NetworkStateChanged(); }
    int32_t& DestructiblePartInitialStateDestructed1_PartIndex() override { return Real()->m_nDestructiblePartInitialStateDestructed1_PartIndex(); }
    void DestructiblePartInitialStateDestructed1_PartIndexUpdated() override { Real()->m_nDestructiblePartInitialStateDestructed1_PartIndex.NetworkStateChanged(); }
    int32_t& DestructiblePartInitialStateDestructed2_PartIndex() override { return Real()->m_nDestructiblePartInitialStateDestructed2_PartIndex(); }
    void DestructiblePartInitialStateDestructed2_PartIndexUpdated() override { Real()->m_nDestructiblePartInitialStateDestructed2_PartIndex.NetworkStateChanged(); }
    int32_t& DestructiblePartInitialStateDestructed3_PartIndex() override { return Real()->m_nDestructiblePartInitialStateDestructed3_PartIndex(); }
    void DestructiblePartInitialStateDestructed3_PartIndexUpdated() override { Real()->m_nDestructiblePartInitialStateDestructed3_PartIndex.NetworkStateChanged(); }
    int32_t& DestructiblePartInitialStateDestructed4_PartIndex() override { return Real()->m_nDestructiblePartInitialStateDestructed4_PartIndex(); }
    void DestructiblePartInitialStateDestructed4_PartIndexUpdated() override { Real()->m_nDestructiblePartInitialStateDestructed4_PartIndex.NetworkStateChanged(); }
    bool& DestructiblePartInitialStateDestructed0_GenerateBreakpieces() override { return Real()->m_bDestructiblePartInitialStateDestructed0_GenerateBreakpieces(); }
    void DestructiblePartInitialStateDestructed0_GenerateBreakpiecesUpdated() override { Real()->m_bDestructiblePartInitialStateDestructed0_GenerateBreakpieces.NetworkStateChanged(); }
    bool& DestructiblePartInitialStateDestructed1_GenerateBreakpieces() override { return Real()->m_bDestructiblePartInitialStateDestructed1_GenerateBreakpieces(); }
    void DestructiblePartInitialStateDestructed1_GenerateBreakpiecesUpdated() override { Real()->m_bDestructiblePartInitialStateDestructed1_GenerateBreakpieces.NetworkStateChanged(); }
    bool& DestructiblePartInitialStateDestructed2_GenerateBreakpieces() override { return Real()->m_bDestructiblePartInitialStateDestructed2_GenerateBreakpieces(); }
    void DestructiblePartInitialStateDestructed2_GenerateBreakpiecesUpdated() override { Real()->m_bDestructiblePartInitialStateDestructed2_GenerateBreakpieces.NetworkStateChanged(); }
    bool& DestructiblePartInitialStateDestructed3_GenerateBreakpieces() override { return Real()->m_bDestructiblePartInitialStateDestructed3_GenerateBreakpieces(); }
    void DestructiblePartInitialStateDestructed3_GenerateBreakpiecesUpdated() override { Real()->m_bDestructiblePartInitialStateDestructed3_GenerateBreakpieces.NetworkStateChanged(); }
    bool& DestructiblePartInitialStateDestructed4_GenerateBreakpieces() override { return Real()->m_bDestructiblePartInitialStateDestructed4_GenerateBreakpieces(); }
    void DestructiblePartInitialStateDestructed4_GenerateBreakpiecesUpdated() override { Real()->m_bDestructiblePartInitialStateDestructed4_GenerateBreakpieces.NetworkStateChanged(); }
    CDestructiblePartsComponent*& DestructiblePartsSystemComponent() override { return Real()->m_pDestructiblePartsSystemComponent(); }
    void DestructiblePartsSystemComponentUpdated() override { Real()->m_pDestructiblePartsSystemComponent.NetworkStateChanged(); }
    float& DissolveStartTime() override { return Real()->m_flDissolveStartTime(); }
    void DissolveStartTimeUpdated() override { Real()->m_flDissolveStartTime.NetworkStateChanged(); }
    CEntityIOOutput& OnIgnite() override { return Real()->m_OnIgnite(); }
    void OnIgniteUpdated() override { Real()->m_OnIgnite.NetworkStateChanged(); }
    RenderMode_t& RenderMode() override { return Real()->m_nRenderMode(); }
    void RenderModeUpdated() override { Real()->m_nRenderMode.NetworkStateChanged(); }
    RenderFx_t& RenderFX() override { return Real()->m_nRenderFX(); }
    void RenderFXUpdated() override { Real()->m_nRenderFX.NetworkStateChanged(); }
    bool& AllowFadeInView() override { return Real()->m_bAllowFadeInView(); }
    void AllowFadeInViewUpdated() override { Real()->m_bAllowFadeInView.NetworkStateChanged(); }
    Color& Render() override { return Real()->m_clrRender(); }
    void RenderUpdated() override { Real()->m_clrRender.NetworkStateChanged(); }
    CUtlVector<EntityRenderAttribute_t>& RenderAttributes() override { return Real()->m_vecRenderAttributes(); }
    void RenderAttributesUpdated() override { Real()->m_vecRenderAttributes.NetworkStateChanged(); }
    bool& RenderToCubemaps() override { return Real()->m_bRenderToCubemaps(); }
    void RenderToCubemapsUpdated() override { Real()->m_bRenderToCubemaps.NetworkStateChanged(); }
    bool& NoInterpolate() override { return Real()->m_bNoInterpolate(); }
    void NoInterpolateUpdated() override { Real()->m_bNoInterpolate.NetworkStateChanged(); }
    CCollisionProperty& Collision() override { return Real()->m_Collision(); }
    void CollisionUpdated() override { Real()->m_Collision.NetworkStateChanged(); }
    CGlowProperty& Glow() override { return Real()->m_Glow(); }
    void GlowUpdated() override { Real()->m_Glow.NetworkStateChanged(); }
    float& GlowBackfaceMult() override { return Real()->m_flGlowBackfaceMult(); }
    void GlowBackfaceMultUpdated() override { Real()->m_flGlowBackfaceMult.NetworkStateChanged(); }
    float& FadeMinDist() override { return Real()->m_fadeMinDist(); }
    void FadeMinDistUpdated() override { Real()->m_fadeMinDist.NetworkStateChanged(); }
    float& FadeMaxDist() override { return Real()->m_fadeMaxDist(); }
    void FadeMaxDistUpdated() override { Real()->m_fadeMaxDist.NetworkStateChanged(); }
    float& FadeScale() override { return Real()->m_flFadeScale(); }
    void FadeScaleUpdated() override { Real()->m_flFadeScale.NetworkStateChanged(); }
    float& ShadowStrength() override { return Real()->m_flShadowStrength(); }
    void ShadowStrengthUpdated() override { Real()->m_flShadowStrength.NetworkStateChanged(); }
    uint8_t& ObjectCulling() override { return Real()->m_nObjectCulling(); }
    void ObjectCullingUpdated() override { Real()->m_nObjectCulling.NetworkStateChanged(); }
    CNetworkViewOffsetVector& ViewOffset() override { return Real()->m_vecViewOffset(); }
    void ViewOffsetUpdated() override { Real()->m_vecViewOffset.NetworkStateChanged(); }
    uint32_t* DisabledHitGroups() override { return Real()->m_bvDisabledHitGroups(); }

    CUtlSymbolLarge GetModelName() override { return Real()->GetModelName(); }
    Vector GetEyePosition() override { return Real()->GetEyePosition(); }
    void SetModel(const char* pszModel) override { Real()->SetModel(pszModel); }
};

#endif // _INCLUDE_CBASEMODELENTITYIMPL_H
