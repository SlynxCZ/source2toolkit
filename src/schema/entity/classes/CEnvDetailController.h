#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CEnvDetailController : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvDetailController);

    SCHEMA_FIELD(float, m_flFadeStartDist);
    SCHEMA_FIELD(float, m_flFadeEndDist);
};
