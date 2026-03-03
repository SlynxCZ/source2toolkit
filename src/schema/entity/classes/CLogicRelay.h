#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CLogicRelay : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicRelay);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(bool, m_bWaitForRefire);
    SCHEMA_FIELD(bool, m_bTriggerOnce);
    SCHEMA_FIELD(bool, m_bFastRetrigger);
    SCHEMA_FIELD(bool, m_bPassthoughCaller);
};
