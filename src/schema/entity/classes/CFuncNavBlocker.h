#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CFuncNavBlocker : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFuncNavBlocker);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(int32_t, m_nBlockedTeamNumber);
};
