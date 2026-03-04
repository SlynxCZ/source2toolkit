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

class CEnvVolumetricFogVolume : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvVolumetricFogVolume);

    SCHEMA_FIELD(bool, m_bActive);
    SCHEMA_FIELD(Vector, m_vBoxMins);
    SCHEMA_FIELD(Vector, m_vBoxMaxs);
    SCHEMA_FIELD(bool, m_bStartDisabled);
    SCHEMA_FIELD(bool, m_bIndirectUseLPVs);
    SCHEMA_FIELD(float, m_flStrength);
    SCHEMA_FIELD(int32_t, m_nFalloffShape);
    SCHEMA_FIELD(float, m_flFalloffExponent);
    SCHEMA_FIELD(float, m_flHeightFogDepth);
    SCHEMA_FIELD(float, m_fHeightFogEdgeWidth);
    SCHEMA_FIELD(float, m_fIndirectLightStrength);
    SCHEMA_FIELD(float, m_fSunLightStrength);
    SCHEMA_FIELD(float, m_fNoiseStrength);
    SCHEMA_FIELD(Color, m_TintColor);
    SCHEMA_FIELD(bool, m_bOverrideTintColor);
    SCHEMA_FIELD(bool, m_bOverrideIndirectLightStrength);
    SCHEMA_FIELD(bool, m_bOverrideSunLightStrength);
    SCHEMA_FIELD(bool, m_bOverrideNoiseStrength);
};
