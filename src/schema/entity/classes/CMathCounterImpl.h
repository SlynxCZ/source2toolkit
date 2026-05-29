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

#ifndef _INCLUDE_CMATHCOUNTERIMPL_H
#define _INCLUDE_CMATHCOUNTERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IMathCounter.h"
#include "schema/entity/classes/CMathCounter.h"
#include "CLogicalEntityImpl.h"

class CMathCounterImpl : public CLogicalEntityImpl, public IMathCounter
{

public:
    explicit CMathCounterImpl(CMathCounter* p) : CLogicalEntityImpl(p) {}

private:
    CMathCounter* Real() { return static_cast<CMathCounter*>(m_pReal); }
    CMathCounter* Real() const { return static_cast<CMathCounter*>(m_pReal); }

public:
    CMathCounter* GetOriginal() const override { return Real(); }
    float& Min() override { return Real()->m_flMin(); }
    void MinUpdated() override { Real()->m_flMin.NetworkStateChanged(); }
    float& Max() override { return Real()->m_flMax(); }
    void MaxUpdated() override { Real()->m_flMax.NetworkStateChanged(); }
    bool& HitMin() override { return Real()->m_bHitMin(); }
    void HitMinUpdated() override { Real()->m_bHitMin.NetworkStateChanged(); }
    bool& HitMax() override { return Real()->m_bHitMax(); }
    void HitMaxUpdated() override { Real()->m_bHitMax.NetworkStateChanged(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    ::CEntityIOOutput& OnHitMin() override { return Real()->m_OnHitMin(); }
    void OnHitMinUpdated() override { Real()->m_OnHitMin.NetworkStateChanged(); }
    ::CEntityIOOutput& OnHitMax() override { return Real()->m_OnHitMax(); }
    void OnHitMaxUpdated() override { Real()->m_OnHitMax.NetworkStateChanged(); }
    ::CEntityIOOutput& OnChangedFromMin() override { return Real()->m_OnChangedFromMin(); }
    void OnChangedFromMinUpdated() override { Real()->m_OnChangedFromMin.NetworkStateChanged(); }
    ::CEntityIOOutput& OnChangedFromMax() override { return Real()->m_OnChangedFromMax(); }
    void OnChangedFromMaxUpdated() override { Real()->m_OnChangedFromMax.NetworkStateChanged(); }
};

inline IMathCounter* CMathCounter::ToInterface() { return new CMathCounterImpl(this); }
inline IMathCounter* IMathCounter::FromOriginal(CMathCounter* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CMATHCOUNTERIMPL_H
