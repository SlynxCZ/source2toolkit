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

class CCredits : public CPointEntity, public CBaseEntity::Factory<CCredits>
{
public:
    DECLARE_SCHEMA_CLASS(CCredits);

    SCHEMA_FIELD(CEntityIOOutput, m_OnCreditsDone);
    SCHEMA_FIELD(bool, m_bRolledOutroCredits);
    SCHEMA_FIELD(float, m_flLogoLength);
};
