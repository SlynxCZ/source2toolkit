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

#include "../enums/BrushSolidities_e.h"
#include "CBaseModelEntity.h"

class CFuncBrush : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFuncBrush);

    SCHEMA_FIELD(BrushSolidities_e, m_iSolidity);
    SCHEMA_FIELD(int32_t, m_iDisabled);
    SCHEMA_FIELD(bool, m_bSolidBsp);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszExcludedClass);
    SCHEMA_FIELD(bool, m_bInvertExclusion);
    SCHEMA_FIELD(bool, m_bScriptedMovement);
};
