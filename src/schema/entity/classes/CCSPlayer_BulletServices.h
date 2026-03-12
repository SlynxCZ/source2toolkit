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

class CCSPlayer_BulletServices : public CPlayerPawnComponent, public CBaseEntity::Factory<CCSPlayer_BulletServices>
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayer_BulletServices);

    SCHEMA_FIELD(int32_t, m_totalHitsOnServer);
};
