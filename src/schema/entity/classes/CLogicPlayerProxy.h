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

#include "CLogicalEntity.h"

class CBaseEntity;

class CLogicPlayerProxy : public CLogicalEntity, public CBaseEntity::Factory<CLogicPlayerProxy>
{
public:
    DECLARE_SCHEMA_CLASS(CLogicPlayerProxy);

    SCHEMA_FIELD(CEntityIOOutput, m_PlayerHasAmmo);
    SCHEMA_FIELD(CEntityIOOutput, m_PlayerHasNoAmmo);
    SCHEMA_FIELD(CEntityIOOutput, m_PlayerDied);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hPlayer);
};
