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

#include "CBaseToggle.h"

class CBasePlatTrain : public CBaseToggle
{
public:
    DECLARE_SCHEMA_CLASS(CBasePlatTrain);

    SCHEMA_FIELD(CUtlSymbolLarge, m_NoiseMoving);
    SCHEMA_FIELD(CUtlSymbolLarge, m_NoiseArrived);
    SCHEMA_FIELD(float, m_volume);
    SCHEMA_FIELD(float, m_flTWidth);
    SCHEMA_FIELD(float, m_flTLength);
};
