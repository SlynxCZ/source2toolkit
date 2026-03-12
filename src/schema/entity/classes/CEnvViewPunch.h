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

class CEnvViewPunch : public CPointEntity, public CBaseEntity::Factory<CEnvViewPunch>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvViewPunch);

    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(QAngle, m_angViewPunch);
};
