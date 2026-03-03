#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CBasePlayerPawn;
class CEnvSoundscapeTriggerable;

class CTriggerSoundscape : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerSoundscape);

    SCHEMA_FIELD(CHandle<CEnvSoundscapeTriggerable>, m_hSoundscape);
    SCHEMA_FIELD(CUtlSymbolLarge, m_SoundscapeName);
    SCHEMA_FIELD(CUtlVector<CHandle<CBasePlayerPawn>>, m_spectators);
};
