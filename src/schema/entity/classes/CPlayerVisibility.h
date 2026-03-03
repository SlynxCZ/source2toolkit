#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CPlayerVisibility : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPlayerVisibility);

    SCHEMA_FIELD(float, m_flVisibilityStrength);
    SCHEMA_FIELD(float, m_flFogDistanceMultiplier);
    SCHEMA_FIELD(float, m_flFogMaxDensityMultiplier);
    SCHEMA_FIELD(float, m_flFadeTime);
    SCHEMA_FIELD(bool, m_bStartDisabled);
    SCHEMA_FIELD(bool, m_bIsEnabled);
};
