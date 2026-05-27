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

#ifndef _INCLUDE_CCHOREOCOMPONENTIMPL_H
#define _INCLUDE_CCHOREOCOMPONENTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IChoreoComponent.h"
#include "schema/entity/classes/CChoreoComponent.h"

class CChoreoComponentImpl : public virtual IChoreoComponent
{

protected:
    void* m_pReal;

public:
    explicit CChoreoComponentImpl(void* p) : m_pReal(p) {}

private:
    CChoreoComponent* Real() { return static_cast<CChoreoComponent*>(m_pReal); }

public:
    CEntityInstance*& __m_pChainEntity() override { return Real()->__m_pChainEntity(); }
    void __m_pChainEntityUpdated() override { Real()->__m_pChainEntity.NetworkStateChanged(); }
    CHandle<CBaseModelEntity>& Owner() override { return Real()->m_hOwner(); }
    void OwnerUpdated() override { Real()->m_hOwner.NetworkStateChanged(); }
    SceneEventId_t& NextSceneEventId() override { return Real()->m_nNextSceneEventId(); }
    void NextSceneEventIdUpdated() override { Real()->m_nNextSceneEventId.NetworkStateChanged(); }
    bool& UpdateLayerPriorities() override { return Real()->m_bUpdateLayerPriorities(); }
    void UpdateLayerPrioritiesUpdated() override { Real()->m_bUpdateLayerPriorities.NetworkStateChanged(); }
    float& AllowResponsesEndTime() override { return Real()->m_flAllowResponsesEndTime(); }
    void AllowResponsesEndTimeUpdated() override { Real()->m_flAllowResponsesEndTime.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCHOREOCOMPONENTIMPL_H
