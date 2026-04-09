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

#include "SpawnPoint.h"

class CInfoPlayerTerrorist : public SpawnPoint
{
public:
    DECLARE_SCHEMA_CLASS(CInfoPlayerTerrorist);


public:
    static CInfoPlayerTerrorist* New(const char* className)
    {
        return CBaseEntity::New<CInfoPlayerTerrorist>(className);
    }
};
