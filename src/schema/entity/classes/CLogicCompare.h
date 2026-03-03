#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CLogicCompare : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicCompare);

    SCHEMA_FIELD(float, m_flInValue);
    SCHEMA_FIELD(float, m_flCompareValue);
};
