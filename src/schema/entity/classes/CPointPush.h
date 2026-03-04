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

#include "CPointEntity.h"

class CBaseFilter;

class CPointPush : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointPush);

    SCHEMA_FIELD(bool, m_bEnabled);
    SCHEMA_FIELD(float, m_flMagnitude);
    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(float, m_flInnerRadius);
    SCHEMA_FIELD(float, m_flConeOfInfluence);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszFilterName);
    SCHEMA_FIELD(CHandle<CBaseFilter>, m_hFilter);
};
