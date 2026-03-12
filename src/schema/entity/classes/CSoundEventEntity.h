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

class CSoundEventEntity : public CBaseEntity, public CBaseEntity::Factory<CSoundEventEntity>
{
public:
    DECLARE_SCHEMA_CLASS(CSoundEventEntity);

    SCHEMA_FIELD(bool, m_bStartOnSpawn);
    SCHEMA_FIELD(bool, m_bToLocalPlayer);
    SCHEMA_FIELD(bool, m_bStopOnNew);
    SCHEMA_FIELD(bool, m_bSaveRestore);
    SCHEMA_FIELD(bool, m_bSavedIsPlaying);
    SCHEMA_FIELD(float, m_flSavedElapsedTime);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszSourceEntityName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszAttachmentName);
    SCHEMA_FIELD(CEntityIOOutput, m_onSoundFinished);
    SCHEMA_FIELD(float, m_flClientCullRadius);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszSoundName);
    SCHEMA_FIELD(CEntityHandle, m_hSource);
    SCHEMA_FIELD(int32_t, m_nEntityIndexSelection);
};
