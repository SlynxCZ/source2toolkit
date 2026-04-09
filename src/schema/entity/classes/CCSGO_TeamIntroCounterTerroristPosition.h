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

#include "CCSGO_TeamIntroCharacterPosition.h"

class CCSGO_TeamIntroCounterTerroristPosition : public CCSGO_TeamIntroCharacterPosition
{
public:
    DECLARE_SCHEMA_CLASS(CCSGO_TeamIntroCounterTerroristPosition);


public:
    static CCSGO_TeamIntroCounterTerroristPosition* New(const char* className)
    {
        return CBaseEntity::New<CCSGO_TeamIntroCounterTerroristPosition>(className);
    }
};
