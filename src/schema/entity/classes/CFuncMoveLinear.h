#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseToggle.h"
#include "../enums/MoveLinearAuthoredPos_t.h"

class CFuncMoveLinear : public CBaseToggle
{
public:
    DECLARE_SCHEMA_CLASS(CFuncMoveLinear);

    SCHEMA_FIELD(MoveLinearAuthoredPos_t, m_authoredPosition);
    SCHEMA_FIELD(QAngle, m_angMoveEntitySpace);
    SCHEMA_FIELD(Vector, m_vecMoveDirParentSpace);
    SCHEMA_FIELD(CUtlSymbolLarge, m_soundStart);
    SCHEMA_FIELD(CUtlSymbolLarge, m_soundStop);
    SCHEMA_FIELD(CUtlSymbolLarge, m_currentSound);
    SCHEMA_FIELD(float, m_flBlockDamage);
    SCHEMA_FIELD(float, m_flStartPosition);
    SCHEMA_FIELD(CEntityIOOutput, m_OnFullyOpen);
    SCHEMA_FIELD(CEntityIOOutput, m_OnFullyClosed);
    SCHEMA_FIELD(bool, m_bCreateMovableNavMesh);
    SCHEMA_FIELD(bool, m_bAllowMovableNavMeshDockingOnEntireEntity);
    SCHEMA_FIELD(bool, m_bCreateNavObstacle);
};
