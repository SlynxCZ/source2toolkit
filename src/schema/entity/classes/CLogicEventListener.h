#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CLogicEventListener : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicEventListener);

    SCHEMA_FIELD(CUtlString, m_strEventName);
    SCHEMA_FIELD(bool, m_bIsEnabled);
    SCHEMA_FIELD(int32_t, m_nTeam);
};
