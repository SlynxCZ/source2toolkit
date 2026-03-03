#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"
#include "CEnvWindShared.h"

class CEnvWind : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvWind);

    SCHEMA_FIELD(CEnvWindShared, m_EnvWindShared);
};
