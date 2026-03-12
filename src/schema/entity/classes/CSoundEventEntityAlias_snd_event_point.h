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

#include "CSoundEventEntity.h"

class CSoundEventEntityAlias_snd_event_point : public CSoundEventEntity, public CBaseEntity::Factory<CSoundEventEntityAlias_snd_event_point>
{
public:
    DECLARE_SCHEMA_CLASS(CSoundEventEntityAlias_snd_event_point);

};
