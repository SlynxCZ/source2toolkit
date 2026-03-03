#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CBaseEntity;

class CFuncConveyor : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFuncConveyor);

    SCHEMA_FIELD(CUtlSymbolLarge, m_szConveyorModels);
    SCHEMA_FIELD(float, m_flTransitionDurationSeconds);
    SCHEMA_FIELD(QAngle, m_angMoveEntitySpace);
    SCHEMA_FIELD(Vector, m_vecMoveDirEntitySpace);
    SCHEMA_FIELD(float, m_flTargetSpeed);
    SCHEMA_FIELD(int32_t, m_nTransitionStartTick);
    SCHEMA_FIELD(int32_t, m_nTransitionDurationTicks);
    SCHEMA_FIELD(float, m_flTransitionStartSpeed);
    SCHEMA_FIELD(CUtlVector<CHandle<CBaseEntity>>, m_hConveyorModels);
};
