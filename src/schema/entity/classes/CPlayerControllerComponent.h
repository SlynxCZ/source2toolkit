#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>


class CPlayerControllerComponent
{
public:
    DECLARE_SCHEMA_CLASS(CPlayerControllerComponent);

    SCHEMA_FIELD(CEntityInstance*, __m_pChainEntity);
};
