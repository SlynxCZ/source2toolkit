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

#include "CPlayerPawnComponent.h"

class CBaseEntity;

class CCSPlayer_HostageServices : public CPlayerPawnComponent, public CBaseEntity::Factory<CCSPlayer_HostageServices>
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayer_HostageServices);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hCarriedHostage);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hCarriedHostageProp);
};
