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

class CNetworkVelocityVector : public CBaseEntity::Factory<CNetworkVelocityVector>
{
public:
    DECLARE_SCHEMA_CLASS(CNetworkVelocityVector);

    SCHEMA_FIELD(float, m_vecX);
    SCHEMA_FIELD(float, m_vecY);
    SCHEMA_FIELD(float, m_vecZ);
};
