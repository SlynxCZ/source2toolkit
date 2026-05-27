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

#ifndef _INCLUDE_CPOINTCLIENTUIWORLDPANELIMPL_H
#define _INCLUDE_CPOINTCLIENTUIWORLDPANELIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointClientUIWorldPanel.h"
#include "schema/entity/classes/CPointClientUIWorldPanel.h"
#include "CBaseClientUIEntityImpl.h"

class CPointClientUIWorldPanelImpl : public CBaseClientUIEntityImpl, public IPointClientUIWorldPanel
{

public:
    explicit CPointClientUIWorldPanelImpl(CPointClientUIWorldPanel* p) : CBaseClientUIEntityImpl(p) {}

private:
    CPointClientUIWorldPanel* Real() { return static_cast<CPointClientUIWorldPanel*>(m_pReal); }

public:
    bool& IgnoreInput() override { return Real()->m_bIgnoreInput(); }
    void IgnoreInputUpdated() override { Real()->m_bIgnoreInput.NetworkStateChanged(); }
    bool& Lit() override { return Real()->m_bLit(); }
    void LitUpdated() override { Real()->m_bLit.NetworkStateChanged(); }
    bool& FollowPlayerAcrossTeleport() override { return Real()->m_bFollowPlayerAcrossTeleport(); }
    void FollowPlayerAcrossTeleportUpdated() override { Real()->m_bFollowPlayerAcrossTeleport.NetworkStateChanged(); }
    float& Width() override { return Real()->m_flWidth(); }
    void WidthUpdated() override { Real()->m_flWidth.NetworkStateChanged(); }
    float& Height() override { return Real()->m_flHeight(); }
    void HeightUpdated() override { Real()->m_flHeight.NetworkStateChanged(); }
    float& DPI() override { return Real()->m_flDPI(); }
    void DPIUpdated() override { Real()->m_flDPI.NetworkStateChanged(); }
    float& InteractDistance() override { return Real()->m_flInteractDistance(); }
    void InteractDistanceUpdated() override { Real()->m_flInteractDistance.NetworkStateChanged(); }
    float& DepthOffset() override { return Real()->m_flDepthOffset(); }
    void DepthOffsetUpdated() override { Real()->m_flDepthOffset.NetworkStateChanged(); }
    uint32_t& OwnerContext() override { return Real()->m_unOwnerContext(); }
    void OwnerContextUpdated() override { Real()->m_unOwnerContext.NetworkStateChanged(); }
    uint32_t& HorizontalAlign() override { return Real()->m_unHorizontalAlign(); }
    void HorizontalAlignUpdated() override { Real()->m_unHorizontalAlign.NetworkStateChanged(); }
    uint32_t& VerticalAlign() override { return Real()->m_unVerticalAlign(); }
    void VerticalAlignUpdated() override { Real()->m_unVerticalAlign.NetworkStateChanged(); }
    uint32_t& Orientation() override { return Real()->m_unOrientation(); }
    void OrientationUpdated() override { Real()->m_unOrientation.NetworkStateChanged(); }
    bool& AllowInteractionFromAllSceneWorlds() override { return Real()->m_bAllowInteractionFromAllSceneWorlds(); }
    void AllowInteractionFromAllSceneWorldsUpdated() override { Real()->m_bAllowInteractionFromAllSceneWorlds.NetworkStateChanged(); }
    CUtlVector<CUtlSymbolLarge>& CSSClasses() override { return Real()->m_vecCSSClasses(); }
    void CSSClassesUpdated() override { Real()->m_vecCSSClasses.NetworkStateChanged(); }
    bool& Opaque() override { return Real()->m_bOpaque(); }
    void OpaqueUpdated() override { Real()->m_bOpaque.NetworkStateChanged(); }
    bool& NoDepth() override { return Real()->m_bNoDepth(); }
    void NoDepthUpdated() override { Real()->m_bNoDepth.NetworkStateChanged(); }
    bool& VisibleWhenParentNoDraw() override { return Real()->m_bVisibleWhenParentNoDraw(); }
    void VisibleWhenParentNoDrawUpdated() override { Real()->m_bVisibleWhenParentNoDraw.NetworkStateChanged(); }
    bool& RenderBackface() override { return Real()->m_bRenderBackface(); }
    void RenderBackfaceUpdated() override { Real()->m_bRenderBackface.NetworkStateChanged(); }
    bool& UseOffScreenIndicator() override { return Real()->m_bUseOffScreenIndicator(); }
    void UseOffScreenIndicatorUpdated() override { Real()->m_bUseOffScreenIndicator.NetworkStateChanged(); }
    bool& ExcludeFromSaveGames() override { return Real()->m_bExcludeFromSaveGames(); }
    void ExcludeFromSaveGamesUpdated() override { Real()->m_bExcludeFromSaveGames.NetworkStateChanged(); }
    bool& Grabbable() override { return Real()->m_bGrabbable(); }
    void GrabbableUpdated() override { Real()->m_bGrabbable.NetworkStateChanged(); }
    bool& OnlyRenderToTexture() override { return Real()->m_bOnlyRenderToTexture(); }
    void OnlyRenderToTextureUpdated() override { Real()->m_bOnlyRenderToTexture.NetworkStateChanged(); }
    bool& DisableMipGen() override { return Real()->m_bDisableMipGen(); }
    void DisableMipGenUpdated() override { Real()->m_bDisableMipGen.NetworkStateChanged(); }
    int32_t& ExplicitImageLayout() override { return Real()->m_nExplicitImageLayout(); }
    void ExplicitImageLayoutUpdated() override { Real()->m_nExplicitImageLayout.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPOINTCLIENTUIWORLDPANELIMPL_H
