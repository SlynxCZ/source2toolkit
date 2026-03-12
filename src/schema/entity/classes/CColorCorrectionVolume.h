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

#include "CBaseTrigger.h"

class CColorCorrectionVolume : public CBaseTrigger, public CBaseEntity::Factory<CColorCorrectionVolume>
{
public:
    DECLARE_SCHEMA_CLASS(CColorCorrectionVolume);

    SCHEMA_FIELD(float, m_MaxWeight);
    SCHEMA_FIELD(float, m_FadeDuration);
    SCHEMA_FIELD(float, m_Weight);
    SCHEMA_FIELD_POINTER(char, m_lookupFilename);
    SCHEMA_FIELD(float, m_LastEnterWeight);
    SCHEMA_FIELD(float, m_LastEnterTime);
    SCHEMA_FIELD(float, m_LastExitWeight);
    SCHEMA_FIELD(float, m_LastExitTime);
};
