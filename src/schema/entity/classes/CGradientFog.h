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
#include "InfoForResourceTypeCTextureBase.h"

class CGradientFog : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CGradientFog);

    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_hGradientFogTexture);
    SCHEMA_FIELD(float, m_flFogStartDistance);
    SCHEMA_FIELD(float, m_flFogEndDistance);
    SCHEMA_FIELD(bool, m_bHeightFogEnabled);
    SCHEMA_FIELD(float, m_flFogStartHeight);
    SCHEMA_FIELD(float, m_flFogEndHeight);
    SCHEMA_FIELD(float, m_flFarZ);
    SCHEMA_FIELD(float, m_flFogMaxOpacity);
    SCHEMA_FIELD(float, m_flFogFalloffExponent);
    SCHEMA_FIELD(float, m_flFogVerticalExponent);
    SCHEMA_FIELD(Color, m_fogColor);
    SCHEMA_FIELD(float, m_flFogStrength);
    SCHEMA_FIELD(float, m_flFadeTime);
    SCHEMA_FIELD(bool, m_bStartDisabled);
    SCHEMA_FIELD(bool, m_bIsEnabled);
    SCHEMA_FIELD(bool, m_bGradientFogNeedsTextures);
};
