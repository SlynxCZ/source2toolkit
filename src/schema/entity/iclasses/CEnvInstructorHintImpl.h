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

#ifndef _INCLUDE_CENVINSTRUCTORHINTIMPL_H
#define _INCLUDE_CENVINSTRUCTORHINTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IEnvInstructorHint.h"
#include "schema/entity/classes/CEnvInstructorHint.h"
#include "CPointEntityImpl.h"

class CEnvInstructorHintImpl : public CPointEntityImpl, public IEnvInstructorHint
{

public:
    explicit CEnvInstructorHintImpl(CEnvInstructorHint* p) : CPointEntityImpl(p) {}

private:
    CEnvInstructorHint* Real() { return static_cast<CEnvInstructorHint*>(m_pReal); }

public:
    CUtlSymbolLarge& Name() override { return Real()->m_iszName(); }
    void NameUpdated() override { Real()->m_iszName.NetworkStateChanged(); }
    CUtlSymbolLarge& Replace_Key() override { return Real()->m_iszReplace_Key(); }
    void Replace_KeyUpdated() override { Real()->m_iszReplace_Key.NetworkStateChanged(); }
    CUtlSymbolLarge& HintTargetEntity() override { return Real()->m_iszHintTargetEntity(); }
    void HintTargetEntityUpdated() override { Real()->m_iszHintTargetEntity.NetworkStateChanged(); }
    int32_t& Timeout() override { return Real()->m_iTimeout(); }
    void TimeoutUpdated() override { Real()->m_iTimeout.NetworkStateChanged(); }
    int32_t& DisplayLimit() override { return Real()->m_iDisplayLimit(); }
    void DisplayLimitUpdated() override { Real()->m_iDisplayLimit.NetworkStateChanged(); }
    CUtlSymbolLarge& Icon_Onscreen() override { return Real()->m_iszIcon_Onscreen(); }
    void Icon_OnscreenUpdated() override { Real()->m_iszIcon_Onscreen.NetworkStateChanged(); }
    CUtlSymbolLarge& Icon_Offscreen() override { return Real()->m_iszIcon_Offscreen(); }
    void Icon_OffscreenUpdated() override { Real()->m_iszIcon_Offscreen.NetworkStateChanged(); }
    CUtlSymbolLarge& Caption() override { return Real()->m_iszCaption(); }
    void CaptionUpdated() override { Real()->m_iszCaption.NetworkStateChanged(); }
    CUtlSymbolLarge& ActivatorCaption() override { return Real()->m_iszActivatorCaption(); }
    void ActivatorCaptionUpdated() override { Real()->m_iszActivatorCaption.NetworkStateChanged(); }
    Color& Color() override { return Real()->m_Color(); }
    void ColorUpdated() override { Real()->m_Color.NetworkStateChanged(); }
    float& IconOffset() override { return Real()->m_fIconOffset(); }
    void IconOffsetUpdated() override { Real()->m_fIconOffset.NetworkStateChanged(); }
    float& Range() override { return Real()->m_fRange(); }
    void RangeUpdated() override { Real()->m_fRange.NetworkStateChanged(); }
    uint8_t& PulseOption() override { return Real()->m_iPulseOption(); }
    void PulseOptionUpdated() override { Real()->m_iPulseOption.NetworkStateChanged(); }
    uint8_t& AlphaOption() override { return Real()->m_iAlphaOption(); }
    void AlphaOptionUpdated() override { Real()->m_iAlphaOption.NetworkStateChanged(); }
    uint8_t& ShakeOption() override { return Real()->m_iShakeOption(); }
    void ShakeOptionUpdated() override { Real()->m_iShakeOption.NetworkStateChanged(); }
    bool& Static() override { return Real()->m_bStatic(); }
    void StaticUpdated() override { Real()->m_bStatic.NetworkStateChanged(); }
    bool& NoOffscreen() override { return Real()->m_bNoOffscreen(); }
    void NoOffscreenUpdated() override { Real()->m_bNoOffscreen.NetworkStateChanged(); }
    bool& ForceCaption() override { return Real()->m_bForceCaption(); }
    void ForceCaptionUpdated() override { Real()->m_bForceCaption.NetworkStateChanged(); }
    int32_t& InstanceType() override { return Real()->m_iInstanceType(); }
    void InstanceTypeUpdated() override { Real()->m_iInstanceType.NetworkStateChanged(); }
    bool& SuppressRest() override { return Real()->m_bSuppressRest(); }
    void SuppressRestUpdated() override { Real()->m_bSuppressRest.NetworkStateChanged(); }
    CUtlSymbolLarge& Binding() override { return Real()->m_iszBinding(); }
    void BindingUpdated() override { Real()->m_iszBinding.NetworkStateChanged(); }
    bool& AllowNoDrawTarget() override { return Real()->m_bAllowNoDrawTarget(); }
    void AllowNoDrawTargetUpdated() override { Real()->m_bAllowNoDrawTarget.NetworkStateChanged(); }
    bool& AutoStart() override { return Real()->m_bAutoStart(); }
    void AutoStartUpdated() override { Real()->m_bAutoStart.NetworkStateChanged(); }
    bool& LocalPlayerOnly() override { return Real()->m_bLocalPlayerOnly(); }
    void LocalPlayerOnlyUpdated() override { Real()->m_bLocalPlayerOnly.NetworkStateChanged(); }
};

#endif // _INCLUDE_CENVINSTRUCTORHINTIMPL_H
