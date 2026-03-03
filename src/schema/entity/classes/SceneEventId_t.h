#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class SceneEventId_t
{
public:
    DECLARE_SCHEMA_CLASS(SceneEventId_t);

    SCHEMA_FIELD(uint32_t, m_Value);
};
