#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CFuncBrush.h"

class CBaseEntity;

class CFuncMonitor : public CFuncBrush
{
public:
    DECLARE_SCHEMA_CLASS(CFuncMonitor);

    SCHEMA_FIELD(CUtlString, m_targetCamera);
    SCHEMA_FIELD(int32_t, m_nResolutionEnum);
    SCHEMA_FIELD(bool, m_bRenderShadows);
    SCHEMA_FIELD(bool, m_bUseUniqueColorTarget);
    SCHEMA_FIELD(CUtlString, m_brushModelName);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hTargetCamera);
    SCHEMA_FIELD(bool, m_bEnabled);
    SCHEMA_FIELD(bool, m_bDraw3DSkybox);
    SCHEMA_FIELD(bool, m_bStartEnabled);
};
