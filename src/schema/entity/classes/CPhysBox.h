#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBreakable.h"
#include "../enums/HoverPoseFlags_t.h"

class CBasePlayerPawn;

class CPhysBox : public CBreakable
{
public:
    DECLARE_SCHEMA_CLASS(CPhysBox);

    SCHEMA_FIELD(int32_t, m_damageType);
    SCHEMA_FIELD(int32_t, m_damageToEnableMotion);
    SCHEMA_FIELD(float, m_flForceToEnableMotion);
    SCHEMA_FIELD(Vector, m_vHoverPosePosition);
    SCHEMA_FIELD(QAngle, m_angHoverPoseAngles);
    SCHEMA_FIELD(bool, m_bNotSolidToWorld);
    SCHEMA_FIELD(bool, m_bEnableUseOutput);
    SCHEMA_FIELD(HoverPoseFlags_t, m_nHoverPoseFlags);
    SCHEMA_FIELD(float, m_flTouchOutputPerEntityDelay);
    SCHEMA_FIELD(CEntityIOOutput, m_OnDamaged);
    SCHEMA_FIELD(CEntityIOOutput, m_OnAwakened);
    SCHEMA_FIELD(CEntityIOOutput, m_OnMotionEnabled);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPlayerUse);
    SCHEMA_FIELD(CEntityIOOutput, m_OnStartTouch);
    SCHEMA_FIELD(CHandle<CBasePlayerPawn>, m_hCarryingPlayer);
};
