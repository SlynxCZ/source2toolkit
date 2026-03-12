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

#include "CEnvSoundscapeTriggerable.h"

class CEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable : public CEnvSoundscapeTriggerable, public CBaseEntity::Factory<CEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable);

};
