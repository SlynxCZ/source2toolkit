#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CMapSharedEnvironment : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CMapSharedEnvironment);

    SCHEMA_FIELD(CUtlSymbolLarge, m_targetMapName);
};
