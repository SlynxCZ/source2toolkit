/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
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
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
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
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */
#pragma once
#include "source2toolkit/IToolkitTrace.h"

#include "schema/entity/classes/CBaseEntity.h"
#include "schema/entity/classes/CCollisionProperty.h"

#include "eiface.h"
#include "entitysystem.h"

#include "dynlibutils/memaddr.h"

class CTraceFilterEx : public CTraceFilter
{
public:
    explicit CTraceFilterEx(CBaseEntity* entityToIgnore)
        : CTraceFilter(static_cast<CEntityInstance*>(entityToIgnore),
                       entityToIgnore ? entityToIgnore->m_hOwnerEntity.Get() : nullptr,
                       entityToIgnore
                           ? entityToIgnore->m_pCollision()->m_collisionAttribute().m_nHierarchyId()
                           : static_cast<uint16>(0xFFFFFFFF),
                       MASK_ALL,
                       COLLISION_GROUP_DEFAULT, true)
    {
    }

    CTraceFilterEx() : CTraceFilter(MASK_ALL, COLLISION_GROUP_DEFAULT, true)
    {
    }
};

namespace raytrace
{
    class RayTrace : public IToolkitTrace
    {
    public:
        TraceResult TraceShape(const Vector& vecStart, const QAngle& angAngles, IBaseEntity* pIgnoreEntity, TraceOptions* pTraceOptions) override;
        TraceResult TraceEndShape(const Vector& vecStart, const Vector& vecEnd, IBaseEntity* pIgnoreEntity, TraceOptions* pTraceOptions) override;
        TraceResult TraceHullShape(const Vector& vecStart, const Vector& vecEnd, const Vector& vecMins, const Vector& vecMaxs, IBaseEntity* pIgnoreEntity, TraceOptions* pTraceOptions) override;
        TraceResult TraceShapeEx(const Vector& vecStart, const Vector& vecEnd, CTraceFilter* pTraceFilter, Ray_t* pRay) override;
        uint64 PointContents(const Vector* const vTestPos, uint64 nContentsMask) override;
        bool CheckAreaOverlappingEntity(const void* const rArea, const IBaseEntity* const rEntity, bool bExtrudeHullHeight) override;
        void GetEntityWorldSpaceAABB(const IBaseEntity* const rEntity, Vector* pMinsOut, Vector* pMaxsOut) override;
    };

    extern RayTrace rayTrace;
}
