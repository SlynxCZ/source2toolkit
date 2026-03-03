#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CBaseClientUIEntity : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CBaseClientUIEntity);

    SCHEMA_FIELD(bool, m_bEnabled);
    SCHEMA_FIELD(CUtlSymbolLarge, m_DialogXMLName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_PanelClassName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_PanelID);
};
