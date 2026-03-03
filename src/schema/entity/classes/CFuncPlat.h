#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBasePlatTrain.h"

class CFuncPlat : public CBasePlatTrain
{
public:
    DECLARE_SCHEMA_CLASS(CFuncPlat);

    SCHEMA_FIELD(CUtlSymbolLarge, m_sNoise);
};
