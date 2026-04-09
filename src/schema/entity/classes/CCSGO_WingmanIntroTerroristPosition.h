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

#include "CCSGO_WingmanIntroCharacterPosition.h"

class CCSGO_WingmanIntroTerroristPosition : public CCSGO_WingmanIntroCharacterPosition
{
public:
    DECLARE_SCHEMA_CLASS(CCSGO_WingmanIntroTerroristPosition);


public:
    static CCSGO_WingmanIntroTerroristPosition* New(const char* className)
    {
        return CBaseEntity::New<CCSGO_WingmanIntroTerroristPosition>(className);
    }
};
