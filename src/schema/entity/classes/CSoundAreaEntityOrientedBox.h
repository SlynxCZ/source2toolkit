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

#include "CSoundAreaEntityBase.h"

class CSoundAreaEntityOrientedBox : public CSoundAreaEntityBase, public CBaseEntity::Factory<CSoundAreaEntityOrientedBox>
{
public:
    DECLARE_SCHEMA_CLASS(CSoundAreaEntityOrientedBox);

    SCHEMA_FIELD(Vector, m_vMin);
    SCHEMA_FIELD(Vector, m_vMax);
};
