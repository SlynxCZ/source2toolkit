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

#ifndef _INCLUDE_CBASEENTITYIMPL_H
#define _INCLUDE_CBASEENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IBaseEntity.h"
#include "schema/entity/classes/CBaseEntity.h"

class CBaseEntityImpl : public virtual IBaseEntity
{

protected:
    void* m_pReal;

public:
    explicit CBaseEntityImpl(void* p) : m_pReal(p) {}

private:
    CBaseEntity* Real() { return static_cast<CBaseEntity*>(m_pReal); }

public:
    CBodyComponent*& CBodyComponent() override { return Real()->m_CBodyComponent(); }
    void CBodyComponentUpdated() override { Real()->m_CBodyComponent.NetworkStateChanged(); }
    CNetworkTransmitComponent& NetworkTransmitComponent() override { return Real()->m_NetworkTransmitComponent(); }
    void NetworkTransmitComponentUpdated() override { Real()->m_NetworkTransmitComponent.NetworkStateChanged(); }
    CUtlVector<thinkfunc_t>& ThinkFunctions() override { return Real()->m_aThinkFunctions(); }
    void ThinkFunctionsUpdated() override { Real()->m_aThinkFunctions.NetworkStateChanged(); }
    int32_t& CurrentThinkContext() override { return Real()->m_iCurrentThinkContext(); }
    void CurrentThinkContextUpdated() override { Real()->m_iCurrentThinkContext.NetworkStateChanged(); }
    int32_t& LastThinkTick() override { return Real()->m_nLastThinkTick(); }
    void LastThinkTickUpdated() override { Real()->m_nLastThinkTick.NetworkStateChanged(); }
    bool& DisabledContextThinks() override { return Real()->m_bDisabledContextThinks(); }
    void DisabledContextThinksUpdated() override { Real()->m_bDisabledContextThinks.NetworkStateChanged(); }
    CTypedBitVec<64>& IsSteadyState() override { return Real()->m_isSteadyState(); }
    void IsSteadyStateUpdated() override { Real()->m_isSteadyState.NetworkStateChanged(); }
    float& LastNetworkChange() override { return Real()->m_lastNetworkChange(); }
    void LastNetworkChangeUpdated() override { Real()->m_lastNetworkChange.NetworkStateChanged(); }
    BASEPTR& Think() override { return Real()->m_think(); }
    void ThinkUpdated() override { Real()->m_think.NetworkStateChanged(); }
    CUtlVector<ResponseContext_t>& ResponseContexts() override { return Real()->m_ResponseContexts(); }
    void ResponseContextsUpdated() override { Real()->m_ResponseContexts.NetworkStateChanged(); }
    CUtlSymbolLarge& ResponseContext() override { return Real()->m_iszResponseContext(); }
    void ResponseContextUpdated() override { Real()->m_iszResponseContext.NetworkStateChanged(); }
    ENTITYFUNCPTR& PfnTouch() override { return Real()->m_pfnTouch(); }
    void PfnTouchUpdated() override { Real()->m_pfnTouch.NetworkStateChanged(); }
    USEPTR& PfnUse() override { return Real()->m_pfnUse(); }
    void PfnUseUpdated() override { Real()->m_pfnUse.NetworkStateChanged(); }
    ENTITYFUNCPTR& PfnBlocked() override { return Real()->m_pfnBlocked(); }
    void PfnBlockedUpdated() override { Real()->m_pfnBlocked.NetworkStateChanged(); }
    BASEPTR& PfnMoveDone() override { return Real()->m_pfnMoveDone(); }
    void PfnMoveDoneUpdated() override { Real()->m_pfnMoveDone.NetworkStateChanged(); }
    int32_t& Health() override { return Real()->m_iHealth(); }
    void HealthUpdated() override { Real()->m_iHealth.NetworkStateChanged(); }
    int32_t& MaxHealth() override { return Real()->m_iMaxHealth(); }
    void MaxHealthUpdated() override { Real()->m_iMaxHealth.NetworkStateChanged(); }
    uint8_t& LifeState() override { return Real()->m_lifeState(); }
    void LifeStateUpdated() override { Real()->m_lifeState.NetworkStateChanged(); }
    float& DamageAccumulator() override { return Real()->m_flDamageAccumulator(); }
    void DamageAccumulatorUpdated() override { Real()->m_flDamageAccumulator.NetworkStateChanged(); }
    bool& TakesDamage() override { return Real()->m_bTakesDamage(); }
    void TakesDamageUpdated() override { Real()->m_bTakesDamage.NetworkStateChanged(); }
    TakeDamageFlags_t& TakeDamageFlags() override { return Real()->m_nTakeDamageFlags(); }
    void TakeDamageFlagsUpdated() override { Real()->m_nTakeDamageFlags.NetworkStateChanged(); }
    EntityPlatformTypes_t& PlatformType() override { return Real()->m_nPlatformType(); }
    void PlatformTypeUpdated() override { Real()->m_nPlatformType.NetworkStateChanged(); }
    MoveCollide_t& MoveCollide() override { return Real()->m_MoveCollide(); }
    void MoveCollideUpdated() override { Real()->m_MoveCollide.NetworkStateChanged(); }
    MoveType_t& MoveType() override { return Real()->m_MoveType(); }
    void MoveTypeUpdated() override { Real()->m_MoveType.NetworkStateChanged(); }
    MoveType_t& PreviouslySetMoveType() override { return Real()->m_nPreviouslySetMoveType(); }
    void PreviouslySetMoveTypeUpdated() override { Real()->m_nPreviouslySetMoveType.NetworkStateChanged(); }
    MoveType_t& ActualMoveType() override { return Real()->m_nActualMoveType(); }
    void ActualMoveTypeUpdated() override { Real()->m_nActualMoveType.NetworkStateChanged(); }
    uint8_t& WaterTouch() override { return Real()->m_nWaterTouch(); }
    void WaterTouchUpdated() override { Real()->m_nWaterTouch.NetworkStateChanged(); }
    uint8_t& SlimeTouch() override { return Real()->m_nSlimeTouch(); }
    void SlimeTouchUpdated() override { Real()->m_nSlimeTouch.NetworkStateChanged(); }
    bool& RestoreInHierarchy() override { return Real()->m_bRestoreInHierarchy(); }
    void RestoreInHierarchyUpdated() override { Real()->m_bRestoreInHierarchy.NetworkStateChanged(); }
    CUtlSymbolLarge& Target() override { return Real()->m_target(); }
    void TargetUpdated() override { Real()->m_target.NetworkStateChanged(); }
    CHandle<CBaseFilter>& DamageFilter() override { return Real()->m_hDamageFilter(); }
    void DamageFilterUpdated() override { Real()->m_hDamageFilter.NetworkStateChanged(); }
    CUtlSymbolLarge& DamageFilterName() override { return Real()->m_iszDamageFilterName(); }
    void DamageFilterNameUpdated() override { Real()->m_iszDamageFilterName.NetworkStateChanged(); }
    float& MoveDoneTime() override { return Real()->m_flMoveDoneTime(); }
    void MoveDoneTimeUpdated() override { Real()->m_flMoveDoneTime.NetworkStateChanged(); }
    CUtlStringToken* SubclassID() override { return Real()->m_nSubclassID(); }
    float& AnimTime() override { return Real()->m_flAnimTime(); }
    void AnimTimeUpdated() override { Real()->m_flAnimTime.NetworkStateChanged(); }
    float& SimulationTime() override { return Real()->m_flSimulationTime(); }
    void SimulationTimeUpdated() override { Real()->m_flSimulationTime.NetworkStateChanged(); }
    float& CreateTime() override { return Real()->m_flCreateTime(); }
    void CreateTimeUpdated() override { Real()->m_flCreateTime.NetworkStateChanged(); }
    bool& ClientSideRagdoll() override { return Real()->m_bClientSideRagdoll(); }
    void ClientSideRagdollUpdated() override { Real()->m_bClientSideRagdoll.NetworkStateChanged(); }
    uint8_t& InterpolationFrame() override { return Real()->m_ubInterpolationFrame(); }
    void InterpolationFrameUpdated() override { Real()->m_ubInterpolationFrame.NetworkStateChanged(); }
    Vector& PrevVPhysicsUpdatePos() override { return Real()->m_vPrevVPhysicsUpdatePos(); }
    void PrevVPhysicsUpdatePosUpdated() override { Real()->m_vPrevVPhysicsUpdatePos.NetworkStateChanged(); }
    uint8_t& TeamNum() override { return Real()->m_iTeamNum(); }
    void TeamNumUpdated() override { Real()->m_iTeamNum.NetworkStateChanged(); }
    CUtlSymbolLarge& Globalname() override { return Real()->m_iGlobalname(); }
    void GlobalnameUpdated() override { Real()->m_iGlobalname.NetworkStateChanged(); }
    int32_t& SentToClients() override { return Real()->m_iSentToClients(); }
    void SentToClientsUpdated() override { Real()->m_iSentToClients.NetworkStateChanged(); }
    float& Speed() override { return Real()->m_flSpeed(); }
    void SpeedUpdated() override { Real()->m_flSpeed.NetworkStateChanged(); }
    CUtlString& UniqueHammerID() override { return Real()->m_sUniqueHammerID(); }
    void UniqueHammerIDUpdated() override { Real()->m_sUniqueHammerID.NetworkStateChanged(); }
    uint32_t& Spawnflags() override { return Real()->m_spawnflags(); }
    void SpawnflagsUpdated() override { Real()->m_spawnflags.NetworkStateChanged(); }
    int32_t& NextThinkTick() override { return Real()->m_nNextThinkTick(); }
    void NextThinkTickUpdated() override { Real()->m_nNextThinkTick.NetworkStateChanged(); }
    int32_t& SimulationTick() override { return Real()->m_nSimulationTick(); }
    void SimulationTickUpdated() override { Real()->m_nSimulationTick.NetworkStateChanged(); }
    CEntityIOOutput& OnKilled() override { return Real()->m_OnKilled(); }
    void OnKilledUpdated() override { Real()->m_OnKilled.NetworkStateChanged(); }
    uint32_t& Flags() override { return Real()->m_fFlags(); }
    void FlagsUpdated() override { Real()->m_fFlags.NetworkStateChanged(); }
    Vector& AbsVelocity() override { return Real()->m_vecAbsVelocity(); }
    void AbsVelocityUpdated() override { Real()->m_vecAbsVelocity.NetworkStateChanged(); }
    CNetworkVelocityVector& Velocity() override { return Real()->m_vecVelocity(); }
    void VelocityUpdated() override { Real()->m_vecVelocity.NetworkStateChanged(); }
    Vector& BaseVelocity() override { return Real()->m_vecBaseVelocity(); }
    void BaseVelocityUpdated() override { Real()->m_vecBaseVelocity.NetworkStateChanged(); }
    int32_t& PushEnumCount() override { return Real()->m_nPushEnumCount(); }
    void PushEnumCountUpdated() override { Real()->m_nPushEnumCount.NetworkStateChanged(); }
    CCollisionProperty*& Collision() override { return Real()->m_pCollision(); }
    void CollisionUpdated() override { Real()->m_pCollision.NetworkStateChanged(); }
    CHandle<CBaseEntity>& EffectEntity() override { return Real()->m_hEffectEntity(); }
    void EffectEntityUpdated() override { Real()->m_hEffectEntity.NetworkStateChanged(); }
    CHandle<CBaseEntity>& OwnerEntity() override { return Real()->m_hOwnerEntity(); }
    void OwnerEntityUpdated() override { Real()->m_hOwnerEntity.NetworkStateChanged(); }
    uint32_t& Effects() override { return Real()->m_fEffects(); }
    void EffectsUpdated() override { Real()->m_fEffects.NetworkStateChanged(); }
    CHandle<CBaseEntity>& GroundEntity() override { return Real()->m_hGroundEntity(); }
    void GroundEntityUpdated() override { Real()->m_hGroundEntity.NetworkStateChanged(); }
    int32_t& GroundBodyIndex() override { return Real()->m_nGroundBodyIndex(); }
    void GroundBodyIndexUpdated() override { Real()->m_nGroundBodyIndex.NetworkStateChanged(); }
    float& Friction() override { return Real()->m_flFriction(); }
    void FrictionUpdated() override { Real()->m_flFriction.NetworkStateChanged(); }
    float& Elasticity() override { return Real()->m_flElasticity(); }
    void ElasticityUpdated() override { Real()->m_flElasticity.NetworkStateChanged(); }
    float& GravityScale() override { return Real()->m_flGravityScale(); }
    void GravityScaleUpdated() override { Real()->m_flGravityScale.NetworkStateChanged(); }
    float& TimeScale() override { return Real()->m_flTimeScale(); }
    void TimeScaleUpdated() override { Real()->m_flTimeScale.NetworkStateChanged(); }
    float& WaterLevel() override { return Real()->m_flWaterLevel(); }
    void WaterLevelUpdated() override { Real()->m_flWaterLevel.NetworkStateChanged(); }
    bool& GravityDisabled() override { return Real()->m_bGravityDisabled(); }
    void GravityDisabledUpdated() override { Real()->m_bGravityDisabled.NetworkStateChanged(); }
    bool& AnimatedEveryTick() override { return Real()->m_bAnimatedEveryTick(); }
    void AnimatedEveryTickUpdated() override { Real()->m_bAnimatedEveryTick.NetworkStateChanged(); }
    float& ActualGravityScale() override { return Real()->m_flActualGravityScale(); }
    void ActualGravityScaleUpdated() override { Real()->m_flActualGravityScale.NetworkStateChanged(); }
    bool& GravityActuallyDisabled() override { return Real()->m_bGravityActuallyDisabled(); }
    void GravityActuallyDisabledUpdated() override { Real()->m_bGravityActuallyDisabled.NetworkStateChanged(); }
    bool& DisableLowViolence() override { return Real()->m_bDisableLowViolence(); }
    void DisableLowViolenceUpdated() override { Real()->m_bDisableLowViolence.NetworkStateChanged(); }
    uint8_t& WaterType() override { return Real()->m_nWaterType(); }
    void WaterTypeUpdated() override { Real()->m_nWaterType.NetworkStateChanged(); }
    int32_t& EFlags() override { return Real()->m_iEFlags(); }
    void EFlagsUpdated() override { Real()->m_iEFlags.NetworkStateChanged(); }
    CEntityIOOutput& OnUser1() override { return Real()->m_OnUser1(); }
    void OnUser1Updated() override { Real()->m_OnUser1.NetworkStateChanged(); }
    CEntityIOOutput& OnUser2() override { return Real()->m_OnUser2(); }
    void OnUser2Updated() override { Real()->m_OnUser2.NetworkStateChanged(); }
    CEntityIOOutput& OnUser3() override { return Real()->m_OnUser3(); }
    void OnUser3Updated() override { Real()->m_OnUser3.NetworkStateChanged(); }
    CEntityIOOutput& OnUser4() override { return Real()->m_OnUser4(); }
    void OnUser4Updated() override { Real()->m_OnUser4.NetworkStateChanged(); }
    int32_t& InitialTeamNum() override { return Real()->m_iInitialTeamNum(); }
    void InitialTeamNumUpdated() override { Real()->m_iInitialTeamNum.NetworkStateChanged(); }
    float& NavIgnoreUntilTime() override { return Real()->m_flNavIgnoreUntilTime(); }
    void NavIgnoreUntilTimeUpdated() override { Real()->m_flNavIgnoreUntilTime.NetworkStateChanged(); }
    QAngle& AngVelocity() override { return Real()->m_vecAngVelocity(); }
    void AngVelocityUpdated() override { Real()->m_vecAngVelocity.NetworkStateChanged(); }
    bool& NetworkQuantizeOriginAndAngles() override { return Real()->m_bNetworkQuantizeOriginAndAngles(); }
    void NetworkQuantizeOriginAndAnglesUpdated() override { Real()->m_bNetworkQuantizeOriginAndAngles.NetworkStateChanged(); }
    bool& LagCompensate() override { return Real()->m_bLagCompensate(); }
    void LagCompensateUpdated() override { Real()->m_bLagCompensate.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Blocker() override { return Real()->m_pBlocker(); }
    void BlockerUpdated() override { Real()->m_pBlocker.NetworkStateChanged(); }
    float& LocalTime() override { return Real()->m_flLocalTime(); }
    void LocalTimeUpdated() override { Real()->m_flLocalTime.NetworkStateChanged(); }
    float& VPhysicsUpdateLocalTime() override { return Real()->m_flVPhysicsUpdateLocalTime(); }
    void VPhysicsUpdateLocalTimeUpdated() override { Real()->m_flVPhysicsUpdateLocalTime.NetworkStateChanged(); }
    BloodType& BloodType() override { return Real()->m_nBloodType(); }
    void BloodTypeUpdated() override { Real()->m_nBloodType.NetworkStateChanged(); }
    CPulseGraphInstance_ServerEntity*& PulseGraphInstance() override { return Real()->m_pPulseGraphInstance(); }
    void PulseGraphInstanceUpdated() override { Real()->m_pPulseGraphInstance.NetworkStateChanged(); }
};

#endif // _INCLUDE_CBASEENTITYIMPL_H
