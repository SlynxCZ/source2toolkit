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

#ifndef _INCLUDE_CMATHREMAPIMPL_H
#define _INCLUDE_CMATHREMAPIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IMathRemap.h"
#include "schema/entity/classes/CMathRemap.h"
#include "CLogicalEntityImpl.h"

class CMathRemapImpl : public CLogicalEntityImpl, public IMathRemap
{

public:
    explicit CMathRemapImpl(CMathRemap* p) : CLogicalEntityImpl(p) {}

private:
    CMathRemap* Real() { return static_cast<CMathRemap*>(m_pReal); }

public:
    float& InMin() override { return Real()->m_flInMin(); }
    void InMinUpdated() override { Real()->m_flInMin.NetworkStateChanged(); }
    float& InMax() override { return Real()->m_flInMax(); }
    void InMaxUpdated() override { Real()->m_flInMax.NetworkStateChanged(); }
    float& Out1() override { return Real()->m_flOut1(); }
    void Out1Updated() override { Real()->m_flOut1.NetworkStateChanged(); }
    float& Out2() override { return Real()->m_flOut2(); }
    void Out2Updated() override { Real()->m_flOut2.NetworkStateChanged(); }
    float& OldInValue() override { return Real()->m_flOldInValue(); }
    void OldInValueUpdated() override { Real()->m_flOldInValue.NetworkStateChanged(); }
    bool& Enabled() override { return Real()->m_bEnabled(); }
    void EnabledUpdated() override { Real()->m_bEnabled.NetworkStateChanged(); }
    CEntityIOOutput& OnRoseAboveMin() override { return Real()->m_OnRoseAboveMin(); }
    void OnRoseAboveMinUpdated() override { Real()->m_OnRoseAboveMin.NetworkStateChanged(); }
    CEntityIOOutput& OnRoseAboveMax() override { return Real()->m_OnRoseAboveMax(); }
    void OnRoseAboveMaxUpdated() override { Real()->m_OnRoseAboveMax.NetworkStateChanged(); }
    CEntityIOOutput& OnFellBelowMin() override { return Real()->m_OnFellBelowMin(); }
    void OnFellBelowMinUpdated() override { Real()->m_OnFellBelowMin.NetworkStateChanged(); }
    CEntityIOOutput& OnFellBelowMax() override { return Real()->m_OnFellBelowMax(); }
    void OnFellBelowMaxUpdated() override { Real()->m_OnFellBelowMax.NetworkStateChanged(); }
};

#endif // _INCLUDE_CMATHREMAPIMPL_H
