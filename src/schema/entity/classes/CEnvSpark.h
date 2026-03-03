#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CEnvSpark : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvSpark);

    SCHEMA_FIELD(float, m_flDelay);
    SCHEMA_FIELD(int32_t, m_nMagnitude);
    SCHEMA_FIELD(int32_t, m_nTrailLength);
    SCHEMA_FIELD(int32_t, m_nType);
    SCHEMA_FIELD(CEntityIOOutput, m_OnSpark);
};
