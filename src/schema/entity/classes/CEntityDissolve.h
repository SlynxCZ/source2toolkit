#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"
#include "../enums/EntityDisolveType_t.h"

class CEntityDissolve : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEntityDissolve);

    SCHEMA_FIELD(float, m_flFadeInStart);
    SCHEMA_FIELD(float, m_flFadeInLength);
    SCHEMA_FIELD(float, m_flFadeOutModelStart);
    SCHEMA_FIELD(float, m_flFadeOutModelLength);
    SCHEMA_FIELD(float, m_flFadeOutStart);
    SCHEMA_FIELD(float, m_flFadeOutLength);
    SCHEMA_FIELD(float, m_flStartTime);
    SCHEMA_FIELD(EntityDisolveType_t, m_nDissolveType);
    SCHEMA_FIELD(Vector, m_vDissolverOrigin);
    SCHEMA_FIELD(uint32_t, m_nMagnitude);
};
