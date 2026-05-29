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

#ifndef _INCLUDE_CENVSOUNDSCAPEIMPL_H
#define _INCLUDE_CENVSOUNDSCAPEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvSoundscape.h"
#include "schema/entity/classes/CEnvSoundscape.h"
#include "CBaseEntityImpl.h"

class CEnvSoundscapeImpl : public CBaseEntityImpl, public IEnvSoundscape
{

public:
    explicit CEnvSoundscapeImpl(CEnvSoundscape* p) : CBaseEntityImpl(p) {}

private:
    CEnvSoundscape* Real() { return static_cast<CEnvSoundscape*>(m_pReal); }
    CEnvSoundscape* Real() const { return static_cast<CEnvSoundscape*>(m_pReal); }

public:
    CEnvSoundscape* GetOriginal() const override { return Real(); }
    CEntityIOOutput& OnPlay() override { return Real()->m_OnPlay(); }
    void OnPlayUpdated() override { Real()->m_OnPlay.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_flRadius(); }
    void RadiusUpdated() override { Real()->m_flRadius.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundEventName() override { return Real()->m_soundEventName(); }
    void SoundEventNameUpdated() override { Real()->m_soundEventName.NetworkStateChanged(); }
    bool& OverrideWithEvent() override { return Real()->m_bOverrideWithEvent(); }
    void OverrideWithEventUpdated() override { Real()->m_bOverrideWithEvent.NetworkStateChanged(); }
    int32_t& SoundscapeIndex() override { return Real()->m_soundscapeIndex(); }
    void SoundscapeIndexUpdated() override { Real()->m_soundscapeIndex.NetworkStateChanged(); }
    int32_t& SoundscapeEntityListId() override { return Real()->m_soundscapeEntityListId(); }
    void SoundscapeEntityListIdUpdated() override { Real()->m_soundscapeEntityListId.NetworkStateChanged(); }
    CUtlSymbolLarge* PositionNames() override { return Real()->m_positionNames(); }
    CHandle<CEnvSoundscape>& ProxySoundscape() override { return Real()->m_hProxySoundscape(); }
    void ProxySoundscapeUpdated() override { Real()->m_hProxySoundscape.NetworkStateChanged(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundscapeName() override { return Real()->m_soundscapeName(); }
    void SoundscapeNameUpdated() override { Real()->m_soundscapeName.NetworkStateChanged(); }
    uint32_t& SoundEventHash() override { return Real()->m_soundEventHash(); }
    void SoundEventHashUpdated() override { Real()->m_soundEventHash.NetworkStateChanged(); }
};

inline IEnvSoundscape* CEnvSoundscape::ToInterface() { return new CEnvSoundscapeImpl(this); }
inline IEnvSoundscape* IEnvSoundscape::FromOriginal(CEnvSoundscape* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENVSOUNDSCAPEIMPL_H
