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

#include "CBaseEntity.h"

class CAI_ChangeHintGroup : public CBaseEntity, public CBaseEntity::Factory<CAI_ChangeHintGroup>
{
public:
    DECLARE_SCHEMA_CLASS(CAI_ChangeHintGroup);

    SCHEMA_FIELD(int32_t, m_iSearchType);
    SCHEMA_FIELD(CUtlSymbolLarge, m_strSearchName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_strNewHintGroup);
    SCHEMA_FIELD(float, m_flRadius);
};
