#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CSoundEventEntity.h"

class CSoundEventPathCornerEntity : public CSoundEventEntity
{
public:
    DECLARE_SCHEMA_CLASS(CSoundEventPathCornerEntity);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszPathCorner);
    SCHEMA_FIELD(int32_t, m_iCountMax);
    SCHEMA_FIELD(float, m_flDistanceMax);
    SCHEMA_FIELD(float, m_flDistMaxSqr);
    SCHEMA_FIELD(float, m_flDotProductMax);
    SCHEMA_FIELD(bool, m_bPlaying);
    SCHEMA_FIELD(CUtlVector<SoundeventPathCornerPairNetworked_t>, m_vecCornerPairsNetworked);
};
