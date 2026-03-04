#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "vector.h"
#include "utlsymbol.h"
#include "utlsymbollarge.h"
#include "utlstring.h"
#include "utlstringtoken.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "../enums/BloodType.h"
#include "CNetworkTransmitComponent.h"
#include "CNetworkVelocityVector.h"
#include "../enums/EntityPlatformTypes_t.h"
#include "ResponseContext_t.h"
#include "../enums/TakeDamageFlags_t.h"
#include "thinkfunc_t.h"

class CBaseFilter;
class CBodyComponent;
class CCollisionProperty;
class CEntitySubclassVDataBase;
class CPulseGraphInstance_ServerEntity;

class CBaseEntity : public CEntityInstance
{
public:
    DECLARE_SCHEMA_CLASS(CBaseEntity);

    SCHEMA_FIELD(CBodyComponent*, m_CBodyComponent);
    SCHEMA_FIELD(CNetworkTransmitComponent, m_NetworkTransmitComponent);
    SCHEMA_FIELD(CUtlVector<thinkfunc_t>, m_aThinkFunctions);
    SCHEMA_FIELD(int32_t, m_iCurrentThinkContext);
    SCHEMA_FIELD(int32_t, m_nLastThinkTick);
    SCHEMA_FIELD(bool, m_bDisabledContextThinks);
    SCHEMA_FIELD_POINTER(uint8_t, m_isSteadyState);
    SCHEMA_FIELD(float, m_lastNetworkChange);
    SCHEMA_FIELD(CUtlVector<ResponseContext_t>, m_ResponseContexts);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszResponseContext);
    SCHEMA_FIELD(int32_t, m_iHealth);
    SCHEMA_FIELD(int32_t, m_iMaxHealth);
    SCHEMA_FIELD(uint8_t, m_lifeState);
    SCHEMA_FIELD(float, m_flDamageAccumulator);
    SCHEMA_FIELD(bool, m_bTakesDamage);
    SCHEMA_FIELD(TakeDamageFlags_t, m_nTakeDamageFlags);
    SCHEMA_FIELD(EntityPlatformTypes_t, m_nPlatformType);
    SCHEMA_FIELD(MoveCollide_t, m_MoveCollide);
    SCHEMA_FIELD(MoveType_t, m_MoveType);
    SCHEMA_FIELD(MoveType_t, m_nActualMoveType);
    SCHEMA_FIELD(uint8_t, m_nWaterTouch);
    SCHEMA_FIELD(uint8_t, m_nSlimeTouch);
    SCHEMA_FIELD(bool, m_bRestoreInHierarchy);
    SCHEMA_FIELD(CUtlSymbolLarge, m_target);
    SCHEMA_FIELD(CHandle<CBaseFilter>, m_hDamageFilter);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszDamageFilterName);
    SCHEMA_FIELD(float, m_flMoveDoneTime);
    SCHEMA_FIELD_POINTER(CUtlStringToken, m_nSubclassID);
    SCHEMA_FIELD(float, m_flAnimTime);
    SCHEMA_FIELD(float, m_flSimulationTime);
    SCHEMA_FIELD(float, m_flCreateTime);
    SCHEMA_FIELD(bool, m_bClientSideRagdoll);
    SCHEMA_FIELD(uint8_t, m_ubInterpolationFrame);
    SCHEMA_FIELD(Vector, m_vPrevVPhysicsUpdatePos);
    SCHEMA_FIELD(uint8_t, m_iTeamNum);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iGlobalname);
    SCHEMA_FIELD(int32_t, m_iSentToClients);
    SCHEMA_FIELD(float, m_flSpeed);
    SCHEMA_FIELD(CUtlString, m_sUniqueHammerID);
    SCHEMA_FIELD(uint32_t, m_spawnflags);
    SCHEMA_FIELD(int32_t, m_nNextThinkTick);
    SCHEMA_FIELD(int32_t, m_nSimulationTick);
    SCHEMA_FIELD(CEntityIOOutput, m_OnKilled);
    SCHEMA_FIELD(uint32_t, m_fFlags);
    SCHEMA_FIELD(Vector, m_vecAbsVelocity);
    SCHEMA_FIELD(CNetworkVelocityVector, m_vecVelocity);
    SCHEMA_FIELD(Vector, m_vecBaseVelocity);
    SCHEMA_FIELD(int32_t, m_nPushEnumCount);
    SCHEMA_FIELD(CCollisionProperty*, m_pCollision);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hEffectEntity);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hOwnerEntity);
    SCHEMA_FIELD(uint32_t, m_fEffects);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hGroundEntity);
    SCHEMA_FIELD(int32_t, m_nGroundBodyIndex);
    SCHEMA_FIELD(float, m_flFriction);
    SCHEMA_FIELD(float, m_flElasticity);
    SCHEMA_FIELD(float, m_flGravityScale);
    SCHEMA_FIELD(float, m_flTimeScale);
    SCHEMA_FIELD(float, m_flWaterLevel);
    SCHEMA_FIELD(bool, m_bGravityDisabled);
    SCHEMA_FIELD(bool, m_bAnimatedEveryTick);
    SCHEMA_FIELD(float, m_flActualGravityScale);
    SCHEMA_FIELD(bool, m_bGravityActuallyDisabled);
    SCHEMA_FIELD(bool, m_bDisableLowViolence);
    SCHEMA_FIELD(uint8_t, m_nWaterType);
    SCHEMA_FIELD(int32_t, m_iEFlags);
    SCHEMA_FIELD(CEntityIOOutput, m_OnUser1);
    SCHEMA_FIELD(CEntityIOOutput, m_OnUser2);
    SCHEMA_FIELD(CEntityIOOutput, m_OnUser3);
    SCHEMA_FIELD(CEntityIOOutput, m_OnUser4);
    SCHEMA_FIELD(int32_t, m_iInitialTeamNum);
    SCHEMA_FIELD(float, m_flNavIgnoreUntilTime);
    SCHEMA_FIELD(QAngle, m_vecAngVelocity);
    SCHEMA_FIELD(bool, m_bNetworkQuantizeOriginAndAngles);
    SCHEMA_FIELD(bool, m_bLagCompensate);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_pBlocker);
    SCHEMA_FIELD(float, m_flLocalTime);
    SCHEMA_FIELD(float, m_flVPhysicsUpdateLocalTime);
    SCHEMA_FIELD(BloodType, m_nBloodType);
    SCHEMA_FIELD(CPulseGraphInstance_ServerEntity*, m_pPulseGraphInstance);

public:
    Vector GetAbsOrigin();
    QAngle GetAngRotation();
    QAngle GetAbsRotation();
    Vector GetAbsVelocity();
    void SetAbsOrigin(Vector vecOrigin);
    void SetAbsRotation(QAngle angAbsRotation);
    void SetAngRotation(QAngle angRotation);
    void SetAbsVelocity(Vector vecVelocity);
    void SetBaseVelocity(Vector vecVelocity);
    CEntitySubclassVDataBase* GetVData();
    void Teleport(const Vector* position, const QAngle* angles, const Vector* velocity);
    void SetMoveType(MoveType_t nMoveType);
    uint8 GetCollisionGroup();
    void SetCollisionGroup(uint8 nCollisionGroup);
    void CollisionRulesChanged();
    CHandle<CBaseEntity> GetHandle();
    const char* GetName() const;
};
