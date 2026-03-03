#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CEnvSoundscape : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvSoundscape);

    SCHEMA_FIELD(CEntityIOOutput, m_OnPlay);
    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(CUtlSymbolLarge, m_soundEventName);
    SCHEMA_FIELD(bool, m_bOverrideWithEvent);
    SCHEMA_FIELD(int32_t, m_soundscapeIndex);
    SCHEMA_FIELD(int32_t, m_soundscapeEntityListId);
    SCHEMA_FIELD_POINTER(CUtlSymbolLarge, m_positionNames);
    SCHEMA_FIELD(CHandle<CEnvSoundscape>, m_hProxySoundscape);
    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(CUtlSymbolLarge, m_soundscapeName);
    SCHEMA_FIELD(uint32_t, m_soundEventHash);
};
