//
// Created by Michal Přikryl on 09.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "raytrace.h"

#include "addresses.h"
#include "commands.h"
#include "events.h"
#include "shared.h"
#include "utils/plat.h"
#include "utils/scheduler.h"
#include "utils/vectorextends.h"
#include "dynlibutils/module.h"
#include "iserver.h"
#include "schema/entity/classes/CBeam.h"
#include "schema/cgameresourceserviceserver.h"

namespace raytrace
{
    RayTrace rayTrace;

    static void DrawBeam(const Vector& vecStart, const Vector& vecEnd, const Color& clrColor)
    {
        CBeam* pBeam = CBeam::New("env_beam");
        if (!pBeam) return;

        pBeam->m_clrRender() = clrColor;
        pBeam->m_fWidth() = 1.5f;
        pBeam->m_nRenderMode() = kRenderNormal;
        pBeam->m_nRenderFX() = kRenderFxNone;

        pBeam->Teleport(&vecStart, &vectorextends::RotationZero, &vectorextends::VectorZero);
        pBeam->m_vecEndPos() = vecEnd;
        pBeam->DispatchSpawn();
    }

    void RayTrace::InitListeners()
    {
        m_pCNavPhysicsInterfaceVTable = DynLibUtils::CModule(shared::g_pServer).GetVirtualTableByName("CNavPhysicsInterface").RCast<void**>();
        if (!m_pCNavPhysicsInterfaceVTable)
        {
            FP_WARN("Tried getting virtual function from a null vtable.");
            return;
        }

        m_pCNavPhysicsInterface_TraceShape = m_pCNavPhysicsInterfaceVTable[shared::g_pGameConfig->GetOffset("CNavPhysicsInterface_TraceShape")];
    }

    void RayTrace::DestructListeners()
    {
        m_pCNavPhysicsInterfaceVTable = nullptr;
        m_pCNavPhysicsInterface_TraceShape = nullptr;
    }

    bool RayTrace::TraceShape(const Vector& vecStart, const QAngle& angAngles, CEntityInstance* pIgnoreEntity,
                                      TraceOptions* pTraceOptions, TraceResult* pTraceResult)
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
        auto res = TraceShapeEx(vecStart, vecEnd, &filter, &ray, pTraceResult);

        if (pTraceOptions && pTraceOptions->DrawBeam)
        {
            Color col = res ? Color(255, 0, 0) : Color(0, 255, 0);
            DrawBeam(vecStart, res ? pTraceResult->EndPos : vecEnd, col);
        }

        return res;
    }

    bool RayTrace::TraceEndShape(const Vector& vecStart, const Vector& vecEnd, CEntityInstance* pIgnoreEntity,
                                         TraceOptions* pTraceOptions, TraceResult* pTraceResult)
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
        auto res = TraceShapeEx(vecStart, vecEnd, &filter, &ray, pTraceResult);

        if (pTraceOptions && pTraceOptions->DrawBeam)
        {
            Color col = res ? Color(255, 0, 0) : Color(0, 255, 0);
            DrawBeam(vecStart, res ? pTraceResult->EndPos : vecEnd, col);
        }

        return res;
    }

    bool RayTrace::TraceHullShape(const Vector& vecStart, const Vector& vecEnd, const Vector& vecMins,
                                          const Vector& vecMaxs, CEntityInstance* pIgnoreEntity,
                                          TraceOptions* pTraceOptions, TraceResult* pTraceResult)
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
        auto res = TraceShapeEx(vecStart, vecEnd, &filter, &ray, pTraceResult);

        if (pTraceOptions && pTraceOptions->DrawBeam)
        {
            Color col = res ? Color(255, 0, 0) : Color(0, 255, 0);
            DrawBeam(vecStart, res ? pTraceResult->EndPos : vecEnd, col);
        }

        return res;
    }

    bool RayTrace::TraceShapeEx(const Vector& vecStart, const Vector& vecEnd, CTraceFilter* pTraceFilter,
                                        Ray_t* pRay, TraceResult* pTraceResult)
    {
        if (!m_pCNavPhysicsInterface_TraceShape)
        {
            FP_ERROR("CNavPhysicsInterface::TraceShape is not bound!");
            return false;
        }

        CGameTrace trace{};
        Vector vecStartCopy = vecStart;
        Vector vecEndCopy = vecEnd;
        bool bResult = m_pCNavPhysicsInterface_TraceShape.RCast<
            bool (*)(void*, Ray_t&, Vector&, Vector&, CTraceFilter*, CGameTrace*)>()(
            nullptr, *pRay, vecStartCopy, vecEndCopy, pTraceFilter, &trace);

        if (pTraceResult)
        {
            pTraceResult->StartPos = trace.m_vStartPos;
            pTraceResult->EndPos = trace.m_vEndPos;
            pTraceResult->HitPoint = trace.m_vHitPoint;
            pTraceResult->Normal = trace.m_vHitNormal;
            pTraceResult->Fraction = trace.m_flFraction;
            pTraceResult->HitOffset = trace.m_flHitOffset;

            pTraceResult->TriangleIndex = trace.m_nTriangle;
            pTraceResult->HitboxBoneIndex = trace.m_nHitboxBoneIndex;
            pTraceResult->Contents = trace.m_nContents;
            pTraceResult->RayType = trace.m_eRayType;
            pTraceResult->AllSolid = trace.m_bStartInSolid;
            pTraceResult->ExactHitPoint = trace.m_bExactHitPoint;

            pTraceResult->HitEntity = trace.m_pEnt;
            pTraceResult->Hitbox = const_cast<CHitBox*>(trace.m_pHitbox);
            pTraceResult->SurfaceProps = const_cast<CPhysSurfaceProperties*>(trace.m_pSurfaceProperties);
            pTraceResult->BodyHandle = trace.m_hBody;
            pTraceResult->ShapeHandle = trace.m_hShape;
            pTraceResult->BodyTransform = trace.m_BodyTransform;
            pTraceResult->ShapeAttributes = trace.m_ShapeAttributes;
        }

        return bResult;
    }
}
