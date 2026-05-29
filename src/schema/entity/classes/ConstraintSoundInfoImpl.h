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

#ifndef _INCLUDE_CONSTRAINTSOUNDINFOIMPL_H
#define _INCLUDE_CONSTRAINTSOUNDINFOIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IConstraintSoundInfo.h"
#include "schema/entity/classes/ConstraintSoundInfo.h"

class ConstraintSoundInfoImpl : public virtual IConstraintSoundInfo
{

protected:
    void* m_pReal;

public:
    explicit ConstraintSoundInfoImpl(void* p) : m_pReal(p) {}

private:
    ConstraintSoundInfo* Real() { return static_cast<ConstraintSoundInfo*>(m_pReal); }
    ConstraintSoundInfo* Real() const { return static_cast<ConstraintSoundInfo*>(m_pReal); }

public:
    ConstraintSoundInfo* GetOriginal() const override { return Real(); }
    VelocitySampler& Sampler() override { return Real()->m_vSampler(); }
    void SamplerUpdated() override { Real()->m_vSampler.NetworkStateChanged(); }
    SimpleConstraintSoundProfile& SoundProfile() override { return Real()->m_soundProfile(); }
    void SoundProfileUpdated() override { Real()->m_soundProfile.NetworkStateChanged(); }
    Vector& ForwardAxis() override { return Real()->m_forwardAxis(); }
    void ForwardAxisUpdated() override { Real()->m_forwardAxis.NetworkStateChanged(); }
    CUtlSymbolLarge& TravelSoundFwd() override { return Real()->m_iszTravelSoundFwd(); }
    void TravelSoundFwdUpdated() override { Real()->m_iszTravelSoundFwd.NetworkStateChanged(); }
    CUtlSymbolLarge& TravelSoundBack() override { return Real()->m_iszTravelSoundBack(); }
    void TravelSoundBackUpdated() override { Real()->m_iszTravelSoundBack.NetworkStateChanged(); }
    CUtlSymbolLarge& ReversalSoundSmall() override { return Real()->m_iszReversalSoundSmall(); }
    void ReversalSoundSmallUpdated() override { Real()->m_iszReversalSoundSmall.NetworkStateChanged(); }
    CUtlSymbolLarge& ReversalSoundMedium() override { return Real()->m_iszReversalSoundMedium(); }
    void ReversalSoundMediumUpdated() override { Real()->m_iszReversalSoundMedium.NetworkStateChanged(); }
    CUtlSymbolLarge& ReversalSoundLarge() override { return Real()->m_iszReversalSoundLarge(); }
    void ReversalSoundLargeUpdated() override { Real()->m_iszReversalSoundLarge.NetworkStateChanged(); }
    bool& PlayTravelSound() override { return Real()->m_bPlayTravelSound(); }
    void PlayTravelSoundUpdated() override { Real()->m_bPlayTravelSound.NetworkStateChanged(); }
    bool& PlayReversalSound() override { return Real()->m_bPlayReversalSound(); }
    void PlayReversalSoundUpdated() override { Real()->m_bPlayReversalSound.NetworkStateChanged(); }
};

inline IConstraintSoundInfo* ConstraintSoundInfo::ToInterface() { return new ConstraintSoundInfoImpl(this); }
inline IConstraintSoundInfo* IConstraintSoundInfo::FromOriginal(ConstraintSoundInfo* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CONSTRAINTSOUNDINFOIMPL_H
