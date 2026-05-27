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

#ifndef _INCLUDE_CNAVHULLVDATAIMPL_H
#define _INCLUDE_CNAVHULLVDATAIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/INavHullVData.h"
#include "schema/entity/classes/CNavHullVData.h"

class CNavHullVDataImpl : public virtual INavHullVData
{

protected:
    void* m_pReal;

public:
    explicit CNavHullVDataImpl(void* p) : m_pReal(p) {}

private:
    CNavHullVData* Real() { return static_cast<CNavHullVData*>(m_pReal); }

public:
    bool& AgentEnabled() override { return Real()->m_bAgentEnabled(); }
    void AgentEnabledUpdated() override { Real()->m_bAgentEnabled.NetworkStateChanged(); }
    float& AgentRadius() override { return Real()->m_agentRadius(); }
    void AgentRadiusUpdated() override { Real()->m_agentRadius.NetworkStateChanged(); }
    float& AgentHeight() override { return Real()->m_agentHeight(); }
    void AgentHeightUpdated() override { Real()->m_agentHeight.NetworkStateChanged(); }
    bool& AgentShortHeightEnabled() override { return Real()->m_agentShortHeightEnabled(); }
    void AgentShortHeightEnabledUpdated() override { Real()->m_agentShortHeightEnabled.NetworkStateChanged(); }
    float& AgentShortHeight() override { return Real()->m_agentShortHeight(); }
    void AgentShortHeightUpdated() override { Real()->m_agentShortHeight.NetworkStateChanged(); }
    bool& AgentCrawlEnabled() override { return Real()->m_agentCrawlEnabled(); }
    void AgentCrawlEnabledUpdated() override { Real()->m_agentCrawlEnabled.NetworkStateChanged(); }
    float& AgentCrawlHeight() override { return Real()->m_agentCrawlHeight(); }
    void AgentCrawlHeightUpdated() override { Real()->m_agentCrawlHeight.NetworkStateChanged(); }
    float& AgentMaxClimb() override { return Real()->m_agentMaxClimb(); }
    void AgentMaxClimbUpdated() override { Real()->m_agentMaxClimb.NetworkStateChanged(); }
    int32_t& AgentMaxSlope() override { return Real()->m_agentMaxSlope(); }
    void AgentMaxSlopeUpdated() override { Real()->m_agentMaxSlope.NetworkStateChanged(); }
    float& AgentMaxJumpDownDist() override { return Real()->m_agentMaxJumpDownDist(); }
    void AgentMaxJumpDownDistUpdated() override { Real()->m_agentMaxJumpDownDist.NetworkStateChanged(); }
    float& AgentMaxJumpHorizDistBase() override { return Real()->m_agentMaxJumpHorizDistBase(); }
    void AgentMaxJumpHorizDistBaseUpdated() override { Real()->m_agentMaxJumpHorizDistBase.NetworkStateChanged(); }
    float& AgentMaxJumpUpDist() override { return Real()->m_agentMaxJumpUpDist(); }
    void AgentMaxJumpUpDistUpdated() override { Real()->m_agentMaxJumpUpDist.NetworkStateChanged(); }
    int32_t& AgentBorderErosion() override { return Real()->m_agentBorderErosion(); }
    void AgentBorderErosionUpdated() override { Real()->m_agentBorderErosion.NetworkStateChanged(); }
    bool& FlowMapGenerationEnabled() override { return Real()->m_flowMapGenerationEnabled(); }
    void FlowMapGenerationEnabledUpdated() override { Real()->m_flowMapGenerationEnabled.NetworkStateChanged(); }
    float& FlowMapNodeMaxRadius() override { return Real()->m_flowMapNodeMaxRadius(); }
    void FlowMapNodeMaxRadiusUpdated() override { Real()->m_flowMapNodeMaxRadius.NetworkStateChanged(); }
};

#endif // _INCLUDE_CNAVHULLVDATAIMPL_H
