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

#include "../enums/BloodType.h"
#include "CPointEntity.h"

class CBlood : public CPointEntity, public CBaseEntity::Factory<CBlood>
{
public:
    DECLARE_SCHEMA_CLASS(CBlood);

    SCHEMA_FIELD(QAngle, m_vecSprayAngles);
    SCHEMA_FIELD(Vector, m_vecSprayDir);
    SCHEMA_FIELD(float, m_flAmount);
    SCHEMA_FIELD(BloodType, m_Color);
};
