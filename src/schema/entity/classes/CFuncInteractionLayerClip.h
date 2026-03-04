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

class CFuncInteractionLayerClip : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFuncInteractionLayerClip);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszInteractsAs);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszInteractsWith);
};
