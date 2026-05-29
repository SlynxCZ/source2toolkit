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

#ifndef _INCLUDE_CTESTEFFECTIMPL_H
#define _INCLUDE_CTESTEFFECTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITestEffect.h"
#include "schema/entity/classes/CTestEffect.h"
#include "CBaseEntityImpl.h"

class CTestEffectImpl : public CBaseEntityImpl, public virtual ITestEffect
{

public:
    explicit CTestEffectImpl(CTestEffect* p) : CBaseEntityImpl(p) {}

private:
    CTestEffect* Real() { return static_cast<CTestEffect*>(m_pReal); }
    CTestEffect* Real() const { return static_cast<CTestEffect*>(m_pReal); }

public:
    CTestEffect* GetOriginal() const override { return Real(); }
    int32_t& Loop() override { return Real()->m_iLoop(); }
    void LoopUpdated() override { Real()->m_iLoop.NetworkStateChanged(); }
    int32_t& Beam() override { return Real()->m_iBeam(); }
    void BeamUpdated() override { Real()->m_iBeam.NetworkStateChanged(); }
    float* BeamTime() override { return Real()->m_flBeamTime(); }
    float& StartTime() override { return Real()->m_flStartTime(); }
    void StartTimeUpdated() override { Real()->m_flStartTime.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ITestEffect* CTestEffect::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ITestEffect*>(tagIt->second.ptr_for_return);
    auto* impl = new CTestEffectImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ITestEffect*>(impl));
    return impl;
}
inline ITestEffect* ITestEffect::FromRaw(CEntityInstance* p) { return p ? static_cast<CTestEffect*>(p)->ToInterface() : nullptr; }
inline ITestEffect* ITestEffect::FromOriginal(CTestEffect* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CTESTEFFECTIMPL_H
