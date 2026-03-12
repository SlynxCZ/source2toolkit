#pragma once
#include "CBaseEntity.h"
#include "igameevents.h"
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

#include "CSoundOpvarSetPointEntity.h"

class CSoundOpvarSetPathCornerEntity : public CSoundOpvarSetPointEntity, public CBaseEntity::Factory<CSoundOpvarSetPathCornerEntity>
{
public:
    DECLARE_SCHEMA_CLASS(CSoundOpvarSetPathCornerEntity);

    SCHEMA_FIELD(bool, m_bUseParentedPath);
    SCHEMA_FIELD(float, m_flDistMinSqr);
    SCHEMA_FIELD(float, m_flDistMaxSqr);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszPathCornerEntityName);
};
