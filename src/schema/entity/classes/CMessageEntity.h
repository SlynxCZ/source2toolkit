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

#include "CPointEntity.h"

class CMessageEntity : public CPointEntity, public CBaseEntity::Factory<CMessageEntity>
{
public:
    DECLARE_SCHEMA_CLASS(CMessageEntity);

    SCHEMA_FIELD(int32_t, m_radius);
    SCHEMA_FIELD(CUtlSymbolLarge, m_messageText);
    SCHEMA_FIELD(bool, m_drawText);
    SCHEMA_FIELD(bool, m_bDeveloperOnly);
    SCHEMA_FIELD(bool, m_bEnabled);
};
