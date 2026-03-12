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

#include "CEnvSoundscape.h"

class CEnvSoundscapeProxy : public CEnvSoundscape, public CBaseEntity::Factory<CEnvSoundscapeProxy>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvSoundscapeProxy);

    SCHEMA_FIELD(CUtlSymbolLarge, m_MainSoundscapeName);
};
