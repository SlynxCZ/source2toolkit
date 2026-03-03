#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseAnimGraph.h"

class CConstraintAnchor : public CBaseAnimGraph
{
public:
    DECLARE_SCHEMA_CLASS(CConstraintAnchor);

    SCHEMA_FIELD(float, m_massScale);
};
