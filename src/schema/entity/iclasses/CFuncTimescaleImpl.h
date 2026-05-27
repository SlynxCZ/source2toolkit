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

#ifndef _INCLUDE_CFUNCTIMESCALEIMPL_H
#define _INCLUDE_CFUNCTIMESCALEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IFuncTimescale.h"
#include "schema/entity/classes/CFuncTimescale.h"
#include "CBaseEntityImpl.h"

class CFuncTimescaleImpl : public CBaseEntityImpl, public IFuncTimescale
{

public:
    explicit CFuncTimescaleImpl(CFuncTimescale* p) : CBaseEntityImpl(p) {}

private:
    CFuncTimescale* Real() { return static_cast<CFuncTimescale*>(m_pReal); }

public:
    float& DesiredTimescale() override { return Real()->m_flDesiredTimescale(); }
    void DesiredTimescaleUpdated() override { Real()->m_flDesiredTimescale.NetworkStateChanged(); }
    float& Acceleration() override { return Real()->m_flAcceleration(); }
    void AccelerationUpdated() override { Real()->m_flAcceleration.NetworkStateChanged(); }
    float& MinBlendRate() override { return Real()->m_flMinBlendRate(); }
    void MinBlendRateUpdated() override { Real()->m_flMinBlendRate.NetworkStateChanged(); }
    float& BlendDeltaMultiplier() override { return Real()->m_flBlendDeltaMultiplier(); }
    void BlendDeltaMultiplierUpdated() override { Real()->m_flBlendDeltaMultiplier.NetworkStateChanged(); }
    bool& IsStarted() override { return Real()->m_isStarted(); }
    void IsStartedUpdated() override { Real()->m_isStarted.NetworkStateChanged(); }
};

#endif // _INCLUDE_CFUNCTIMESCALEIMPL_H
