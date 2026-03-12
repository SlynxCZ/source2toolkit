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

#include "CBaseEntity.h"

class CTonemapController2 : public CBaseEntity, public CBaseEntity::Factory<CTonemapController2>
{
public:
    DECLARE_SCHEMA_CLASS(CTonemapController2);

    SCHEMA_FIELD(float, m_flAutoExposureMin);
    SCHEMA_FIELD(float, m_flAutoExposureMax);
    SCHEMA_FIELD(float, m_flExposureAdaptationSpeedUp);
    SCHEMA_FIELD(float, m_flExposureAdaptationSpeedDown);
    SCHEMA_FIELD(float, m_flTonemapEVSmoothingRange);
};
