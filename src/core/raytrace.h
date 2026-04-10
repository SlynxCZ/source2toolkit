//
// Created by Michal Přikryl on 09.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "schema/entity/classes/CBaseEntity.h"
#include "schema/entity/classes/CCollisionProperty.h"
#include "schema/entityio.h"

#include "eiface.h"
#include "entitysystem.h"

#include "dynlibutils/memaddr.h"

enum class InteractionLayers : uint64_t
{
    Solid = 0x1,
    Hitboxes = 0x2,
    Trigger = 0x4,
    Sky = 0x8,
    PlayerClip = 0x10,
    NPCClip = 0x20,
    BlockLOS = 0x40,
    BlockLight = 0x80,
    Ladder = 0x100,
    Pickup = 0x200,
    BlockSound = 0x400,
    NoDraw = 0x800,
    Window = 0x1000,
    PassBullets = 0x2000,
    WorldGeometry = 0x4000,
    Water = 0x8000,
    Slime = 0x10000,
    TouchAll = 0x20000,
    Player = 0x40000,
    NPC = 0x80000,
    Debris = 0x100000,
    Physics_Prop = 0x200000,
    NavIgnore = 0x400000,
    NavLocalIgnore = 0x800000,
    PostProcessingVolume = 0x1000000,
    UnusedLayer3 = 0x2000000,
    CarriedObject = 0x4000000,
    PushAway = 0x8000000,
    ServerEntityOnClient = 0x10000000,
    CarriedWeapon = 0x20000000,
    StaticLevel = 0x40000000,
    csgo_team1 = 0x80000000,
    csgo_team2 = 0x100000000,
    csgo_grenadeclip = 0x200000000,
    csgo_droneclip = 0x400000000,
    csgo_moveable = 0x800000000,
    csgo_opaque = 0x1000000000,
    csgo_monster = 0x2000000000,
    csgo_thrown_grenade = 0x8000000000
};

constexpr InteractionLayers operator|(InteractionLayers a, InteractionLayers b)
{
    return static_cast<InteractionLayers>(
        static_cast<uint64_t>(a) | static_cast<uint64_t>(b)
    );
}

constexpr InteractionLayers operator&(InteractionLayers a, InteractionLayers b)
{
    return static_cast<InteractionLayers>(
        static_cast<uint64_t>(a) & static_cast<uint64_t>(b)
    );
}

constexpr InteractionLayers operator~(InteractionLayers a)
{
    return static_cast<InteractionLayers>(
        ~static_cast<uint64_t>(a)
    );
}

constexpr InteractionLayers& operator|=(InteractionLayers& a, InteractionLayers b)
{
    a = a | b;
    return a;
}

/// Custom base (0x2C3011, using this as default in my plugins)
constexpr InteractionLayers MASK_SHOT_PHYSICS =
    InteractionLayers::Solid |
    InteractionLayers::PlayerClip |
    InteractionLayers::Window |
    InteractionLayers::PassBullets |
    InteractionLayers::Player |
    InteractionLayers::NPC |
    InteractionLayers::Physics_Prop;

/// Only hitboxes (headshots etc.)
constexpr InteractionLayers MASK_SHOT_HITBOX =
    InteractionLayers::Hitboxes |
    InteractionLayers::Player |
    InteractionLayers::NPC;

/// Physics + hitboxes (full bullet trace)
constexpr InteractionLayers MASK_SHOT_FULL =
    MASK_SHOT_PHYSICS |
    InteractionLayers::Hitboxes;

/// World only (no entities)
constexpr InteractionLayers MASK_WORLD_ONLY =
    InteractionLayers::Solid |
    InteractionLayers::Window |
    InteractionLayers::PassBullets;

/// Grenade trace
constexpr InteractionLayers MASK_GRENADE =
    InteractionLayers::Solid |
    InteractionLayers::Window |
    InteractionLayers::Physics_Prop |
    InteractionLayers::PassBullets;

/// Brush only
constexpr InteractionLayers MASK_BRUSH_ONLY =
    InteractionLayers::Solid |
    InteractionLayers::Window;

/// Movement (player)
constexpr InteractionLayers MASK_PLAYER_MOVE =
    InteractionLayers::Solid |
    InteractionLayers::Window |
    InteractionLayers::PlayerClip |
    InteractionLayers::PassBullets;

/// Movement (NPC)
constexpr InteractionLayers MASK_NPC_MOVE =
    InteractionLayers::Solid |
    InteractionLayers::Window |
    InteractionLayers::NPCClip |
    InteractionLayers::PassBullets;

struct TraceOptions
{
    uint64_t InteractsAs = 0;
    uint64_t InteractsWith = static_cast<uint64_t>(MASK_SHOT_PHYSICS);
    uint64_t InteractsExclude = 0;
};

struct TraceResult
{
    CGameTrace m_Trace{};

    TraceResult() = default;

    TraceResult(const TraceResult&) = delete;
    TraceResult& operator=(const TraceResult&) = delete;

    TraceResult(TraceResult&&) = delete;
    TraceResult& operator=(TraceResult&&) = default;

    const Vector& StartPos() const { return m_Trace.m_vStartPos; }
    const Vector& EndPos() const { return m_Trace.m_vEndPos; }
    const Vector& HitPoint() const { return m_Trace.m_vHitPoint; }
    const Vector& Normal() const { return m_Trace.m_vHitNormal; }

    float Fraction() const { return m_Trace.m_flFraction; }
    float HitOffset() const { return m_Trace.m_flHitOffset; }

    bool DidHit() const { return m_Trace.m_flFraction < 1.0f; }
    bool IsAllSolid() const { return m_Trace.m_bStartInSolid; }
    bool HasExactHit() const { return m_Trace.m_bExactHitPoint; }

    CEntityInstance* HitEntity() const { return m_Trace.m_pEnt; }

    int TriangleIndex() const { return m_Trace.m_nTriangle; }
    int HitboxBoneIndex() const { return m_Trace.m_nHitboxBoneIndex; }

    CHitBox* Hitbox() const { return const_cast<CHitBox*>(m_Trace.m_pHitbox); }

    int Contents() const { return m_Trace.m_nContents; }
    RayType_t RayType() const { return m_Trace.m_eRayType; }

    IPhysicsBody* Body() const { return m_Trace.m_hBody; }
    IPhysicsShape* Shape() const { return m_Trace.m_hShape; }

    const CTransform& BodyTransform() const { return m_Trace.m_BodyTransform; }
    const RnCollisionAttr_t& ShapeAttributes() const { return m_Trace.m_ShapeAttributes; }

    CPhysSurfaceProperties* Surface() const { return const_cast<CPhysSurfaceProperties*>(m_Trace.m_pSurfaceProperties); }
};

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
    class RayTrace {
    public:
        void InitRayTrace();
        void DestructRayTrace();
    public:
        bool TraceShape(const Vector& vecStart, const QAngle& angAngles, CEntityInstance* pIgnoreEntity, TraceOptions* pTraceOptions, CGameTrace* pGameTrace);
        bool TraceEndShape(const Vector& vecStart, const Vector& vecEnd, CEntityInstance* pIgnoreEntity, TraceOptions* pTraceOptions, CGameTrace* pGameTrace);
        bool TraceHullShape(const Vector& vecStart, const Vector& vecEnd, const Vector& vecMins, const Vector& vecMaxs, CEntityInstance* pIgnoreEntity, TraceOptions* pTraceOptions, CGameTrace* pGameTrace);
        bool TraceShapeEx(const Vector& vecStart, const Vector& vecEnd, CTraceFilter* pTraceFilter, Ray_t* pRay, CGameTrace* pGameTrace);
    protected:
        DynLibUtils::CMemory m_pCNavPhysicsInterface_TraceShape;
    protected:
        void** m_pCNavPhysicsInterfaceVTable;
    };

    extern RayTrace rayTrace;
}
