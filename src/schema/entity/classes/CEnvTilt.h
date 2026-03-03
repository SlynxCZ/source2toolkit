#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CEnvTilt : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvTilt);

    SCHEMA_FIELD(float, m_Duration);
    SCHEMA_FIELD(float, m_Radius);
    SCHEMA_FIELD(float, m_TiltTime);
    SCHEMA_FIELD(float, m_stopTime);
};
