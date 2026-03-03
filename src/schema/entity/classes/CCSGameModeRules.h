#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>


class CCSGameModeRules
{
public:
    DECLARE_SCHEMA_CLASS(CCSGameModeRules);

    SCHEMA_FIELD(CEntityInstance*, __m_pChainEntity);
};
