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

#ifndef _INCLUDE_CINFOFANIMPL_H
#define _INCLUDE_CINFOFANIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IInfoFan.h"
#include "schema/entity/classes/CInfoFan.h"
#include "CPointEntityImpl.h"

class CInfoFanImpl : public CPointEntityImpl, public IInfoFan
{

public:
    explicit CInfoFanImpl(CInfoFan* p) : CPointEntityImpl(p) {}

private:
    CInfoFan* Real() { return static_cast<CInfoFan*>(m_pReal); }
    CInfoFan* Real() const { return static_cast<CInfoFan*>(m_pReal); }

public:
    CInfoFan* GetOriginal() const override { return Real(); }
    float& FanForceMaxRadius() override { return Real()->m_fFanForceMaxRadius(); }
    void FanForceMaxRadiusUpdated() override { Real()->m_fFanForceMaxRadius.NetworkStateChanged(); }
    float& FanForceMinRadius() override { return Real()->m_fFanForceMinRadius(); }
    void FanForceMinRadiusUpdated() override { Real()->m_fFanForceMinRadius.NetworkStateChanged(); }
    float& CurveDistRange() override { return Real()->m_flCurveDistRange(); }
    void CurveDistRangeUpdated() override { Real()->m_flCurveDistRange.NetworkStateChanged(); }
    CUtlSymbolLarge& FanForceCurveString() override { return Real()->m_FanForceCurveString(); }
    void FanForceCurveStringUpdated() override { Real()->m_FanForceCurveString.NetworkStateChanged(); }
};

inline IInfoFan* CInfoFan::ToInterface() { return new CInfoFanImpl(this); }
inline IInfoFan* IInfoFan::FromOriginal(CInfoFan* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CINFOFANIMPL_H
