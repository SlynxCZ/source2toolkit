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

#include "CFuncPlat.h"

class CFuncPlatRot : public CFuncPlat, public CBaseEntity::Factory<CFuncPlatRot>
{
public:
    DECLARE_SCHEMA_CLASS(CFuncPlatRot);

    SCHEMA_FIELD(QAngle, m_end);
    SCHEMA_FIELD(QAngle, m_start);
};
