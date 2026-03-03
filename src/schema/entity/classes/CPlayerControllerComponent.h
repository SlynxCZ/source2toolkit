#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CNetworkVarChainer.h"

class CPlayerControllerComponent
{
public:
    DECLARE_SCHEMA_CLASS(CPlayerControllerComponent);

    SCHEMA_FIELD(CNetworkVarChainer, __m_pChainEntity);
};
