#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CTriggerOnce.h"

class CScriptTriggerOnce : public CTriggerOnce
{
public:
    DECLARE_SCHEMA_CLASS(CScriptTriggerOnce);

    SCHEMA_FIELD(Vector, m_vExtent);
};
