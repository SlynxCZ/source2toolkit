#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPropDoorRotating.h"

class CPropDoorRotatingBreakable : public CPropDoorRotating
{
public:
    DECLARE_SCHEMA_CLASS(CPropDoorRotatingBreakable);

    SCHEMA_FIELD(bool, m_bBreakable);
    SCHEMA_FIELD(bool, m_isAbleToCloseAreaPortals);
    SCHEMA_FIELD(int32_t, m_currentDamageState);
    SCHEMA_FIELD(CUtlVector<CUtlSymbolLarge>, m_damageStates);
};
