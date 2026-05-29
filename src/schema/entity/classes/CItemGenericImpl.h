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

#ifndef _INCLUDE_CITEMGENERICIMPL_H
#define _INCLUDE_CITEMGENERICIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IItemGeneric.h"
#include "schema/entity/classes/CItemGeneric.h"
#include "CItemImpl.h"

class CItemGenericImpl : public CItemImpl, public IItemGeneric
{

public:
    explicit CItemGenericImpl(CItemGeneric* p) : CItemImpl(p) {}

private:
    CItemGeneric* Real() { return static_cast<CItemGeneric*>(m_pReal); }
    CItemGeneric* Real() const { return static_cast<CItemGeneric*>(m_pReal); }

public:
    CItemGeneric* GetOriginal() const override { return Real(); }
    bool& HasTriggerRadius() override { return Real()->m_bHasTriggerRadius(); }
    void HasTriggerRadiusUpdated() override { Real()->m_bHasTriggerRadius.NetworkStateChanged(); }
    bool& HasPickupRadius() override { return Real()->m_bHasPickupRadius(); }
    void HasPickupRadiusUpdated() override { Real()->m_bHasPickupRadius.NetworkStateChanged(); }
    float& PickupRadiusSqr() override { return Real()->m_flPickupRadiusSqr(); }
    void PickupRadiusSqrUpdated() override { Real()->m_flPickupRadiusSqr.NetworkStateChanged(); }
    float& TriggerRadiusSqr() override { return Real()->m_flTriggerRadiusSqr(); }
    void TriggerRadiusSqrUpdated() override { Real()->m_flTriggerRadiusSqr.NetworkStateChanged(); }
    float& LastPickupCheck() override { return Real()->m_flLastPickupCheck(); }
    void LastPickupCheckUpdated() override { Real()->m_flLastPickupCheck.NetworkStateChanged(); }
    bool& PlayerCounterListenerAdded() override { return Real()->m_bPlayerCounterListenerAdded(); }
    void PlayerCounterListenerAddedUpdated() override { Real()->m_bPlayerCounterListenerAdded.NetworkStateChanged(); }
    bool& PlayerInTriggerRadius() override { return Real()->m_bPlayerInTriggerRadius(); }
    void PlayerInTriggerRadiusUpdated() override { Real()->m_bPlayerInTriggerRadius.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIParticleSystemDefinition>& SpawnParticleEffect() override { return Real()->m_hSpawnParticleEffect(); }
    void SpawnParticleEffectUpdated() override { Real()->m_hSpawnParticleEffect.NetworkStateChanged(); }
    CUtlSymbolLarge& AmbientSoundEffect() override { return Real()->m_pAmbientSoundEffect(); }
    void AmbientSoundEffectUpdated() override { Real()->m_pAmbientSoundEffect.NetworkStateChanged(); }
    bool& AutoStartAmbientSound() override { return Real()->m_bAutoStartAmbientSound(); }
    void AutoStartAmbientSoundUpdated() override { Real()->m_bAutoStartAmbientSound.NetworkStateChanged(); }
    CUtlSymbolLarge& SpawnScriptFunction() override { return Real()->m_pSpawnScriptFunction(); }
    void SpawnScriptFunctionUpdated() override { Real()->m_pSpawnScriptFunction.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIParticleSystemDefinition>& PickupParticleEffect() override { return Real()->m_hPickupParticleEffect(); }
    void PickupParticleEffectUpdated() override { Real()->m_hPickupParticleEffect.NetworkStateChanged(); }
    CUtlSymbolLarge& PickupSoundEffect() override { return Real()->m_pPickupSoundEffect(); }
    void PickupSoundEffectUpdated() override { Real()->m_pPickupSoundEffect.NetworkStateChanged(); }
    CUtlSymbolLarge& PickupScriptFunction() override { return Real()->m_pPickupScriptFunction(); }
    void PickupScriptFunctionUpdated() override { Real()->m_pPickupScriptFunction.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIParticleSystemDefinition>& TimeoutParticleEffect() override { return Real()->m_hTimeoutParticleEffect(); }
    void TimeoutParticleEffectUpdated() override { Real()->m_hTimeoutParticleEffect.NetworkStateChanged(); }
    CUtlSymbolLarge& TimeoutSoundEffect() override { return Real()->m_pTimeoutSoundEffect(); }
    void TimeoutSoundEffectUpdated() override { Real()->m_pTimeoutSoundEffect.NetworkStateChanged(); }
    CUtlSymbolLarge& TimeoutScriptFunction() override { return Real()->m_pTimeoutScriptFunction(); }
    void TimeoutScriptFunctionUpdated() override { Real()->m_pTimeoutScriptFunction.NetworkStateChanged(); }
    CUtlSymbolLarge& PickupFilterName() override { return Real()->m_pPickupFilterName(); }
    void PickupFilterNameUpdated() override { Real()->m_pPickupFilterName.NetworkStateChanged(); }
    CHandle<CBaseFilter>& PickupFilter() override { return Real()->m_hPickupFilter(); }
    void PickupFilterUpdated() override { Real()->m_hPickupFilter.NetworkStateChanged(); }
    CEntityIOOutput& OnPickup() override { return Real()->m_OnPickup(); }
    void OnPickupUpdated() override { Real()->m_OnPickup.NetworkStateChanged(); }
    CEntityIOOutput& OnTimeout() override { return Real()->m_OnTimeout(); }
    void OnTimeoutUpdated() override { Real()->m_OnTimeout.NetworkStateChanged(); }
    CEntityIOOutput& OnTriggerStartTouch() override { return Real()->m_OnTriggerStartTouch(); }
    void OnTriggerStartTouchUpdated() override { Real()->m_OnTriggerStartTouch.NetworkStateChanged(); }
    CEntityIOOutput& OnTriggerTouch() override { return Real()->m_OnTriggerTouch(); }
    void OnTriggerTouchUpdated() override { Real()->m_OnTriggerTouch.NetworkStateChanged(); }
    CEntityIOOutput& OnTriggerEndTouch() override { return Real()->m_OnTriggerEndTouch(); }
    void OnTriggerEndTouchUpdated() override { Real()->m_OnTriggerEndTouch.NetworkStateChanged(); }
    CUtlSymbolLarge& AllowPickupScriptFunction() override { return Real()->m_pAllowPickupScriptFunction(); }
    void AllowPickupScriptFunctionUpdated() override { Real()->m_pAllowPickupScriptFunction.NetworkStateChanged(); }
    float& PickupRadius() override { return Real()->m_flPickupRadius(); }
    void PickupRadiusUpdated() override { Real()->m_flPickupRadius.NetworkStateChanged(); }
    float& TriggerRadius() override { return Real()->m_flTriggerRadius(); }
    void TriggerRadiusUpdated() override { Real()->m_flTriggerRadius.NetworkStateChanged(); }
    CUtlSymbolLarge& TriggerSoundEffect() override { return Real()->m_pTriggerSoundEffect(); }
    void TriggerSoundEffectUpdated() override { Real()->m_pTriggerSoundEffect.NetworkStateChanged(); }
    bool& GlowWhenInTrigger() override { return Real()->m_bGlowWhenInTrigger(); }
    void GlowWhenInTriggerUpdated() override { Real()->m_bGlowWhenInTrigger.NetworkStateChanged(); }
    Color& GlowColor() override { return Real()->m_glowColor(); }
    void GlowColorUpdated() override { Real()->m_glowColor.NetworkStateChanged(); }
    bool& Useable() override { return Real()->m_bUseable(); }
    void UseableUpdated() override { Real()->m_bUseable.NetworkStateChanged(); }
    CHandle<CItemGenericTriggerHelper>& TriggerHelper() override { return Real()->m_hTriggerHelper(); }
    void TriggerHelperUpdated() override { Real()->m_hTriggerHelper.NetworkStateChanged(); }
};

inline IItemGeneric* CItemGeneric::ToInterface() { return new CItemGenericImpl(this); }
inline IItemGeneric* IItemGeneric::FromOriginal(CItemGeneric* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CITEMGENERICIMPL_H
