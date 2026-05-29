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

#ifndef _INCLUDE_VELOCITYSAMPLERIMPL_H
#define _INCLUDE_VELOCITYSAMPLERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IVelocitySampler.h"
#include "schema/entity/classes/VelocitySampler.h"

class VelocitySamplerImpl : public virtual IVelocitySampler
{

protected:
    void* m_pReal;

public:
    explicit VelocitySamplerImpl(void* p) : m_pReal(p) {}

private:
    VelocitySampler* Real() { return static_cast<VelocitySampler*>(m_pReal); }
    VelocitySampler* Real() const { return static_cast<VelocitySampler*>(m_pReal); }

public:
    VelocitySampler* GetOriginal() const override { return Real(); }
    Vector& PrevSample() override { return Real()->m_prevSample(); }
    void PrevSampleUpdated() override { Real()->m_prevSample.NetworkStateChanged(); }
    float& PrevSampleTime() override { return Real()->m_fPrevSampleTime(); }
    void PrevSampleTimeUpdated() override { Real()->m_fPrevSampleTime.NetworkStateChanged(); }
    float& IdealSampleRate() override { return Real()->m_fIdealSampleRate(); }
    void IdealSampleRateUpdated() override { Real()->m_fIdealSampleRate.NetworkStateChanged(); }
};

inline IVelocitySampler* VelocitySampler::ToInterface() { return new VelocitySamplerImpl(this); }
inline IVelocitySampler* IVelocitySampler::FromOriginal(VelocitySampler* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_VELOCITYSAMPLERIMPL_H
