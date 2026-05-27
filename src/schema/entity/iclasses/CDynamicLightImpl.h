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

#ifndef _INCLUDE_CDYNAMICLIGHTIMPL_H
#define _INCLUDE_CDYNAMICLIGHTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IDynamicLight.h"
#include "schema/entity/classes/CDynamicLight.h"
#include "CBaseModelEntityImpl.h"

class CDynamicLightImpl : public CBaseModelEntityImpl, public IDynamicLight
{

public:
    explicit CDynamicLightImpl(CDynamicLight* p) : CBaseModelEntityImpl(p) {}

private:
    CDynamicLight* Real() { return static_cast<CDynamicLight*>(m_pReal); }

public:
    uint8_t& ActualFlags() override { return Real()->m_ActualFlags(); }
    void ActualFlagsUpdated() override { Real()->m_ActualFlags.NetworkStateChanged(); }
    uint8_t& Flags() override { return Real()->m_Flags(); }
    void FlagsUpdated() override { Real()->m_Flags.NetworkStateChanged(); }
    uint8_t& LightStyle() override { return Real()->m_LightStyle(); }
    void LightStyleUpdated() override { Real()->m_LightStyle.NetworkStateChanged(); }
    bool& On() override { return Real()->m_On(); }
    void OnUpdated() override { Real()->m_On.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_Radius(); }
    void RadiusUpdated() override { Real()->m_Radius.NetworkStateChanged(); }
    int32_t& Exponent() override { return Real()->m_Exponent(); }
    void ExponentUpdated() override { Real()->m_Exponent.NetworkStateChanged(); }
    float& InnerAngle() override { return Real()->m_InnerAngle(); }
    void InnerAngleUpdated() override { Real()->m_InnerAngle.NetworkStateChanged(); }
    float& OuterAngle() override { return Real()->m_OuterAngle(); }
    void OuterAngleUpdated() override { Real()->m_OuterAngle.NetworkStateChanged(); }
    float& SpotRadius() override { return Real()->m_SpotRadius(); }
    void SpotRadiusUpdated() override { Real()->m_SpotRadius.NetworkStateChanged(); }
};

#endif // _INCLUDE_CDYNAMICLIGHTIMPL_H
