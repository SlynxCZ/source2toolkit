#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"
#include "InfoForResourceTypeCTextureBase.h"

class CEnvCombinedLightProbeVolume : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvCombinedLightProbeVolume);

    SCHEMA_FIELD(Color, m_Entity_Color);
    SCHEMA_FIELD(float, m_Entity_flBrightness);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_Entity_hCubemapTexture);
    SCHEMA_FIELD(bool, m_Entity_bCustomCubemapTexture);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_Entity_hLightProbeTexture_AmbientCube);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_Entity_hLightProbeTexture_SDF);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_Entity_hLightProbeTexture_SH2_DC);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_Entity_hLightProbeTexture_SH2_R);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_Entity_hLightProbeTexture_SH2_G);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_Entity_hLightProbeTexture_SH2_B);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_Entity_hLightProbeDirectLightIndicesTexture);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_Entity_hLightProbeDirectLightScalarsTexture);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_Entity_hLightProbeDirectLightShadowsTexture);
    SCHEMA_FIELD(Vector, m_Entity_vBoxMins);
    SCHEMA_FIELD(Vector, m_Entity_vBoxMaxs);
    SCHEMA_FIELD(bool, m_Entity_bMoveable);
    SCHEMA_FIELD(int32_t, m_Entity_nHandshake);
    SCHEMA_FIELD(int32_t, m_Entity_nEnvCubeMapArrayIndex);
    SCHEMA_FIELD(int32_t, m_Entity_nPriority);
    SCHEMA_FIELD(bool, m_Entity_bStartDisabled);
    SCHEMA_FIELD(float, m_Entity_flEdgeFadeDist);
    SCHEMA_FIELD(Vector, m_Entity_vEdgeFadeDists);
    SCHEMA_FIELD(int32_t, m_Entity_nLightProbeSizeX);
    SCHEMA_FIELD(int32_t, m_Entity_nLightProbeSizeY);
    SCHEMA_FIELD(int32_t, m_Entity_nLightProbeSizeZ);
    SCHEMA_FIELD(int32_t, m_Entity_nLightProbeAtlasX);
    SCHEMA_FIELD(int32_t, m_Entity_nLightProbeAtlasY);
    SCHEMA_FIELD(int32_t, m_Entity_nLightProbeAtlasZ);
    SCHEMA_FIELD(bool, m_Entity_bEnabled);
};
