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

#include "CGameRulesProxy.h"

class CCSGameRules;

class CCSGameRulesProxy : public CGameRulesProxy, public CBaseEntity::Factory<CCSGameRulesProxy>
{
public:
    DECLARE_SCHEMA_CLASS(CCSGameRulesProxy);

    SCHEMA_FIELD(CCSGameRules*, m_pGameRules);
};
