#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CEnvSplash : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvSplash);

    SCHEMA_FIELD(float, m_flScale);
};
