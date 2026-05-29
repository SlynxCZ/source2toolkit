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

#ifndef _INCLUDE_CINFOINTERACTIONIMPL_H
#define _INCLUDE_CINFOINTERACTIONIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IInfoInteraction.h"
#include "schema/entity/classes/CInfoInteraction.h"
#include "CPointEntityImpl.h"

class CInfoInteractionImpl : public CPointEntityImpl, public virtual IInfoInteraction
{

public:
    explicit CInfoInteractionImpl(CInfoInteraction* p) : CPointEntityImpl(p) {}

private:
    CInfoInteraction* Real() { return static_cast<CInfoInteraction*>(m_pReal); }
    CInfoInteraction* Real() const { return static_cast<CInfoInteraction*>(m_pReal); }

public:
    CInfoInteraction* GetOriginal() const override { return Real(); }
    ::SceneRequestHandle_t& SceneRequest() override { return Real()->m_hSceneRequest(); }
    void SceneRequestUpdated() override { Real()->m_hSceneRequest.NetworkStateChanged(); }
    ::SceneOpportunityHandle_t& SceneOpportunity() override { return Real()->m_hSceneOpportunity(); }
    void SceneOpportunityUpdated() override { Real()->m_hSceneOpportunity.NetworkStateChanged(); }
    bool& Enabled() override { return Real()->m_bEnabled(); }
    void EnabledUpdated() override { Real()->m_bEnabled.NetworkStateChanged(); }
    bool& StartDisabled() override { return Real()->m_bStartDisabled(); }
    void StartDisabledUpdated() override { Real()->m_bStartDisabled.NetworkStateChanged(); }
    CUtlSymbolLarge& StrSceneVDataName() override { return Real()->m_strSceneVDataName(); }
    void StrSceneVDataNameUpdated() override { Real()->m_strSceneVDataName.NetworkStateChanged(); }
    CUtlSymbolLarge& StrPulseVDataName() override { return Real()->m_strPulseVDataName(); }
    void StrPulseVDataNameUpdated() override { Real()->m_strPulseVDataName.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_flRadius(); }
    void RadiusUpdated() override { Real()->m_flRadius.NetworkStateChanged(); }
    float& OwnerFOV() override { return Real()->m_flOwnerFOV(); }
    void OwnerFOVUpdated() override { Real()->m_flOwnerFOV.NetworkStateChanged(); }
    CUtlSymbolLarge& StrLocalInterestReqTags() override { return Real()->m_strLocalInterestReqTags(); }
    void StrLocalInterestReqTagsUpdated() override { Real()->m_strLocalInterestReqTags.NetworkStateChanged(); }
    CUtlSymbolLarge& StrLocalInterestOptTags() override { return Real()->m_strLocalInterestOptTags(); }
    void StrLocalInterestOptTagsUpdated() override { Real()->m_strLocalInterestOptTags.NetworkStateChanged(); }
    CUtlSymbolLarge& StrLookTarget() override { return Real()->m_strLookTarget(); }
    void StrLookTargetUpdated() override { Real()->m_strLookTarget.NetworkStateChanged(); }
    float& Duration() override { return Real()->m_flDuration(); }
    void DurationUpdated() override { Real()->m_flDuration.NetworkStateChanged(); }
    float& Cooldown() override { return Real()->m_flCooldown(); }
    void CooldownUpdated() override { Real()->m_flCooldown.NetworkStateChanged(); }
    int32_t& RepeatCount() override { return Real()->m_nRepeatCount(); }
    void RepeatCountUpdated() override { Real()->m_nRepeatCount.NetworkStateChanged(); }
    bool& DisableOnExit() override { return Real()->m_bDisableOnExit(); }
    void DisableOnExitUpdated() override { Real()->m_bDisableOnExit.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IInfoInteraction* CInfoInteraction::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IInfoInteraction*>(tagIt->second.ptr_for_return);
    auto* impl = new CInfoInteractionImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IInfoInteraction*>(impl));
    return impl;
}
inline IInfoInteraction* IInfoInteraction::FromRaw(CEntityInstance* p) { return p ? static_cast<CInfoInteraction*>(p)->ToInterface() : nullptr; }
inline IInfoInteraction* IInfoInteraction::FromOriginal(CInfoInteraction* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CINFOINTERACTIONIMPL_H
