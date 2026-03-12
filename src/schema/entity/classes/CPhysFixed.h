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

#include "CPhysConstraint.h"

class CPhysFixed : public CPhysConstraint, public CBaseEntity::Factory<CPhysFixed>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysFixed);

    SCHEMA_FIELD(float, m_flLinearFrequency);
    SCHEMA_FIELD(float, m_flLinearDampingRatio);
    SCHEMA_FIELD(float, m_flAngularFrequency);
    SCHEMA_FIELD(float, m_flAngularDampingRatio);
    SCHEMA_FIELD(bool, m_bEnableLinearConstraint);
    SCHEMA_FIELD(bool, m_bEnableAngularConstraint);
    SCHEMA_FIELD(CUtlSymbolLarge, m_sBoneName1);
    SCHEMA_FIELD(CUtlSymbolLarge, m_sBoneName2);
};
