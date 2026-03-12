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
#include "InfoForResourceTypeCPostProcessingResource.h"

class CPostProcessingVolume : public CBaseTrigger, public CBaseEntity::Factory<CPostProcessingVolume>
{
public:
    DECLARE_SCHEMA_CLASS(CPostProcessingVolume);

    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCPostProcessingResource >, m_hPostSettings);
    SCHEMA_FIELD(float, m_flFadeDuration);
    SCHEMA_FIELD(float, m_flMinLogExposure);
    SCHEMA_FIELD(float, m_flMaxLogExposure);
    SCHEMA_FIELD(float, m_flMinExposure);
    SCHEMA_FIELD(float, m_flMaxExposure);
    SCHEMA_FIELD(float, m_flExposureCompensation);
    SCHEMA_FIELD(float, m_flExposureFadeSpeedUp);
    SCHEMA_FIELD(float, m_flExposureFadeSpeedDown);
    SCHEMA_FIELD(float, m_flTonemapEVSmoothingRange);
    SCHEMA_FIELD(bool, m_bMaster);
    SCHEMA_FIELD(bool, m_bExposureControl);
};
