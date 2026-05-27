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

#ifndef _INCLUDE_CFUNCTRACKTRAINIMPL_H
#define _INCLUDE_CFUNCTRACKTRAINIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IFuncTrackTrain.h"
#include "schema/entity/classes/CFuncTrackTrain.h"
#include "CBaseModelEntityImpl.h"

class CFuncTrackTrainImpl : public CBaseModelEntityImpl, public IFuncTrackTrain
{

public:
    explicit CFuncTrackTrainImpl(CFuncTrackTrain* p) : CBaseModelEntityImpl(p) {}

private:
    CFuncTrackTrain* Real() { return static_cast<CFuncTrackTrain*>(m_pReal); }

public:
    CHandle<CPathTrack>& Ppath() override { return Real()->m_ppath(); }
    void PpathUpdated() override { Real()->m_ppath.NetworkStateChanged(); }
    float& Length() override { return Real()->m_length(); }
    void LengthUpdated() override { Real()->m_length.NetworkStateChanged(); }
    Vector& PosPrev() override { return Real()->m_vPosPrev(); }
    void PosPrevUpdated() override { Real()->m_vPosPrev.NetworkStateChanged(); }
    QAngle& Prev() override { return Real()->m_angPrev(); }
    void PrevUpdated() override { Real()->m_angPrev.NetworkStateChanged(); }
    Vector& ControlMins() override { return Real()->m_controlMins(); }
    void ControlMinsUpdated() override { Real()->m_controlMins.NetworkStateChanged(); }
    Vector& ControlMaxs() override { return Real()->m_controlMaxs(); }
    void ControlMaxsUpdated() override { Real()->m_controlMaxs.NetworkStateChanged(); }
    Vector& LastBlockPos() override { return Real()->m_lastBlockPos(); }
    void LastBlockPosUpdated() override { Real()->m_lastBlockPos.NetworkStateChanged(); }
    int32_t& LastBlockTick() override { return Real()->m_lastBlockTick(); }
    void LastBlockTickUpdated() override { Real()->m_lastBlockTick.NetworkStateChanged(); }
    float& Volume() override { return Real()->m_flVolume(); }
    void VolumeUpdated() override { Real()->m_flVolume.NetworkStateChanged(); }
    float& Bank() override { return Real()->m_flBank(); }
    void BankUpdated() override { Real()->m_flBank.NetworkStateChanged(); }
    float& OldSpeed() override { return Real()->m_oldSpeed(); }
    void OldSpeedUpdated() override { Real()->m_oldSpeed.NetworkStateChanged(); }
    float& BlockDamage() override { return Real()->m_flBlockDamage(); }
    void BlockDamageUpdated() override { Real()->m_flBlockDamage.NetworkStateChanged(); }
    float& Height() override { return Real()->m_height(); }
    void HeightUpdated() override { Real()->m_height.NetworkStateChanged(); }
    float& MaxSpeed() override { return Real()->m_maxSpeed(); }
    void MaxSpeedUpdated() override { Real()->m_maxSpeed.NetworkStateChanged(); }
    float& Dir() override { return Real()->m_dir(); }
    void DirUpdated() override { Real()->m_dir.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundMove() override { return Real()->m_iszSoundMove(); }
    void SoundMoveUpdated() override { Real()->m_iszSoundMove.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundMovePing() override { return Real()->m_iszSoundMovePing(); }
    void SoundMovePingUpdated() override { Real()->m_iszSoundMovePing.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundStart() override { return Real()->m_iszSoundStart(); }
    void SoundStartUpdated() override { Real()->m_iszSoundStart.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundStop() override { return Real()->m_iszSoundStop(); }
    void SoundStopUpdated() override { Real()->m_iszSoundStop.NetworkStateChanged(); }
    CUtlSymbolLarge& StrPathTarget() override { return Real()->m_strPathTarget(); }
    void StrPathTargetUpdated() override { Real()->m_strPathTarget.NetworkStateChanged(); }
    float& MoveSoundMinDuration() override { return Real()->m_flMoveSoundMinDuration(); }
    void MoveSoundMinDurationUpdated() override { Real()->m_flMoveSoundMinDuration.NetworkStateChanged(); }
    float& MoveSoundMaxDuration() override { return Real()->m_flMoveSoundMaxDuration(); }
    void MoveSoundMaxDurationUpdated() override { Real()->m_flMoveSoundMaxDuration.NetworkStateChanged(); }
    float& NextMoveSoundTime() override { return Real()->m_flNextMoveSoundTime(); }
    void NextMoveSoundTimeUpdated() override { Real()->m_flNextMoveSoundTime.NetworkStateChanged(); }
    float& MoveSoundMinPitch() override { return Real()->m_flMoveSoundMinPitch(); }
    void MoveSoundMinPitchUpdated() override { Real()->m_flMoveSoundMinPitch.NetworkStateChanged(); }
    float& MoveSoundMaxPitch() override { return Real()->m_flMoveSoundMaxPitch(); }
    void MoveSoundMaxPitchUpdated() override { Real()->m_flMoveSoundMaxPitch.NetworkStateChanged(); }
    TrainOrientationType_t& OrientationType() override { return Real()->m_eOrientationType(); }
    void OrientationTypeUpdated() override { Real()->m_eOrientationType.NetworkStateChanged(); }
    TrainVelocityType_t& VelocityType() override { return Real()->m_eVelocityType(); }
    void VelocityTypeUpdated() override { Real()->m_eVelocityType.NetworkStateChanged(); }
    CEntityIOOutput& OnStart() override { return Real()->m_OnStart(); }
    void OnStartUpdated() override { Real()->m_OnStart.NetworkStateChanged(); }
    CEntityIOOutput& OnNext() override { return Real()->m_OnNext(); }
    void OnNextUpdated() override { Real()->m_OnNext.NetworkStateChanged(); }
    CEntityIOOutput& OnArrivedAtDestinationNode() override { return Real()->m_OnArrivedAtDestinationNode(); }
    void OnArrivedAtDestinationNodeUpdated() override { Real()->m_OnArrivedAtDestinationNode.NetworkStateChanged(); }
    bool& ManualSpeedChanges() override { return Real()->m_bManualSpeedChanges(); }
    void ManualSpeedChangesUpdated() override { Real()->m_bManualSpeedChanges.NetworkStateChanged(); }
    float& DesiredSpeed() override { return Real()->m_flDesiredSpeed(); }
    void DesiredSpeedUpdated() override { Real()->m_flDesiredSpeed.NetworkStateChanged(); }
    float& SpeedChangeTime() override { return Real()->m_flSpeedChangeTime(); }
    void SpeedChangeTimeUpdated() override { Real()->m_flSpeedChangeTime.NetworkStateChanged(); }
    float& AccelSpeed() override { return Real()->m_flAccelSpeed(); }
    void AccelSpeedUpdated() override { Real()->m_flAccelSpeed.NetworkStateChanged(); }
    float& DecelSpeed() override { return Real()->m_flDecelSpeed(); }
    void DecelSpeedUpdated() override { Real()->m_flDecelSpeed.NetworkStateChanged(); }
    bool& AccelToSpeed() override { return Real()->m_bAccelToSpeed(); }
    void AccelToSpeedUpdated() override { Real()->m_bAccelToSpeed.NetworkStateChanged(); }
    float& NextMPSoundTime() override { return Real()->m_flNextMPSoundTime(); }
    void NextMPSoundTimeUpdated() override { Real()->m_flNextMPSoundTime.NetworkStateChanged(); }
};

#endif // _INCLUDE_CFUNCTRACKTRAINIMPL_H
