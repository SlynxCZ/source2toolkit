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

#include "CPlayerControllerComponent.h"

class CCSPlayerController_InGameMoneyServices : public CPlayerControllerComponent, public CBaseEntity::Factory<CCSPlayerController_InGameMoneyServices>
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayerController_InGameMoneyServices);

    SCHEMA_FIELD(bool, m_bReceivesMoneyNextRound);
    SCHEMA_FIELD(int32_t, m_iMoneyEarnedForNextRound);
    SCHEMA_FIELD(int32_t, m_iAccount);
    SCHEMA_FIELD(int32_t, m_iStartAccount);
    SCHEMA_FIELD(int32_t, m_iTotalCashSpent);
    SCHEMA_FIELD(int32_t, m_iCashSpentThisRound);
};
