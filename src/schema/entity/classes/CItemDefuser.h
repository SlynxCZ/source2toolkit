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

#include "CItem.h"
#include "EntitySpottedState_t.h"

class CItemDefuser : public CItem, public CBaseEntity::Factory<CItemDefuser>
{
public:
    DECLARE_SCHEMA_CLASS(CItemDefuser);

    SCHEMA_FIELD(EntitySpottedState_t, m_entitySpottedState);
    SCHEMA_FIELD(int32_t, m_nSpotRules);
};
