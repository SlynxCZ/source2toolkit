#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CEnvEntityIgniter : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvEntityIgniter);

    SCHEMA_FIELD(float, m_flLifetime);
};
