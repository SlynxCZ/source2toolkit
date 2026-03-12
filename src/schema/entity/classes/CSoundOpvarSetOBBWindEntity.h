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

#include "CSoundOpvarSetPointBase.h"

class CSoundOpvarSetOBBWindEntity : public CSoundOpvarSetPointBase, public CBaseEntity::Factory<CSoundOpvarSetOBBWindEntity>
{
public:
    DECLARE_SCHEMA_CLASS(CSoundOpvarSetOBBWindEntity);

    SCHEMA_FIELD(Vector, m_vMins);
    SCHEMA_FIELD(Vector, m_vMaxs);
    SCHEMA_FIELD(Vector, m_vDistanceMins);
    SCHEMA_FIELD(Vector, m_vDistanceMaxs);
    SCHEMA_FIELD(float, m_flWindMin);
    SCHEMA_FIELD(float, m_flWindMax);
    SCHEMA_FIELD(float, m_flWindMapMin);
    SCHEMA_FIELD(float, m_flWindMapMax);
};
