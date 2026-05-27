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

#ifndef _INCLUDE_CPOINTWORLDTEXTIMPL_H
#define _INCLUDE_CPOINTWORLDTEXTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointWorldText.h"
#include "schema/entity/classes/CPointWorldText.h"
#include "CModelPointEntityImpl.h"

class CPointWorldTextImpl : public CModelPointEntityImpl, public IPointWorldText
{

public:
    explicit CPointWorldTextImpl(CPointWorldText* p) : CModelPointEntityImpl(p) {}

private:
    CPointWorldText* Real() { return static_cast<CPointWorldText*>(m_pReal); }

public:
    char* MessageText() override { return Real()->m_messageText(); }
    char* FontName() override { return Real()->m_FontName(); }
    char* BackgroundMaterialName() override { return Real()->m_BackgroundMaterialName(); }
    bool& Enabled() override { return Real()->m_bEnabled(); }
    void EnabledUpdated() override { Real()->m_bEnabled.NetworkStateChanged(); }
    bool& Fullbright() override { return Real()->m_bFullbright(); }
    void FullbrightUpdated() override { Real()->m_bFullbright.NetworkStateChanged(); }
    float& WorldUnitsPerPx() override { return Real()->m_flWorldUnitsPerPx(); }
    void WorldUnitsPerPxUpdated() override { Real()->m_flWorldUnitsPerPx.NetworkStateChanged(); }
    float& FontSize() override { return Real()->m_flFontSize(); }
    void FontSizeUpdated() override { Real()->m_flFontSize.NetworkStateChanged(); }
    float& DepthOffset() override { return Real()->m_flDepthOffset(); }
    void DepthOffsetUpdated() override { Real()->m_flDepthOffset.NetworkStateChanged(); }
    bool& DrawBackground() override { return Real()->m_bDrawBackground(); }
    void DrawBackgroundUpdated() override { Real()->m_bDrawBackground.NetworkStateChanged(); }
    float& BackgroundBorderWidth() override { return Real()->m_flBackgroundBorderWidth(); }
    void BackgroundBorderWidthUpdated() override { Real()->m_flBackgroundBorderWidth.NetworkStateChanged(); }
    float& BackgroundBorderHeight() override { return Real()->m_flBackgroundBorderHeight(); }
    void BackgroundBorderHeightUpdated() override { Real()->m_flBackgroundBorderHeight.NetworkStateChanged(); }
    float& BackgroundWorldToUV() override { return Real()->m_flBackgroundWorldToUV(); }
    void BackgroundWorldToUVUpdated() override { Real()->m_flBackgroundWorldToUV.NetworkStateChanged(); }
    Color& Color() override { return Real()->m_Color(); }
    void ColorUpdated() override { Real()->m_Color.NetworkStateChanged(); }
    PointWorldTextJustifyHorizontal_t& JustifyHorizontal() override { return Real()->m_nJustifyHorizontal(); }
    void JustifyHorizontalUpdated() override { Real()->m_nJustifyHorizontal.NetworkStateChanged(); }
    PointWorldTextJustifyVertical_t& JustifyVertical() override { return Real()->m_nJustifyVertical(); }
    void JustifyVerticalUpdated() override { Real()->m_nJustifyVertical.NetworkStateChanged(); }
    PointWorldTextReorientMode_t& ReorientMode() override { return Real()->m_nReorientMode(); }
    void ReorientModeUpdated() override { Real()->m_nReorientMode.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPOINTWORLDTEXTIMPL_H
