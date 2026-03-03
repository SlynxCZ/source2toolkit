#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CPathCorner : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPathCorner);

    SCHEMA_FIELD(float, m_flWait);
    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPass);
};
