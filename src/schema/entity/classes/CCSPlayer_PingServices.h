#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPlayerPawnComponent.h"

class CPlayerPing;

class CCSPlayer_PingServices : public CPlayerPawnComponent
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayer_PingServices);

    SCHEMA_FIELD_POINTER(float, m_flPlayerPingTokens);
    SCHEMA_FIELD(CHandle<CPlayerPing>, m_hPlayerPing);
};
