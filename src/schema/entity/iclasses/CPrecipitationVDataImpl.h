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

#ifndef _INCLUDE_CPRECIPITATIONVDATAIMPL_H
#define _INCLUDE_CPRECIPITATIONVDATAIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IPrecipitationVData.h"
#include "schema/entity/classes/CPrecipitationVData.h"
#include "CEntitySubclassVDataBaseImpl.h"

class CPrecipitationVDataImpl : public CEntitySubclassVDataBaseImpl, public IPrecipitationVData
{

public:
    explicit CPrecipitationVDataImpl(CPrecipitationVData* p) : CEntitySubclassVDataBaseImpl(p) {}

private:
    CPrecipitationVData* Real() { return static_cast<CPrecipitationVData*>(m_pReal); }

public:
    float& InnerDistance() override { return Real()->m_flInnerDistance(); }
    void InnerDistanceUpdated() override { Real()->m_flInnerDistance.NetworkStateChanged(); }
    ParticleAttachment_t& AttachType() override { return Real()->m_nAttachType(); }
    void AttachTypeUpdated() override { Real()->m_nAttachType.NetworkStateChanged(); }
    bool& BatchSameVolumeType() override { return Real()->m_bBatchSameVolumeType(); }
    void BatchSameVolumeTypeUpdated() override { Real()->m_bBatchSameVolumeType.NetworkStateChanged(); }
    int32_t& RTEnvCP() override { return Real()->m_nRTEnvCP(); }
    void RTEnvCPUpdated() override { Real()->m_nRTEnvCP.NetworkStateChanged(); }
    int32_t& RTEnvCPComponent() override { return Real()->m_nRTEnvCPComponent(); }
    void RTEnvCPComponentUpdated() override { Real()->m_nRTEnvCPComponent.NetworkStateChanged(); }
    CUtlString& Modifier() override { return Real()->m_szModifier(); }
    void ModifierUpdated() override { Real()->m_szModifier.NetworkStateChanged(); }
    int32_t& UseSnapshotFromSurfaceGraph() override { return Real()->m_nUseSnapshotFromSurfaceGraph(); }
    void UseSnapshotFromSurfaceGraphUpdated() override { Real()->m_nUseSnapshotFromSurfaceGraph.NetworkStateChanged(); }
    PrecipitationFilter_t& SnapshotFilter() override { return Real()->m_snapshotFilter(); }
    void SnapshotFilterUpdated() override { Real()->m_snapshotFilter.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPRECIPITATIONVDATAIMPL_H
