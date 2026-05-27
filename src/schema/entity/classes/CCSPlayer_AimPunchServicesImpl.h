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

#ifndef _INCLUDE_CCSPLAYER_AIMPUNCHSERVICESIMPL_H
#define _INCLUDE_CCSPLAYER_AIMPUNCHSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayer_AimPunchServices.h"
#include "schema/entity/classes/CCSPlayer_AimPunchServices.h"
#include "CPlayerPawnComponentImpl.h"

class CCSPlayer_AimPunchServicesImpl : public CPlayerPawnComponentImpl, public ICSPlayer_AimPunchServices
{

public:
    explicit CCSPlayer_AimPunchServicesImpl(CCSPlayer_AimPunchServices* p) : CPlayerPawnComponentImpl(p) {}

private:
    CCSPlayer_AimPunchServices* Real() { return static_cast<CCSPlayer_AimPunchServices*>(m_pReal); }

public:
    int32_t& PredictableBaseTick() override { return Real()->m_predictableBaseTick(); }
    void PredictableBaseTickUpdated() override { Real()->m_predictableBaseTick.NetworkStateChanged(); }
    float& PredictableBaseTickInterpAmount() override { return Real()->m_predictableBaseTickInterpAmount(); }
    void PredictableBaseTickInterpAmountUpdated() override { Real()->m_predictableBaseTickInterpAmount.NetworkStateChanged(); }
    QAngle& PredictableBaseAngle() override { return Real()->m_predictableBaseAngle(); }
    void PredictableBaseAngleUpdated() override { Real()->m_predictableBaseAngle.NetworkStateChanged(); }
    QAngle& PredictableBaseAngleVel() override { return Real()->m_predictableBaseAngleVel(); }
    void PredictableBaseAngleVelUpdated() override { Real()->m_predictableBaseAngleVel.NetworkStateChanged(); }
    int32_t& UnpredictableBaseTick() override { return Real()->m_unpredictableBaseTick(); }
    void UnpredictableBaseTickUpdated() override { Real()->m_unpredictableBaseTick.NetworkStateChanged(); }
    QAngle& UnpredictableBaseAngle() override { return Real()->m_unpredictableBaseAngle(); }
    void UnpredictableBaseAngleUpdated() override { Real()->m_unpredictableBaseAngle.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCSPLAYER_AIMPUNCHSERVICESIMPL_H
