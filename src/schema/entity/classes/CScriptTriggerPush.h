#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CTriggerPush.h"

class CScriptTriggerPush : public CTriggerPush
{
public:
    DECLARE_SCHEMA_CLASS(CScriptTriggerPush);

    SCHEMA_FIELD(Vector, m_vExtent);
};
