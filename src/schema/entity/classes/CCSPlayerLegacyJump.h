#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CCSPlayerLegacyJump
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayerLegacyJump);

    SCHEMA_FIELD(bool, m_bOldJumpPressed);
    SCHEMA_FIELD(float, m_flJumpPressedTime);
};
