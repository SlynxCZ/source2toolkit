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

#include "CEnvSoundscape.h"

class CEnvSoundscapeAlias_snd_soundscape : public CEnvSoundscape, public CBaseEntity::Factory<CEnvSoundscapeAlias_snd_soundscape>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvSoundscapeAlias_snd_soundscape);

};
