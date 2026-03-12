#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "vector.h"
#include "utlsymbol.h"
#include "utlsymbollarge.h"
#include "utlstring.h"
#include "utlstringtoken.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CModelPointEntity.h"

class CPlayerSprayDecal : public CModelPointEntity, public CBaseEntity::Factory<CPlayerSprayDecal>
{
public:
    DECLARE_SCHEMA_CLASS(CPlayerSprayDecal);

    SCHEMA_FIELD(int32_t, m_nUniqueID);
    SCHEMA_FIELD(uint32_t, m_unAccountID);
    SCHEMA_FIELD(uint32_t, m_unTraceID);
    SCHEMA_FIELD(uint32_t, m_rtGcTime);
    SCHEMA_FIELD(Vector, m_vecEndPos);
    SCHEMA_FIELD(Vector, m_vecStart);
    SCHEMA_FIELD(Vector, m_vecLeft);
    SCHEMA_FIELD(Vector, m_vecNormal);
    SCHEMA_FIELD(int32_t, m_nPlayer);
    SCHEMA_FIELD(int32_t, m_nEntity);
    SCHEMA_FIELD(int32_t, m_nHitbox);
    SCHEMA_FIELD(float, m_flCreationTime);
    SCHEMA_FIELD(int32_t, m_nTintID);
    SCHEMA_FIELD(uint8_t, m_nVersion);
    SCHEMA_FIELD_POINTER(uint8_t, m_ubSignature);
};
