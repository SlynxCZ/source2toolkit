#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CTriggerTeleport : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerTeleport);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iLandmark);
    SCHEMA_FIELD(bool, m_bUseLandmarkAngles);
    SCHEMA_FIELD(bool, m_bMirrorPlayer);
    SCHEMA_FIELD(bool, m_bCheckDestIfClearForPlayer);
};
