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

#include "CRulePointEntity.h"

class CGameMoney : public CRulePointEntity, public CBaseEntity::Factory<CGameMoney>
{
public:
    DECLARE_SCHEMA_CLASS(CGameMoney);

    SCHEMA_FIELD(CEntityIOOutput, m_OnMoneySpent);
    SCHEMA_FIELD(CEntityIOOutput, m_OnMoneySpentFail);
    SCHEMA_FIELD(int32_t, m_nMoney);
    SCHEMA_FIELD(CUtlString, m_strAwardText);
};
