#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CServerOnlyModelEntity.h"

class CFogVolume : public CServerOnlyModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFogVolume);

    SCHEMA_FIELD(CUtlSymbolLarge, m_fogName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_postProcessName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_colorCorrectionName);
    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(bool, m_bInFogVolumesList);
};
