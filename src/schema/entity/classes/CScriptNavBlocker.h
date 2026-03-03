#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CFuncNavBlocker.h"

class CScriptNavBlocker : public CFuncNavBlocker
{
public:
    DECLARE_SCHEMA_CLASS(CScriptNavBlocker);

    SCHEMA_FIELD(Vector, m_vExtent);
};
