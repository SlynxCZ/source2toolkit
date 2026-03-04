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

class CPhysBallSocket : public CPhysConstraint
{
public:
    DECLARE_SCHEMA_CLASS(CPhysBallSocket);

    SCHEMA_FIELD(float, m_flJointFriction);
    SCHEMA_FIELD(bool, m_bEnableSwingLimit);
    SCHEMA_FIELD(float, m_flSwingLimit);
    SCHEMA_FIELD(bool, m_bEnableTwistLimit);
    SCHEMA_FIELD(float, m_flMinTwistAngle);
    SCHEMA_FIELD(float, m_flMaxTwistAngle);
};
