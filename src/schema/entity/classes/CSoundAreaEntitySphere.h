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

#include "CSoundAreaEntityBase.h"

class CSoundAreaEntitySphere : public CSoundAreaEntityBase, public CBaseEntity::Factory<CSoundAreaEntitySphere>
{
public:
    DECLARE_SCHEMA_CLASS(CSoundAreaEntitySphere);

    SCHEMA_FIELD(float, m_flRadius);
};
