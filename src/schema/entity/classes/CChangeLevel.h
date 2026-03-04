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

class CChangeLevel : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CChangeLevel);

    SCHEMA_FIELD(CUtlString, m_sMapName);
    SCHEMA_FIELD(CUtlString, m_sLandmarkName);
    SCHEMA_FIELD(CEntityIOOutput, m_OnChangeLevel);
    SCHEMA_FIELD(bool, m_bTouched);
    SCHEMA_FIELD(bool, m_bNoTouch);
    SCHEMA_FIELD(bool, m_bNewChapter);
    SCHEMA_FIELD(bool, m_bOnChangeLevelFired);
};
