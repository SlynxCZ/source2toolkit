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

#ifndef _INCLUDE_CRAGDOLLPROPIMPL_H
#define _INCLUDE_CRAGDOLLPROPIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IRagdollProp.h"
#include "schema/entity/classes/CRagdollProp.h"
#include "CBaseAnimGraphImpl.h"

class CRagdollPropImpl : public CBaseAnimGraphImpl, public IRagdollProp
{

public:
    explicit CRagdollPropImpl(CRagdollProp* p) : CBaseAnimGraphImpl(p) {}

private:
    CRagdollProp* Real() { return static_cast<CRagdollProp*>(m_pReal); }
    CRagdollProp* Real() const { return static_cast<CRagdollProp*>(m_pReal); }

public:
    CRagdollProp* GetOriginal() const override { return Real(); }
    ::ragdoll_t& Ragdoll() override { return Real()->m_ragdoll(); }
    void RagdollUpdated() override { Real()->m_ragdoll.NetworkStateChanged(); }
    bool& StartDisabled() override { return Real()->m_bStartDisabled(); }
    void StartDisabledUpdated() override { Real()->m_bStartDisabled.NetworkStateChanged(); }
    CUtlVector<bool>& RagEnabled() override { return Real()->m_ragEnabled(); }
    void RagEnabledUpdated() override { Real()->m_ragEnabled.NetworkStateChanged(); }
    CUtlVector<Vector>& RagPos() override { return Real()->m_ragPos(); }
    void RagPosUpdated() override { Real()->m_ragPos.NetworkStateChanged(); }
    CUtlVector<QAngle>& RagAngles() override { return Real()->m_ragAngles(); }
    void RagAnglesUpdated() override { Real()->m_ragAngles.NetworkStateChanged(); }
    uint32_t& LastUpdateTickCount() override { return Real()->m_lastUpdateTickCount(); }
    void LastUpdateTickCountUpdated() override { Real()->m_lastUpdateTickCount.NetworkStateChanged(); }
    bool& AllAsleep() override { return Real()->m_allAsleep(); }
    void AllAsleepUpdated() override { Real()->m_allAsleep.NetworkStateChanged(); }
    bool& FirstCollisionAfterLaunch() override { return Real()->m_bFirstCollisionAfterLaunch(); }
    void FirstCollisionAfterLaunchUpdated() override { Real()->m_bFirstCollisionAfterLaunch.NetworkStateChanged(); }
    ::INavObstacle__NavObstacleType_t& NavObstacleType() override { return Real()->m_nNavObstacleType(); }
    void NavObstacleTypeUpdated() override { Real()->m_nNavObstacleType.NetworkStateChanged(); }
    bool& UpdateNavWhenMoving() override { return Real()->m_bUpdateNavWhenMoving(); }
    void UpdateNavWhenMovingUpdated() override { Real()->m_bUpdateNavWhenMoving.NetworkStateChanged(); }
    bool& ForceNavObstacleCut() override { return Real()->m_bForceNavObstacleCut(); }
    void ForceNavObstacleCutUpdated() override { Real()->m_bForceNavObstacleCut.NetworkStateChanged(); }
    bool& AttachedToReferenceFrame() override { return Real()->m_bAttachedToReferenceFrame(); }
    void AttachedToReferenceFrameUpdated() override { Real()->m_bAttachedToReferenceFrame.NetworkStateChanged(); }
    CHandle<CBaseEntity>& DamageEntity() override { return Real()->m_hDamageEntity(); }
    void DamageEntityUpdated() override { Real()->m_hDamageEntity.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Killer() override { return Real()->m_hKiller(); }
    void KillerUpdated() override { Real()->m_hKiller.NetworkStateChanged(); }
    CHandle<CBasePlayerPawn>& PhysicsAttacker() override { return Real()->m_hPhysicsAttacker(); }
    void PhysicsAttackerUpdated() override { Real()->m_hPhysicsAttacker.NetworkStateChanged(); }
    float& LastPhysicsInfluenceTime() override { return Real()->m_flLastPhysicsInfluenceTime(); }
    void LastPhysicsInfluenceTimeUpdated() override { Real()->m_flLastPhysicsInfluenceTime.NetworkStateChanged(); }
    float& FadeOutStartTime() override { return Real()->m_flFadeOutStartTime(); }
    void FadeOutStartTimeUpdated() override { Real()->m_flFadeOutStartTime.NetworkStateChanged(); }
    float& FadeTime() override { return Real()->m_flFadeTime(); }
    void FadeTimeUpdated() override { Real()->m_flFadeTime.NetworkStateChanged(); }
    Vector& LastOrigin() override { return Real()->m_vecLastOrigin(); }
    void LastOriginUpdated() override { Real()->m_vecLastOrigin.NetworkStateChanged(); }
    float& AwakeTime() override { return Real()->m_flAwakeTime(); }
    void AwakeTimeUpdated() override { Real()->m_flAwakeTime.NetworkStateChanged(); }
    float& LastOriginChangeTime() override { return Real()->m_flLastOriginChangeTime(); }
    void LastOriginChangeTimeUpdated() override { Real()->m_flLastOriginChangeTime.NetworkStateChanged(); }
    CUtlSymbolLarge& StrOriginClassName() override { return Real()->m_strOriginClassName(); }
    void StrOriginClassNameUpdated() override { Real()->m_strOriginClassName.NetworkStateChanged(); }
    CUtlSymbolLarge& StrSourceClassName() override { return Real()->m_strSourceClassName(); }
    void StrSourceClassNameUpdated() override { Real()->m_strSourceClassName.NetworkStateChanged(); }
    bool& HasBeenPhysgunned() override { return Real()->m_bHasBeenPhysgunned(); }
    void HasBeenPhysgunnedUpdated() override { Real()->m_bHasBeenPhysgunned.NetworkStateChanged(); }
    bool& AllowStretch() override { return Real()->m_bAllowStretch(); }
    void AllowStretchUpdated() override { Real()->m_bAllowStretch.NetworkStateChanged(); }
    float& BlendWeight() override { return Real()->m_flBlendWeight(); }
    void BlendWeightUpdated() override { Real()->m_flBlendWeight.NetworkStateChanged(); }
    float& DefaultFadeScale() override { return Real()->m_flDefaultFadeScale(); }
    void DefaultFadeScaleUpdated() override { Real()->m_flDefaultFadeScale.NetworkStateChanged(); }
    CUtlVector<Vector>& RagdollMins() override { return Real()->m_ragdollMins(); }
    void RagdollMinsUpdated() override { Real()->m_ragdollMins.NetworkStateChanged(); }
    CUtlVector<Vector>& RagdollMaxs() override { return Real()->m_ragdollMaxs(); }
    void RagdollMaxsUpdated() override { Real()->m_ragdollMaxs.NetworkStateChanged(); }
    bool& ShouldDeleteActivationRecord() override { return Real()->m_bShouldDeleteActivationRecord(); }
    void ShouldDeleteActivationRecordUpdated() override { Real()->m_bShouldDeleteActivationRecord.NetworkStateChanged(); }
    CUtlVector<INavObstacle*>& NavObstacles() override { return Real()->m_vecNavObstacles(); }
    void NavObstaclesUpdated() override { Real()->m_vecNavObstacles.NetworkStateChanged(); }
};

inline IRagdollProp* CRagdollProp::ToInterface() { return new CRagdollPropImpl(this); }
inline IRagdollProp* IRagdollProp::FromOriginal(CRagdollProp* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CRAGDOLLPROPIMPL_H
