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

#ifndef _INCLUDE_CINFOOFFSCREENPANORAMATEXTUREIMPL_H
#define _INCLUDE_CINFOOFFSCREENPANORAMATEXTUREIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IInfoOffscreenPanoramaTexture.h"
#include "schema/entity/classes/CInfoOffscreenPanoramaTexture.h"
#include "CPointEntityImpl.h"

class CInfoOffscreenPanoramaTextureImpl : public CPointEntityImpl, public IInfoOffscreenPanoramaTexture
{

public:
    explicit CInfoOffscreenPanoramaTextureImpl(CInfoOffscreenPanoramaTexture* p) : CPointEntityImpl(p) {}

private:
    CInfoOffscreenPanoramaTexture* Real() { return static_cast<CInfoOffscreenPanoramaTexture*>(m_pReal); }
    CInfoOffscreenPanoramaTexture* Real() const { return static_cast<CInfoOffscreenPanoramaTexture*>(m_pReal); }

public:
    CInfoOffscreenPanoramaTexture* GetOriginal() const override { return Real(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    int32_t& ResolutionX() override { return Real()->m_nResolutionX(); }
    void ResolutionXUpdated() override { Real()->m_nResolutionX.NetworkStateChanged(); }
    int32_t& ResolutionY() override { return Real()->m_nResolutionY(); }
    void ResolutionYUpdated() override { Real()->m_nResolutionY.NetworkStateChanged(); }
    CUtlSymbolLarge& PanelType() override { return Real()->m_szPanelType(); }
    void PanelTypeUpdated() override { Real()->m_szPanelType.NetworkStateChanged(); }
    CUtlSymbolLarge& LayoutFileName() override { return Real()->m_szLayoutFileName(); }
    void LayoutFileNameUpdated() override { Real()->m_szLayoutFileName.NetworkStateChanged(); }
    CUtlSymbolLarge& RenderAttrName() override { return Real()->m_RenderAttrName(); }
    void RenderAttrNameUpdated() override { Real()->m_RenderAttrName.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseModelEntity>>& TargetEntities() override { return Real()->m_TargetEntities(); }
    void TargetEntitiesUpdated() override { Real()->m_TargetEntities.NetworkStateChanged(); }
    int32_t& TargetChangeCount() override { return Real()->m_nTargetChangeCount(); }
    void TargetChangeCountUpdated() override { Real()->m_nTargetChangeCount.NetworkStateChanged(); }
    CUtlVector<CUtlSymbolLarge>& SSClasses() override { return Real()->m_vecCSSClasses(); }
    void SSClassesUpdated() override { Real()->m_vecCSSClasses.NetworkStateChanged(); }
    CUtlSymbolLarge& TargetsName() override { return Real()->m_szTargetsName(); }
    void TargetsNameUpdated() override { Real()->m_szTargetsName.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseModelEntity>>& AdditionalTargetEntities() override { return Real()->m_AdditionalTargetEntities(); }
    void AdditionalTargetEntitiesUpdated() override { Real()->m_AdditionalTargetEntities.NetworkStateChanged(); }
};

inline IInfoOffscreenPanoramaTexture* CInfoOffscreenPanoramaTexture::ToInterface() { return new CInfoOffscreenPanoramaTextureImpl(this); }
inline IInfoOffscreenPanoramaTexture* IInfoOffscreenPanoramaTexture::FromOriginal(CInfoOffscreenPanoramaTexture* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CINFOOFFSCREENPANORAMATEXTUREIMPL_H
