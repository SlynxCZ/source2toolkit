#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CNavHullPresetVData
{
public:
    DECLARE_SCHEMA_CLASS(CNavHullPresetVData);

    SCHEMA_FIELD(CUtlVector<CUtlString>, m_vecNavHulls);
};
