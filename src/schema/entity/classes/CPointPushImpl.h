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

#ifndef _INCLUDE_CPOINTPUSHIMPL_H
#define _INCLUDE_CPOINTPUSHIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointPush.h"
#include "schema/entity/classes/CPointPush.h"
#include "CPointEntityImpl.h"

class CPointPushImpl : public CPointEntityImpl, public IPointPush
{

public:
    explicit CPointPushImpl(CPointPush* p) : CPointEntityImpl(p) {}

private:
    CPointPush* Real() { return static_cast<CPointPush*>(m_pReal); }
    CPointPush* Real() const { return static_cast<CPointPush*>(m_pReal); }

public:
    CPointPush* GetOriginal() const override { return Real(); }
    bool& Enabled() override { return Real()->m_bEnabled(); }
    void EnabledUpdated() override { Real()->m_bEnabled.NetworkStateChanged(); }
    float& Magnitude() override { return Real()->m_flMagnitude(); }
    void MagnitudeUpdated() override { Real()->m_flMagnitude.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_flRadius(); }
    void RadiusUpdated() override { Real()->m_flRadius.NetworkStateChanged(); }
    float& InnerRadius() override { return Real()->m_flInnerRadius(); }
    void InnerRadiusUpdated() override { Real()->m_flInnerRadius.NetworkStateChanged(); }
    float& ConeOfInfluence() override { return Real()->m_flConeOfInfluence(); }
    void ConeOfInfluenceUpdated() override { Real()->m_flConeOfInfluence.NetworkStateChanged(); }
    CUtlSymbolLarge& FilterName() override { return Real()->m_iszFilterName(); }
    void FilterNameUpdated() override { Real()->m_iszFilterName.NetworkStateChanged(); }
    CHandle<CBaseFilter>& Filter() override { return Real()->m_hFilter(); }
    void FilterUpdated() override { Real()->m_hFilter.NetworkStateChanged(); }
};

inline IPointPush* CPointPush::ToInterface() { return new CPointPushImpl(this); }
inline IPointPush* IPointPush::FromOriginal(CPointPush* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPOINTPUSHIMPL_H
