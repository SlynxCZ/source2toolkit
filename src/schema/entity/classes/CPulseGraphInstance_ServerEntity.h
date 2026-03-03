#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBasePulseGraphInstance.h"

class CBaseEntity;

class CPulseGraphInstance_ServerEntity : public CBasePulseGraphInstance
{
public:
    DECLARE_SCHEMA_CLASS(CPulseGraphInstance_ServerEntity);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hOwner);
    SCHEMA_FIELD(bool, m_bActivated);
    SCHEMA_FIELD(CUtlSymbolLarge, m_sNameFixupStaticPrefix);
    SCHEMA_FIELD(CUtlSymbolLarge, m_sNameFixupParent);
    SCHEMA_FIELD(CUtlSymbolLarge, m_sNameFixupLocal);
    SCHEMA_FIELD(CUtlSymbolLarge, m_sProceduralWorldNameForRelays);
};
