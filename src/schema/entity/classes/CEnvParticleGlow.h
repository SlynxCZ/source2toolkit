#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CParticleSystem.h"
#include "InfoForResourceTypeCTextureBase.h"

class CEnvParticleGlow : public CParticleSystem
{
public:
    DECLARE_SCHEMA_CLASS(CEnvParticleGlow);

    SCHEMA_FIELD(float, m_flAlphaScale);
    SCHEMA_FIELD(float, m_flRadiusScale);
    SCHEMA_FIELD(float, m_flSelfIllumScale);
    SCHEMA_FIELD(Color, m_ColorTint);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_hTextureOverride);
};
