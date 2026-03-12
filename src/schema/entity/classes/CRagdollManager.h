#pragma once
#include "CBaseEntity.h"
#include "igameevents.h"
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

#include "CBaseEntity.h"

class CRagdollManager : public CBaseEntity, public CBaseEntity::Factory<CRagdollManager>
{
public:
    DECLARE_SCHEMA_CLASS(CRagdollManager);

    SCHEMA_FIELD(int8_t, m_iCurrentMaxRagdollCount);
    SCHEMA_FIELD(int32_t, m_iMaxRagdollCount);
    SCHEMA_FIELD(bool, m_bSaveImportant);
    SCHEMA_FIELD(bool, m_bCanTakeDamage);
};
