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

#ifndef _INCLUDE_CPOINTVALUEREMAPPERIMPL_H
#define _INCLUDE_CPOINTVALUEREMAPPERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointValueRemapper.h"
#include "schema/entity/classes/CPointValueRemapper.h"
#include "CBaseEntityImpl.h"

class CPointValueRemapperImpl : public CBaseEntityImpl, public IPointValueRemapper
{

public:
    explicit CPointValueRemapperImpl(CPointValueRemapper* p) : CBaseEntityImpl(p) {}

private:
    CPointValueRemapper* Real() { return static_cast<CPointValueRemapper*>(m_pReal); }

public:
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    bool& UpdateOnClient() override { return Real()->m_bUpdateOnClient(); }
    void UpdateOnClientUpdated() override { Real()->m_bUpdateOnClient.NetworkStateChanged(); }
    ValueRemapperInputType_t& InputType() override { return Real()->m_nInputType(); }
    void InputTypeUpdated() override { Real()->m_nInputType.NetworkStateChanged(); }
    CUtlSymbolLarge& RemapLineStartName() override { return Real()->m_iszRemapLineStartName(); }
    void RemapLineStartNameUpdated() override { Real()->m_iszRemapLineStartName.NetworkStateChanged(); }
    CUtlSymbolLarge& RemapLineEndName() override { return Real()->m_iszRemapLineEndName(); }
    void RemapLineEndNameUpdated() override { Real()->m_iszRemapLineEndName.NetworkStateChanged(); }
    CHandle<CBaseEntity>& RemapLineStart() override { return Real()->m_hRemapLineStart(); }
    void RemapLineStartUpdated() override { Real()->m_hRemapLineStart.NetworkStateChanged(); }
    CHandle<CBaseEntity>& RemapLineEnd() override { return Real()->m_hRemapLineEnd(); }
    void RemapLineEndUpdated() override { Real()->m_hRemapLineEnd.NetworkStateChanged(); }
    float& MaximumChangePerSecond() override { return Real()->m_flMaximumChangePerSecond(); }
    void MaximumChangePerSecondUpdated() override { Real()->m_flMaximumChangePerSecond.NetworkStateChanged(); }
    float& DisengageDistance() override { return Real()->m_flDisengageDistance(); }
    void DisengageDistanceUpdated() override { Real()->m_flDisengageDistance.NetworkStateChanged(); }
    float& EngageDistance() override { return Real()->m_flEngageDistance(); }
    void EngageDistanceUpdated() override { Real()->m_flEngageDistance.NetworkStateChanged(); }
    bool& RequiresUseKey() override { return Real()->m_bRequiresUseKey(); }
    void RequiresUseKeyUpdated() override { Real()->m_bRequiresUseKey.NetworkStateChanged(); }
    ValueRemapperOutputType_t& OutputType() override { return Real()->m_nOutputType(); }
    void OutputTypeUpdated() override { Real()->m_nOutputType.NetworkStateChanged(); }
    CUtlSymbolLarge& OutputEntityName() override { return Real()->m_iszOutputEntityName(); }
    void OutputEntityNameUpdated() override { Real()->m_iszOutputEntityName.NetworkStateChanged(); }
    CUtlSymbolLarge& OutputEntity2Name() override { return Real()->m_iszOutputEntity2Name(); }
    void OutputEntity2NameUpdated() override { Real()->m_iszOutputEntity2Name.NetworkStateChanged(); }
    CUtlSymbolLarge& OutputEntity3Name() override { return Real()->m_iszOutputEntity3Name(); }
    void OutputEntity3NameUpdated() override { Real()->m_iszOutputEntity3Name.NetworkStateChanged(); }
    CUtlSymbolLarge& OutputEntity4Name() override { return Real()->m_iszOutputEntity4Name(); }
    void OutputEntity4NameUpdated() override { Real()->m_iszOutputEntity4Name.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseEntity>>& OutputEntities() override { return Real()->m_hOutputEntities(); }
    void OutputEntitiesUpdated() override { Real()->m_hOutputEntities.NetworkStateChanged(); }
    ValueRemapperHapticsType_t& HapticsType() override { return Real()->m_nHapticsType(); }
    void HapticsTypeUpdated() override { Real()->m_nHapticsType.NetworkStateChanged(); }
    ValueRemapperMomentumType_t& MomentumType() override { return Real()->m_nMomentumType(); }
    void MomentumTypeUpdated() override { Real()->m_nMomentumType.NetworkStateChanged(); }
    float& MomentumModifier() override { return Real()->m_flMomentumModifier(); }
    void MomentumModifierUpdated() override { Real()->m_flMomentumModifier.NetworkStateChanged(); }
    float& SnapValue() override { return Real()->m_flSnapValue(); }
    void SnapValueUpdated() override { Real()->m_flSnapValue.NetworkStateChanged(); }
    float& CurrentMomentum() override { return Real()->m_flCurrentMomentum(); }
    void CurrentMomentumUpdated() override { Real()->m_flCurrentMomentum.NetworkStateChanged(); }
    ValueRemapperRatchetType_t& RatchetType() override { return Real()->m_nRatchetType(); }
    void RatchetTypeUpdated() override { Real()->m_nRatchetType.NetworkStateChanged(); }
    float& RatchetOffset() override { return Real()->m_flRatchetOffset(); }
    void RatchetOffsetUpdated() override { Real()->m_flRatchetOffset.NetworkStateChanged(); }
    float& InputOffset() override { return Real()->m_flInputOffset(); }
    void InputOffsetUpdated() override { Real()->m_flInputOffset.NetworkStateChanged(); }
    bool& Engaged() override { return Real()->m_bEngaged(); }
    void EngagedUpdated() override { Real()->m_bEngaged.NetworkStateChanged(); }
    bool& FirstUpdate() override { return Real()->m_bFirstUpdate(); }
    void FirstUpdateUpdated() override { Real()->m_bFirstUpdate.NetworkStateChanged(); }
    float& PreviousValue() override { return Real()->m_flPreviousValue(); }
    void PreviousValueUpdated() override { Real()->m_flPreviousValue.NetworkStateChanged(); }
    float& PreviousUpdateTickTime() override { return Real()->m_flPreviousUpdateTickTime(); }
    void PreviousUpdateTickTimeUpdated() override { Real()->m_flPreviousUpdateTickTime.NetworkStateChanged(); }
    Vector& PreviousTestPoint() override { return Real()->m_vecPreviousTestPoint(); }
    void PreviousTestPointUpdated() override { Real()->m_vecPreviousTestPoint.NetworkStateChanged(); }
    CHandle<CBasePlayerPawn>& UsingPlayer() override { return Real()->m_hUsingPlayer(); }
    void UsingPlayerUpdated() override { Real()->m_hUsingPlayer.NetworkStateChanged(); }
    float& CustomOutputValue() override { return Real()->m_flCustomOutputValue(); }
    void CustomOutputValueUpdated() override { Real()->m_flCustomOutputValue.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundEngage() override { return Real()->m_iszSoundEngage(); }
    void SoundEngageUpdated() override { Real()->m_iszSoundEngage.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundDisengage() override { return Real()->m_iszSoundDisengage(); }
    void SoundDisengageUpdated() override { Real()->m_iszSoundDisengage.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundReachedValueZero() override { return Real()->m_iszSoundReachedValueZero(); }
    void SoundReachedValueZeroUpdated() override { Real()->m_iszSoundReachedValueZero.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundReachedValueOne() override { return Real()->m_iszSoundReachedValueOne(); }
    void SoundReachedValueOneUpdated() override { Real()->m_iszSoundReachedValueOne.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundMovingLoop() override { return Real()->m_iszSoundMovingLoop(); }
    void SoundMovingLoopUpdated() override { Real()->m_iszSoundMovingLoop.NetworkStateChanged(); }
    CEntityIOOutput& OnReachedValueZero() override { return Real()->m_OnReachedValueZero(); }
    void OnReachedValueZeroUpdated() override { Real()->m_OnReachedValueZero.NetworkStateChanged(); }
    CEntityIOOutput& OnReachedValueOne() override { return Real()->m_OnReachedValueOne(); }
    void OnReachedValueOneUpdated() override { Real()->m_OnReachedValueOne.NetworkStateChanged(); }
    CEntityIOOutput& OnReachedValueCustom() override { return Real()->m_OnReachedValueCustom(); }
    void OnReachedValueCustomUpdated() override { Real()->m_OnReachedValueCustom.NetworkStateChanged(); }
    CEntityIOOutput& OnEngage() override { return Real()->m_OnEngage(); }
    void OnEngageUpdated() override { Real()->m_OnEngage.NetworkStateChanged(); }
    CEntityIOOutput& OnDisengage() override { return Real()->m_OnDisengage(); }
    void OnDisengageUpdated() override { Real()->m_OnDisengage.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPOINTVALUEREMAPPERIMPL_H
