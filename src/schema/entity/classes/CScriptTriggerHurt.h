#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CTriggerHurt.h"

class CScriptTriggerHurt : public CTriggerHurt
{
public:
    DECLARE_SCHEMA_CLASS(CScriptTriggerHurt);

    SCHEMA_FIELD(Vector, m_vExtent);
};
