#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CPointCamera : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointCamera);

    SCHEMA_FIELD(float, m_FOV);
    SCHEMA_FIELD(float, m_Resolution);
    SCHEMA_FIELD(bool, m_bFogEnable);
    SCHEMA_FIELD(Color, m_FogColor);
    SCHEMA_FIELD(float, m_flFogStart);
    SCHEMA_FIELD(float, m_flFogEnd);
    SCHEMA_FIELD(float, m_flFogMaxDensity);
    SCHEMA_FIELD(bool, m_bActive);
    SCHEMA_FIELD(bool, m_bUseScreenAspectRatio);
    SCHEMA_FIELD(float, m_flAspectRatio);
    SCHEMA_FIELD(bool, m_bNoSky);
    SCHEMA_FIELD(float, m_fBrightness);
    SCHEMA_FIELD(float, m_flZFar);
    SCHEMA_FIELD(float, m_flZNear);
    SCHEMA_FIELD(bool, m_bCanHLTVUse);
    SCHEMA_FIELD(bool, m_bAlignWithParent);
    SCHEMA_FIELD(bool, m_bDofEnabled);
    SCHEMA_FIELD(float, m_flDofNearBlurry);
    SCHEMA_FIELD(float, m_flDofNearCrisp);
    SCHEMA_FIELD(float, m_flDofFarCrisp);
    SCHEMA_FIELD(float, m_flDofFarBlurry);
    SCHEMA_FIELD(float, m_flDofTiltToGround);
    SCHEMA_FIELD(float, m_TargetFOV);
    SCHEMA_FIELD(float, m_DegreesPerSecond);
    SCHEMA_FIELD(bool, m_bIsOn);
    SCHEMA_FIELD(CPointCamera*, m_pNext);
};
