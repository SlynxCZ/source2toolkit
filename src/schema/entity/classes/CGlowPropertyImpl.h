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

#ifndef _INCLUDE_CGLOWPROPERTYIMPL_H
#define _INCLUDE_CGLOWPROPERTYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IGlowProperty.h"
#include "schema/entity/classes/CGlowProperty.h"

class CGlowPropertyImpl : public virtual IGlowProperty
{

protected:
    void* m_pReal;

public:
    explicit CGlowPropertyImpl(void* p) : m_pReal(p) {}

private:
    CGlowProperty* Real() { return static_cast<CGlowProperty*>(m_pReal); }
    CGlowProperty* Real() const { return static_cast<CGlowProperty*>(m_pReal); }

public:
    CGlowProperty* GetOriginal() const override { return Real(); }
    Vector& GlowColor() override { return Real()->m_fGlowColor(); }
    void GlowColorUpdated() override { Real()->m_fGlowColor.NetworkStateChanged(); }
    int32_t& GlowType() override { return Real()->m_iGlowType(); }
    void GlowTypeUpdated() override { Real()->m_iGlowType.NetworkStateChanged(); }
    int32_t& GlowTeam() override { return Real()->m_iGlowTeam(); }
    void GlowTeamUpdated() override { Real()->m_iGlowTeam.NetworkStateChanged(); }
    int32_t& GlowRange() override { return Real()->m_nGlowRange(); }
    void GlowRangeUpdated() override { Real()->m_nGlowRange.NetworkStateChanged(); }
    int32_t& GlowRangeMin() override { return Real()->m_nGlowRangeMin(); }
    void GlowRangeMinUpdated() override { Real()->m_nGlowRangeMin.NetworkStateChanged(); }
    Color& GlowColorOverride() override { return Real()->m_glowColorOverride(); }
    void GlowColorOverrideUpdated() override { Real()->m_glowColorOverride.NetworkStateChanged(); }
    bool& Flashing() override { return Real()->m_bFlashing(); }
    void FlashingUpdated() override { Real()->m_bFlashing.NetworkStateChanged(); }
    float& GlowTime() override { return Real()->m_flGlowTime(); }
    void GlowTimeUpdated() override { Real()->m_flGlowTime.NetworkStateChanged(); }
    float& GlowStartTime() override { return Real()->m_flGlowStartTime(); }
    void GlowStartTimeUpdated() override { Real()->m_flGlowStartTime.NetworkStateChanged(); }
    bool& EligibleForScreenHighlight() override { return Real()->m_bEligibleForScreenHighlight(); }
    void EligibleForScreenHighlightUpdated() override { Real()->m_bEligibleForScreenHighlight.NetworkStateChanged(); }
    bool& Glowing() override { return Real()->m_bGlowing(); }
    void GlowingUpdated() override { Real()->m_bGlowing.NetworkStateChanged(); }
};

inline IGlowProperty* CGlowProperty::ToInterface() { return new CGlowPropertyImpl(this); }
inline IGlowProperty* IGlowProperty::FromRaw(CEntityInstance*) { return nullptr; }
inline IGlowProperty* IGlowProperty::FromOriginal(CGlowProperty* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CGLOWPROPERTYIMPL_H
