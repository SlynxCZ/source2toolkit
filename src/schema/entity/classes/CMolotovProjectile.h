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

#include "CBaseCSGrenadeProjectile.h"
#include "IntervalTimer.h"

class CMolotovProjectile : public CBaseCSGrenadeProjectile, public CBaseEntity::Factory<CMolotovProjectile>
{
public:
    DECLARE_SCHEMA_CLASS(CMolotovProjectile);

    SCHEMA_FIELD(bool, m_bIsIncGrenade);
    SCHEMA_FIELD(bool, m_bDetonated);
    SCHEMA_FIELD(IntervalTimer, m_stillTimer);
};
