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

#include "CBaseAnimGraph.h"

class CConstraintAnchor : public CBaseAnimGraph, public CBaseEntity::Factory<CConstraintAnchor>
{
public:
    DECLARE_SCHEMA_CLASS(CConstraintAnchor);

    SCHEMA_FIELD(float, m_massScale);
};
