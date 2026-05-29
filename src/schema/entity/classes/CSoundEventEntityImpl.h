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

#ifndef _INCLUDE_CSOUNDEVENTENTITYIMPL_H
#define _INCLUDE_CSOUNDEVENTENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISoundEventEntity.h"
#include "schema/entity/classes/CSoundEventEntity.h"
#include "CBaseEntityImpl.h"

class CSoundEventEntityImpl : public CBaseEntityImpl, public ISoundEventEntity
{

public:
    explicit CSoundEventEntityImpl(CSoundEventEntity* p) : CBaseEntityImpl(p) {}

private:
    CSoundEventEntity* Real() { return static_cast<CSoundEventEntity*>(m_pReal); }
    CSoundEventEntity* Real() const { return static_cast<CSoundEventEntity*>(m_pReal); }

public:
    CSoundEventEntity* GetOriginal() const override { return Real(); }
    bool& StartOnSpawn() override { return Real()->m_bStartOnSpawn(); }
    void StartOnSpawnUpdated() override { Real()->m_bStartOnSpawn.NetworkStateChanged(); }
    bool& ToLocalPlayer() override { return Real()->m_bToLocalPlayer(); }
    void ToLocalPlayerUpdated() override { Real()->m_bToLocalPlayer.NetworkStateChanged(); }
    bool& StopOnNew() override { return Real()->m_bStopOnNew(); }
    void StopOnNewUpdated() override { Real()->m_bStopOnNew.NetworkStateChanged(); }
    bool& SaveRestore() override { return Real()->m_bSaveRestore(); }
    void SaveRestoreUpdated() override { Real()->m_bSaveRestore.NetworkStateChanged(); }
    bool& SavedIsPlaying() override { return Real()->m_bSavedIsPlaying(); }
    void SavedIsPlayingUpdated() override { Real()->m_bSavedIsPlaying.NetworkStateChanged(); }
    float& SavedElapsedTime() override { return Real()->m_flSavedElapsedTime(); }
    void SavedElapsedTimeUpdated() override { Real()->m_flSavedElapsedTime.NetworkStateChanged(); }
    CUtlSymbolLarge& SourceEntityName() override { return Real()->m_iszSourceEntityName(); }
    void SourceEntityNameUpdated() override { Real()->m_iszSourceEntityName.NetworkStateChanged(); }
    CUtlSymbolLarge& AttachmentName() override { return Real()->m_iszAttachmentName(); }
    void AttachmentNameUpdated() override { Real()->m_iszAttachmentName.NetworkStateChanged(); }
    ::CEntityIOOutput& OnSoundFinished() override { return Real()->m_onSoundFinished(); }
    void OnSoundFinishedUpdated() override { Real()->m_onSoundFinished.NetworkStateChanged(); }
    float& ClientCullRadius() override { return Real()->m_flClientCullRadius(); }
    void ClientCullRadiusUpdated() override { Real()->m_flClientCullRadius.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundName() override { return Real()->m_iszSoundName(); }
    void SoundNameUpdated() override { Real()->m_iszSoundName.NetworkStateChanged(); }
    CEntityHandle& Source() override { return Real()->m_hSource(); }
    void SourceUpdated() override { Real()->m_hSource.NetworkStateChanged(); }
    int32_t& EntityIndexSelection() override { return Real()->m_nEntityIndexSelection(); }
    void EntityIndexSelectionUpdated() override { Real()->m_nEntityIndexSelection.NetworkStateChanged(); }
};

inline ISoundEventEntity* CSoundEventEntity::ToInterface() { return new CSoundEventEntityImpl(this); }
inline ISoundEventEntity* ISoundEventEntity::FromOriginal(CSoundEventEntity* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSOUNDEVENTENTITYIMPL_H
