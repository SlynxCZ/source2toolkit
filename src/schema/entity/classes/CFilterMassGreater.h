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

#include "CBaseFilter.h"

class CFilterMassGreater : public CBaseFilter, public CBaseEntity::Factory<CFilterMassGreater>
{
public:
    DECLARE_SCHEMA_CLASS(CFilterMassGreater);

    SCHEMA_FIELD(float, m_fFilterMass);
};
