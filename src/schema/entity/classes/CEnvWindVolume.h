#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CEnvWindVolume : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvWindVolume);

    SCHEMA_FIELD(bool, m_bActive);
    SCHEMA_FIELD(Vector, m_vBoxMins);
    SCHEMA_FIELD(Vector, m_vBoxMaxs);
    SCHEMA_FIELD(bool, m_bStartDisabled);
    SCHEMA_FIELD(int32_t, m_nShape);
    SCHEMA_FIELD(float, m_fWindSpeedMultiplier);
    SCHEMA_FIELD(float, m_fWindTurbulenceMultiplier);
    SCHEMA_FIELD(float, m_fWindSpeedVariationMultiplier);
    SCHEMA_FIELD(float, m_fWindDirectionVariationMultiplier);
};
