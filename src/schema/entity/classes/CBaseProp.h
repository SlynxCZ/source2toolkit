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

class CBaseProp : public CBaseAnimGraph
{
public:
    DECLARE_SCHEMA_CLASS(CBaseProp);

    SCHEMA_FIELD(bool, m_bModelOverrodeBlockLOS);
    SCHEMA_FIELD(int32_t, m_iShapeType);
    SCHEMA_FIELD(bool, m_bConformToCollisionBounds);
    SCHEMA_FIELD(CTransform, m_mPreferredCatchTransform);
};
