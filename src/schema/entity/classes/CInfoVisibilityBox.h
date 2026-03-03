#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CInfoVisibilityBox : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CInfoVisibilityBox);

    SCHEMA_FIELD(int32_t, m_nMode);
    SCHEMA_FIELD(Vector, m_vBoxSize);
    SCHEMA_FIELD(bool, m_bEnabled);
};
