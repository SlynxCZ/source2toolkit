#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CInButtonState
{
public:
    DECLARE_SCHEMA_CLASS(CInButtonState);

    SCHEMA_FIELD_POINTER(uint64_t, m_pButtonStates);
};
