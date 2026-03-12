#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "vector.h"
#include "utlsymbol.h"
#include "utlsymbollarge.h"
#include "utlstring.h"
#include "utlstringtoken.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CNavHullPresetVData : public CBaseEntity::Factory<CNavHullPresetVData>
{
public:
    DECLARE_SCHEMA_CLASS(CNavHullPresetVData);

    SCHEMA_FIELD(CUtlVector<CUtlString>, m_vecNavHulls);
};
