//
// Created by Michal Přikryl on 09.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "raytrace.h"

#include "addresses.h"
#include "commands.h"
#include "events.h"
#include "shared.h"
#include "source2toolkit/utils/plat.h"
#include "utils/scheduler.h"
#include "utils/vectorextends.h"
#include "dynlibutils/module.h"
#include "iserver.h"
#include "source2toolkit/schema/entity/classes/CBeam.h"
#include "schema/cgameresourceserviceserver.h"

namespace raytrace
{
    RayTrace rayTrace;

    void RayTrace::InitRayTrace()
    {
        m_pCNavPhysicsInterfaceVTable = DynLibUtils::CModule(shared::g_pServer).GetVirtualTableByName("CNavPhysicsInterface").RCast<void**>();
        if (!m_pCNavPhysicsInterfaceVTable)
        {
            FP_WARN("Tried getting virtual function from a null vtable.");
            return;
        }

        m_pCNavPhysicsInterface_TraceShape = m_pCNavPhysicsInterfaceVTable[shared::g_pGameConfig->GetOffset("CNavPhysicsInterface_TraceShape")];
    }

    void RayTrace::DestructRayTrace()
    {
        m_pCNavPhysicsInterfaceVTable = nullptr;
        m_pCNavPhysicsInterface_TraceShape = nullptr;
    }

    TraceResult RayTrace::TraceShape(const Vector& vecStart, const QAngle& angAngles, CEntityInstance* pIgnoreEntity, TraceOptions* pTraceOptions)
    {
        CTraceFilterEx filter = pIgnoreEntity ? CTraceFilterEx(static_cast<CBaseEntity*>(pIgnoreEntity)) : CTraceFilterEx();

        filter.m_nInteractsAs = 0;
        filter.m_nInteractsWith = static_cast<uint64_t>(MASK_SHOT_PHYSICS);
        filter.m_nInteractsExclude = 0;

        if (pTraceOptions)
        {
            if (pTraceOptions->InteractsAs != 0)
                filter.m_nInteractsAs = pTraceOptions->InteractsAs;

            if (pTraceOptions->InteractsWith != static_cast<uint64_t>(MASK_SHOT_PHYSICS))
                filter.m_nInteractsWith = pTraceOptions->InteractsWith;

            if (pTraceOptions->InteractsExclude != 0)
                filter.m_nInteractsExclude = pTraceOptions->InteractsExclude;
        }

        Vector forward;
        AngleVectors(angAngles, &forward);
        Vector vecEnd{
            vecStart.x + forward.x * 8192.f,
            vecStart.y + forward.y * 8192.f,
            vecStart.z + forward.z * 8192.f
        };

        Ray_t ray;

        return TraceShapeEx(vecStart, vecEnd, &filter, &ray);
    }

    TraceResult RayTrace::TraceEndShape(const Vector& vecStart, const Vector& vecEnd, CEntityInstance* pIgnoreEntity, TraceOptions* pTraceOptions)
    {
        CTraceFilterEx filter = pIgnoreEntity ? CTraceFilterEx(static_cast<CBaseEntity*>(pIgnoreEntity)) : CTraceFilterEx();

        filter.m_nInteractsAs = 0;
        filter.m_nInteractsWith = static_cast<uint64_t>(MASK_SHOT_PHYSICS);
        filter.m_nInteractsExclude = 0;

        if (pTraceOptions)
        {
            if (pTraceOptions->InteractsAs != 0)
                filter.m_nInteractsAs = pTraceOptions->InteractsAs;

            if (pTraceOptions->InteractsWith != static_cast<uint64_t>(MASK_SHOT_PHYSICS))
                filter.m_nInteractsWith = pTraceOptions->InteractsWith;

            if (pTraceOptions->InteractsExclude != 0)
                filter.m_nInteractsExclude = pTraceOptions->InteractsExclude;
        }

        Ray_t ray;

        return TraceShapeEx(vecStart, vecEnd, &filter, &ray);
    }

    TraceResult RayTrace::TraceHullShape(const Vector& vecStart, const Vector& vecEnd, const Vector& vecMins,
                                          const Vector& vecMaxs, CEntityInstance* pIgnoreEntity, TraceOptions* pTraceOptions)
    {
        CTraceFilterEx filter = pIgnoreEntity ? CTraceFilterEx(static_cast<CBaseEntity*>(pIgnoreEntity)) : CTraceFilterEx();

        filter.m_nInteractsAs = 0;
        filter.m_nInteractsWith = static_cast<uint64_t>(MASK_SHOT_PHYSICS);
        filter.m_nInteractsExclude = 0;

        if (pTraceOptions)
        {
            if (pTraceOptions->InteractsAs != 0)
                filter.m_nInteractsAs = pTraceOptions->InteractsAs;

            if (pTraceOptions->InteractsWith != static_cast<uint64_t>(MASK_SHOT_PHYSICS))
                filter.m_nInteractsWith = pTraceOptions->InteractsWith;

            if (pTraceOptions->InteractsExclude != 0)
                filter.m_nInteractsExclude = pTraceOptions->InteractsExclude;
        }

        Ray_t ray;
        ray.Init(vecMins, vecMaxs);

        return TraceShapeEx(vecStart, vecEnd, &filter, &ray);
    }

    TraceResult RayTrace::TraceShapeEx(const Vector& vecStart, const Vector& vecEnd, CTraceFilter* pTraceFilter, Ray_t* pRay)
    {
        if (!m_pCNavPhysicsInterface_TraceShape)
        {
            FP_ERROR("CNavPhysicsInterface::TraceShape is not bound!");
            return TraceResult();
        }

        Vector vecStartCopy = vecStart;
        Vector vecEndCopy = vecEnd;
        CGameTrace trace;

        bool bResult = m_pCNavPhysicsInterface_TraceShape.RCast<
            bool (*)(void*, Ray_t&, Vector&, Vector&, CTraceFilter*, CGameTrace*)>()(
            nullptr, *pRay, vecStartCopy, vecEndCopy, pTraceFilter, &trace);

        return TraceResult(&trace, bResult);
    }
}
