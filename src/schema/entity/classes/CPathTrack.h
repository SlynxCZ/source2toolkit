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
#include "../enums/TrackOrientationType_t.h"

class CPathTrack : public CPointEntity, public CBaseEntity::Factory<CPathTrack>
{
public:
    DECLARE_SCHEMA_CLASS(CPathTrack);

    SCHEMA_FIELD(CPathTrack*, m_pnext);
    SCHEMA_FIELD(CPathTrack*, m_pprevious);
    SCHEMA_FIELD(CPathTrack*, m_paltpath);
    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(float, m_length);
    SCHEMA_FIELD(CUtlSymbolLarge, m_altName);
    SCHEMA_FIELD(int32_t, m_nIterVal);
    SCHEMA_FIELD(TrackOrientationType_t, m_eOrientationType);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPass);
};
