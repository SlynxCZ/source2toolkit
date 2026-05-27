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

#ifndef _INCLUDE_CSOUNDOPVARSETENTITYIMPL_H
#define _INCLUDE_CSOUNDOPVARSETENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ISoundOpvarSetEntity.h"
#include "schema/entity/classes/CSoundOpvarSetEntity.h"
#include "CBaseEntityImpl.h"

class CSoundOpvarSetEntityImpl : public CBaseEntityImpl, public ISoundOpvarSetEntity
{

public:
    explicit CSoundOpvarSetEntityImpl(CSoundOpvarSetEntity* p) : CBaseEntityImpl(p) {}

private:
    CSoundOpvarSetEntity* Real() { return static_cast<CSoundOpvarSetEntity*>(m_pReal); }

public:
    CUtlSymbolLarge& StackName() override { return Real()->m_iszStackName(); }
    void StackNameUpdated() override { Real()->m_iszStackName.NetworkStateChanged(); }
    CUtlSymbolLarge& OperatorName() override { return Real()->m_iszOperatorName(); }
    void OperatorNameUpdated() override { Real()->m_iszOperatorName.NetworkStateChanged(); }
    CUtlSymbolLarge& OpvarName() override { return Real()->m_iszOpvarName(); }
    void OpvarNameUpdated() override { Real()->m_iszOpvarName.NetworkStateChanged(); }
    int32_t& OpvarType() override { return Real()->m_nOpvarType(); }
    void OpvarTypeUpdated() override { Real()->m_nOpvarType.NetworkStateChanged(); }
    int32_t& OpvarIndex() override { return Real()->m_nOpvarIndex(); }
    void OpvarIndexUpdated() override { Real()->m_nOpvarIndex.NetworkStateChanged(); }
    float& OpvarValue() override { return Real()->m_flOpvarValue(); }
    void OpvarValueUpdated() override { Real()->m_flOpvarValue.NetworkStateChanged(); }
    CUtlSymbolLarge& OpvarValueString() override { return Real()->m_OpvarValueString(); }
    void OpvarValueStringUpdated() override { Real()->m_OpvarValueString.NetworkStateChanged(); }
    bool& SetOnSpawn() override { return Real()->m_bSetOnSpawn(); }
    void SetOnSpawnUpdated() override { Real()->m_bSetOnSpawn.NetworkStateChanged(); }
};

#endif // _INCLUDE_CSOUNDOPVARSETENTITYIMPL_H
