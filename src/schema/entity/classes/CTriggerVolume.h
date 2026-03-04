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

#include "CBaseModelEntity.h"

class CBaseFilter;

class CTriggerVolume : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerVolume);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iFilterName);
    SCHEMA_FIELD(CHandle<CBaseFilter>, m_hFilter);
};
