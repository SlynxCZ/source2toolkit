#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "../enums/MoodType_t.h"

class CMoodVData
{
public:
    DECLARE_SCHEMA_CLASS(CMoodVData);

    SCHEMA_FIELD(MoodType_t, m_nMoodType);
    SCHEMA_FIELD(CUtlVector<MoodAnimationLayer_t>, m_animationLayers);
};
