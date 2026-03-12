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

#include "CSoundEventEntity.h"

class CSoundEventPathCornerEntity : public CSoundEventEntity, public CBaseEntity::Factory<CSoundEventPathCornerEntity>
{
public:
    DECLARE_SCHEMA_CLASS(CSoundEventPathCornerEntity);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszPathCorner);
    SCHEMA_FIELD(int32_t, m_iCountMax);
    SCHEMA_FIELD(float, m_flDistanceMax);
    SCHEMA_FIELD(float, m_flDistMaxSqr);
    SCHEMA_FIELD(float, m_flDotProductMax);
    SCHEMA_FIELD(bool, m_bPlaying);
};
