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

#include "CLogicalEntity.h"

class CBaseEntity;

class CLogicLineToEntity : public CLogicalEntity, public CBaseEntity::Factory<CLogicLineToEntity>
{
public:
    DECLARE_SCHEMA_CLASS(CLogicLineToEntity);

    SCHEMA_FIELD(CUtlSymbolLarge, m_SourceName);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_StartEntity);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_EndEntity);
};
