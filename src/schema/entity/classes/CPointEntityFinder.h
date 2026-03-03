#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"
#include "../enums/EntFinderMethod_t.h"

class CBaseFilter;

class CPointEntityFinder : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointEntityFinder);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hEntity);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iFilterName);
    SCHEMA_FIELD(CHandle<CBaseFilter>, m_hFilter);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iRefName);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hReference);
    SCHEMA_FIELD(EntFinderMethod_t, m_FindMethod);
    SCHEMA_FIELD(CEntityIOOutput, m_OnFoundEntity);
};
