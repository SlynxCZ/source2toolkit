#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CTriggerMultiple.h"

class CScriptTriggerMultiple : public CTriggerMultiple
{
public:
    DECLARE_SCHEMA_CLASS(CScriptTriggerMultiple);

    SCHEMA_FIELD(Vector, m_vExtent);
};
