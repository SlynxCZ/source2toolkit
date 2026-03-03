#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CBaseFilter : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CBaseFilter);

    SCHEMA_FIELD(bool, m_bNegated);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPass);
    SCHEMA_FIELD(CEntityIOOutput, m_OnFail);
};
