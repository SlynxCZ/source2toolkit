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

#include "CEnvSoundscapeProxy.h"

class CEnvSoundscapeProxyAlias_snd_soundscape_proxy : public CEnvSoundscapeProxy, public CBaseEntity::Factory<CEnvSoundscapeProxyAlias_snd_soundscape_proxy>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvSoundscapeProxyAlias_snd_soundscape_proxy);

};
