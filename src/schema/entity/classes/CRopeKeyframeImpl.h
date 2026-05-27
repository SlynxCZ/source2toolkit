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

#ifndef _INCLUDE_CROPEKEYFRAMEIMPL_H
#define _INCLUDE_CROPEKEYFRAMEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IRopeKeyframe.h"
#include "schema/entity/classes/CRopeKeyframe.h"
#include "CBaseModelEntityImpl.h"

class CRopeKeyframeImpl : public CBaseModelEntityImpl, public IRopeKeyframe
{

public:
    explicit CRopeKeyframeImpl(CRopeKeyframe* p) : CBaseModelEntityImpl(p) {}

private:
    CRopeKeyframe* Real() { return static_cast<CRopeKeyframe*>(m_pReal); }

public:
    uint16_t& RopeFlags() override { return Real()->m_RopeFlags(); }
    void RopeFlagsUpdated() override { Real()->m_RopeFlags.NetworkStateChanged(); }
    CUtlSymbolLarge& NextLinkName() override { return Real()->m_iNextLinkName(); }
    void NextLinkNameUpdated() override { Real()->m_iNextLinkName.NetworkStateChanged(); }
    int16_t& Slack() override { return Real()->m_Slack(); }
    void SlackUpdated() override { Real()->m_Slack.NetworkStateChanged(); }
    float& Width() override { return Real()->m_Width(); }
    void WidthUpdated() override { Real()->m_Width.NetworkStateChanged(); }
    float& TextureScale() override { return Real()->m_TextureScale(); }
    void TextureScaleUpdated() override { Real()->m_TextureScale.NetworkStateChanged(); }
    uint8_t& Segments() override { return Real()->m_nSegments(); }
    void SegmentsUpdated() override { Real()->m_nSegments.NetworkStateChanged(); }
    bool& ConstrainBetweenEndpoints() override { return Real()->m_bConstrainBetweenEndpoints(); }
    void ConstrainBetweenEndpointsUpdated() override { Real()->m_bConstrainBetweenEndpoints.NetworkStateChanged(); }
    CUtlSymbolLarge& StrRopeMaterialModel() override { return Real()->m_strRopeMaterialModel(); }
    void StrRopeMaterialModelUpdated() override { Real()->m_strRopeMaterialModel.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIMaterial2>& RopeMaterialModelIndex() override { return Real()->m_iRopeMaterialModelIndex(); }
    void RopeMaterialModelIndexUpdated() override { Real()->m_iRopeMaterialModelIndex.NetworkStateChanged(); }
    uint8_t& Subdiv() override { return Real()->m_Subdiv(); }
    void SubdivUpdated() override { Real()->m_Subdiv.NetworkStateChanged(); }
    uint8_t& ChangeCount() override { return Real()->m_nChangeCount(); }
    void ChangeCountUpdated() override { Real()->m_nChangeCount.NetworkStateChanged(); }
    int16_t& RopeLength() override { return Real()->m_RopeLength(); }
    void RopeLengthUpdated() override { Real()->m_RopeLength.NetworkStateChanged(); }
    uint8_t& LockedPoints() override { return Real()->m_fLockedPoints(); }
    void LockedPointsUpdated() override { Real()->m_fLockedPoints.NetworkStateChanged(); }
    bool& CreatedFromMapFile() override { return Real()->m_bCreatedFromMapFile(); }
    void CreatedFromMapFileUpdated() override { Real()->m_bCreatedFromMapFile.NetworkStateChanged(); }
    float& ScrollSpeed() override { return Real()->m_flScrollSpeed(); }
    void ScrollSpeedUpdated() override { Real()->m_flScrollSpeed.NetworkStateChanged(); }
    bool& StartPointValid() override { return Real()->m_bStartPointValid(); }
    void StartPointValidUpdated() override { Real()->m_bStartPointValid.NetworkStateChanged(); }
    bool& EndPointValid() override { return Real()->m_bEndPointValid(); }
    void EndPointValidUpdated() override { Real()->m_bEndPointValid.NetworkStateChanged(); }
    CHandle<CBaseEntity>& StartPoint() override { return Real()->m_hStartPoint(); }
    void StartPointUpdated() override { Real()->m_hStartPoint.NetworkStateChanged(); }
    CHandle<CBaseEntity>& EndPoint() override { return Real()->m_hEndPoint(); }
    void EndPointUpdated() override { Real()->m_hEndPoint.NetworkStateChanged(); }
};

#endif // _INCLUDE_CROPEKEYFRAMEIMPL_H
