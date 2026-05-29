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

#ifndef _INCLUDE_CAMBIENTGENERICIMPL_H
#define _INCLUDE_CAMBIENTGENERICIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IAmbientGeneric.h"
#include "schema/entity/classes/CAmbientGeneric.h"
#include "CPointEntityImpl.h"

class CAmbientGenericImpl : public CPointEntityImpl, public IAmbientGeneric
{

public:
    explicit CAmbientGenericImpl(CAmbientGeneric* p) : CPointEntityImpl(p) {}

private:
    CAmbientGeneric* Real() { return static_cast<CAmbientGeneric*>(m_pReal); }
    CAmbientGeneric* Real() const { return static_cast<CAmbientGeneric*>(m_pReal); }

public:
    CAmbientGeneric* GetOriginal() const override { return Real(); }
    float& Radius() override { return Real()->m_radius(); }
    void RadiusUpdated() override { Real()->m_radius.NetworkStateChanged(); }
    float& MaxRadius() override { return Real()->m_flMaxRadius(); }
    void MaxRadiusUpdated() override { Real()->m_flMaxRadius.NetworkStateChanged(); }
    ::soundlevel_t& SoundLevel() override { return Real()->m_iSoundLevel(); }
    void SoundLevelUpdated() override { Real()->m_iSoundLevel.NetworkStateChanged(); }
    ::dynpitchvol_t& Dpv() override { return Real()->m_dpv(); }
    void DpvUpdated() override { Real()->m_dpv.NetworkStateChanged(); }
    bool& Active() override { return Real()->m_fActive(); }
    void ActiveUpdated() override { Real()->m_fActive.NetworkStateChanged(); }
    bool& Looping() override { return Real()->m_fLooping(); }
    void LoopingUpdated() override { Real()->m_fLooping.NetworkStateChanged(); }
    CUtlSymbolLarge& Sound() override { return Real()->m_iszSound(); }
    void SoundUpdated() override { Real()->m_iszSound.NetworkStateChanged(); }
    CUtlSymbolLarge& SourceEntName() override { return Real()->m_sSourceEntName(); }
    void SourceEntNameUpdated() override { Real()->m_sSourceEntName.NetworkStateChanged(); }
    CHandle<CBaseEntity>& SoundSource() override { return Real()->m_hSoundSource(); }
    void SoundSourceUpdated() override { Real()->m_hSoundSource.NetworkStateChanged(); }
    CEntityIndex& SoundSourceEntIndex() override { return Real()->m_nSoundSourceEntIndex(); }
    void SoundSourceEntIndexUpdated() override { Real()->m_nSoundSourceEntIndex.NetworkStateChanged(); }
};

inline IAmbientGeneric* CAmbientGeneric::ToInterface() { return new CAmbientGenericImpl(this); }
inline IAmbientGeneric* IAmbientGeneric::FromOriginal(CAmbientGeneric* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CAMBIENTGENERICIMPL_H
