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

#include "CGameRulesProxy.h"

class CCSGameRules;

class CCSGameRulesProxy : public CGameRulesProxy
{
public:
    DECLARE_SCHEMA_CLASS(CCSGameRulesProxy);

    SCHEMA_FIELD(CCSGameRules*, m_pGameRules);

public:
    static CCSGameRulesProxy* New(const char* className)
    {
        return CBaseEntity::New<CCSGameRulesProxy>(className);
    }
};
