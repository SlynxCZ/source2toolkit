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

#include "CPointEntity.h"

class CPointBroadcastClientCommand : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointBroadcastClientCommand);


public:
    static CPointBroadcastClientCommand* New(const char* className)
    {
        return CBaseEntity::New<CPointBroadcastClientCommand>(className);
    }
};
