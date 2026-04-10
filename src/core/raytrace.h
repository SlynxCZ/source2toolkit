//
// Created by Michal Přikryl on 09.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "source2toolkit/schema/entity/classes/CBaseEntity.h"
#include "source2toolkit/schema/entity/classes/CCollisionProperty.h"
#include "source2toolkit/schema/entityio.h"

#include "eiface.h"
#include "entitysystem.h"

#include "dynlibutils/memaddr.h"
#include "source2toolkit/IToolkitTrace.h"

class CTraceFilterEx : public CTraceFilter
{
public:
    explicit CTraceFilterEx(CBaseEntity* entityToIgnore)
        : CTraceFilter(static_cast<CEntityInstance*>(entityToIgnore),
                       entityToIgnore ? entityToIgnore->m_hOwnerEntity.Get() : nullptr,
                       entityToIgnore ? entityToIgnore->m_pCollision()->m_collisionAttribute().m_nHierarchyId() : static_cast<uint16>(0xFFFFFFFF),
                       static_cast<uint64_t>(MASK_SHOT_PHYSICS),
                       COLLISION_GROUP_DEFAULT, true)
    {
    }

    CTraceFilterEx() : CTraceFilter(static_cast<uint64_t>(MASK_SHOT_PHYSICS), COLLISION_GROUP_DEFAULT, true)
    {
    }
};

namespace raytrace {
    class RayTrace : public IToolkitTrace {
    public:
        void InitRayTrace();
        void DestructRayTrace();
    public:
        TraceResult TraceShape(const Vector& vecStart, const QAngle& angAngles, CEntityInstance* pIgnoreEntity, TraceOptions* pTraceOptions) override;
        TraceResult TraceEndShape(const Vector& vecStart, const Vector& vecEnd, CEntityInstance* pIgnoreEntity, TraceOptions* pTraceOptions) override;
        TraceResult TraceHullShape(const Vector& vecStart, const Vector& vecEnd, const Vector& vecMins, const Vector& vecMaxs, CEntityInstance* pIgnoreEntity, TraceOptions* pTraceOptions) override;
        TraceResult TraceShapeEx(const Vector& vecStart, const Vector& vecEnd, CTraceFilter* pTraceFilter, Ray_t* pRay) override;
    protected:
        DynLibUtils::CMemory m_pCNavPhysicsInterface_TraceShape;
    protected:
        void** m_pCNavPhysicsInterfaceVTable;
    };

    extern RayTrace rayTrace;
}
