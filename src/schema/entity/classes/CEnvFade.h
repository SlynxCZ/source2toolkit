#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"

class CEnvFade : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvFade);

    SCHEMA_FIELD(Color, m_fadeColor);
    SCHEMA_FIELD(float, m_Duration);
    SCHEMA_FIELD(float, m_HoldDuration);
    SCHEMA_FIELD(CEntityIOOutput, m_OnBeginFade);
};
