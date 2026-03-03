#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CNetworkTransmitComponent
{
public:
    DECLARE_SCHEMA_CLASS(CNetworkTransmitComponent);

    SCHEMA_FIELD(uint8_t, m_nTransmitStateOwnedCounter);
};
