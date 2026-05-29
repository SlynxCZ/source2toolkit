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

#ifndef _INCLUDE_CMULTILIGHTPROXYIMPL_H
#define _INCLUDE_CMULTILIGHTPROXYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IMultiLightProxy.h"
#include "schema/entity/classes/CMultiLightProxy.h"
#include "CLogicalEntityImpl.h"

class CMultiLightProxyImpl : public CLogicalEntityImpl, public virtual IMultiLightProxy
{

public:
    explicit CMultiLightProxyImpl(CMultiLightProxy* p) : CLogicalEntityImpl(p) {}

private:
    CMultiLightProxy* Real() { return static_cast<CMultiLightProxy*>(m_pReal); }
    CMultiLightProxy* Real() const { return static_cast<CMultiLightProxy*>(m_pReal); }

public:
    CMultiLightProxy* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge& LightNameFilter() override { return Real()->m_iszLightNameFilter(); }
    void LightNameFilterUpdated() override { Real()->m_iszLightNameFilter.NetworkStateChanged(); }
    CUtlSymbolLarge& LightClassFilter() override { return Real()->m_iszLightClassFilter(); }
    void LightClassFilterUpdated() override { Real()->m_iszLightClassFilter.NetworkStateChanged(); }
    float& LightRadiusFilter() override { return Real()->m_flLightRadiusFilter(); }
    void LightRadiusFilterUpdated() override { Real()->m_flLightRadiusFilter.NetworkStateChanged(); }
    float& BrightnessDelta() override { return Real()->m_flBrightnessDelta(); }
    void BrightnessDeltaUpdated() override { Real()->m_flBrightnessDelta.NetworkStateChanged(); }
    bool& PerformScreenFade() override { return Real()->m_bPerformScreenFade(); }
    void PerformScreenFadeUpdated() override { Real()->m_bPerformScreenFade.NetworkStateChanged(); }
    float& TargetBrightnessMultiplier() override { return Real()->m_flTargetBrightnessMultiplier(); }
    void TargetBrightnessMultiplierUpdated() override { Real()->m_flTargetBrightnessMultiplier.NetworkStateChanged(); }
    float& CurrentBrightnessMultiplier() override { return Real()->m_flCurrentBrightnessMultiplier(); }
    void CurrentBrightnessMultiplierUpdated() override { Real()->m_flCurrentBrightnessMultiplier.NetworkStateChanged(); }
    CUtlVector<CHandle<CLightEntity>>& Lights() override { return Real()->m_vecLights(); }
    void LightsUpdated() override { Real()->m_vecLights.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IMultiLightProxy* CMultiLightProxy::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IMultiLightProxy*>(tagIt->second.ptr_for_return);
    auto* impl = new CMultiLightProxyImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IMultiLightProxy*>(impl));
    return impl;
}
inline IMultiLightProxy* IMultiLightProxy::FromRaw(CEntityInstance* p) { return p ? static_cast<CMultiLightProxy*>(p)->ToInterface() : nullptr; }
inline IMultiLightProxy* IMultiLightProxy::FromOriginal(CMultiLightProxy* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CMULTILIGHTPROXYIMPL_H
