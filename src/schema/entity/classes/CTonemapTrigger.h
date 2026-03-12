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

#include "CBaseTrigger.h"

class CTonemapTrigger : public CBaseTrigger, public CBaseEntity::Factory<CTonemapTrigger>
{
public:
    DECLARE_SCHEMA_CLASS(CTonemapTrigger);

    SCHEMA_FIELD(CUtlSymbolLarge, m_tonemapControllerName);
    SCHEMA_FIELD(CEntityHandle, m_hTonemapController);
};
