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

#include "AutoRoomDoorwayPairs_t.h"
#include "CSoundOpvarSetPointEntity.h"
#include "SoundOpvarTraceResult_t.h"

class CSoundOpvarSetAutoRoomEntity : public CSoundOpvarSetPointEntity, public CBaseEntity::Factory<CSoundOpvarSetAutoRoomEntity>
{
public:
    DECLARE_SCHEMA_CLASS(CSoundOpvarSetAutoRoomEntity);

    SCHEMA_FIELD(CUtlVector<SoundOpvarTraceResult_t>, m_traceResults);
    SCHEMA_FIELD(CUtlVector<AutoRoomDoorwayPairs_t>, m_doorwayPairs);
    SCHEMA_FIELD(float, m_flSize);
    SCHEMA_FIELD(float, m_flHeightTolerance);
    SCHEMA_FIELD(float, m_flSizeSqr);
};
