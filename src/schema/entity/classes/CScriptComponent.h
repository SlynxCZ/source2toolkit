#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CEntityComponent.h"

class CScriptComponent : public CEntityComponent
{
public:
    DECLARE_SCHEMA_CLASS(CScriptComponent);

    SCHEMA_FIELD(CUtlSymbolLarge, m_scriptClassName);
};
