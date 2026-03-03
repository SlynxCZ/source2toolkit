#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CNetworkVarChainer.h"

class CPlayerPawnComponent
{
public:
    DECLARE_SCHEMA_CLASS(CPlayerPawnComponent);

    SCHEMA_FIELD(CNetworkVarChainer, __m_pChainEntity);
};
