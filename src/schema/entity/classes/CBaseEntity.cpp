//
// Created by Michal Přikryl on 04.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "CBaseEntity.h"

#include "CBodyComponent.h"
#include "CCollisionProperty.h"
#include "CEntitySubclassVDataBase.h"
#include "CGameSceneNode.h"

#include "core/addresses.h"
#include "core/shared.h"

Vector CBaseEntity::GetAbsOrigin()
{
    return m_CBodyComponent->m_pSceneNode->m_vecAbsOrigin;
}

QAngle CBaseEntity::GetAngRotation()
{
    return m_CBodyComponent->m_pSceneNode->m_angRotation;
}

QAngle CBaseEntity::GetAbsRotation()
{
    return m_CBodyComponent->m_pSceneNode->m_angAbsRotation;
}

Vector CBaseEntity::GetAbsVelocity()
{
    return m_vecAbsVelocity;
}

void CBaseEntity::SetAbsOrigin(Vector vecOrigin)
{
    m_CBodyComponent->m_pSceneNode->m_vecAbsOrigin(vecOrigin);
}

void CBaseEntity::SetAbsRotation(QAngle angAbsRotation)
{
    m_CBodyComponent->m_pSceneNode->m_angAbsRotation(angAbsRotation);
}

void CBaseEntity::SetAngRotation(QAngle angRotation)
{
    m_CBodyComponent->m_pSceneNode->m_angRotation(angRotation);
}

void CBaseEntity::SetAbsVelocity(Vector vecVelocity)
{
    m_vecAbsVelocity = vecVelocity;
}

void CBaseEntity::SetBaseVelocity(Vector vecVelocity)
{
    m_vecBaseVelocity = vecVelocity;
}

CEntitySubclassVDataBase* CBaseEntity::GetVData()
{
    return *(CEntitySubclassVDataBase**)((uint8*)(m_nSubclassID()) + 4);
}

void CBaseEntity::Teleport(const Vector *position, const QAngle *angles, const Vector *velocity)
{
    CALL_VIRTUAL(void, shared::g_pGameConfig->GetOffset("CBaseEntity_Teleport"), this, position, angles, velocity);
}

void CBaseEntity::SetMoveType(MoveType_t nMoveType)
{
    m_MoveType() = nMoveType;
    m_nActualMoveType() = nMoveType;
}

uint8 CBaseEntity::GetCollisionGroup()
{
    if (!m_pCollision())
        return 0;

    return m_pCollision->m_collisionAttribute().m_nCollisionGroup;
}

void CBaseEntity::SetCollisionGroup(uint8 nCollisionGroup = COLLISION_GROUP_DEBRIS)
{
    if (!m_pCollision())
        return;

    m_pCollision->m_collisionAttribute().m_nCollisionGroup = nCollisionGroup;
    m_pCollision->m_CollisionGroup = nCollisionGroup;
    CollisionRulesChanged();
}

void CBaseEntity::CollisionRulesChanged()
{
    CALL_VIRTUAL(void, shared::g_pGameConfig->GetOffset("CBaseEntity_CollisionRulesChanged"), this);
}

CHandle<CBaseEntity> CBaseEntity::GetHandle() { return m_pEntity->m_EHandle; }

const char* CBaseEntity::GetName() const { return m_pEntity->m_name.String(); }