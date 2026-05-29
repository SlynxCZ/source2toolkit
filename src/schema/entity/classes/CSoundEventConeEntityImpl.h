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

#ifndef _INCLUDE_CSOUNDEVENTCONEENTITYIMPL_H
#define _INCLUDE_CSOUNDEVENTCONEENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISoundEventConeEntity.h"
#include "schema/entity/classes/CSoundEventConeEntity.h"
#include "CSoundEventEntityImpl.h"

class CSoundEventConeEntityImpl : public CSoundEventEntityImpl, public ISoundEventConeEntity
{

public:
    explicit CSoundEventConeEntityImpl(CSoundEventConeEntity* p) : CSoundEventEntityImpl(p) {}

private:
    CSoundEventConeEntity* Real() { return static_cast<CSoundEventConeEntity*>(m_pReal); }
    CSoundEventConeEntity* Real() const { return static_cast<CSoundEventConeEntity*>(m_pReal); }

public:
    CSoundEventConeEntity* GetOriginal() const override { return Real(); }
    float& EmitterAngle() override { return Real()->m_flEmitterAngle(); }
    void EmitterAngleUpdated() override { Real()->m_flEmitterAngle.NetworkStateChanged(); }
    float& SweetSpotAngle() override { return Real()->m_flSweetSpotAngle(); }
    void SweetSpotAngleUpdated() override { Real()->m_flSweetSpotAngle.NetworkStateChanged(); }
    float& AttenMin() override { return Real()->m_flAttenMin(); }
    void AttenMinUpdated() override { Real()->m_flAttenMin.NetworkStateChanged(); }
    float& AttenMax() override { return Real()->m_flAttenMax(); }
    void AttenMaxUpdated() override { Real()->m_flAttenMax.NetworkStateChanged(); }
    CUtlSymbolLarge& ParameterName() override { return Real()->m_iszParameterName(); }
    void ParameterNameUpdated() override { Real()->m_iszParameterName.NetworkStateChanged(); }
};

inline ISoundEventConeEntity* CSoundEventConeEntity::ToInterface() { return new CSoundEventConeEntityImpl(this); }
inline ISoundEventConeEntity* ISoundEventConeEntity::FromOriginal(CSoundEventConeEntity* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSOUNDEVENTCONEENTITYIMPL_H
