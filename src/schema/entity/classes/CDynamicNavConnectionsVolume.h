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

#include "CTriggerMultiple.h"
#include "DynamicVolumeDef_t.h"

class CDynamicNavConnectionsVolume : public CTriggerMultiple
{
public:
    DECLARE_SCHEMA_CLASS(CDynamicNavConnectionsVolume);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszConnectionTarget);
    SCHEMA_FIELD(CUtlVector<DynamicVolumeDef_t>, m_vecConnections);
    SCHEMA_FIELD(CGlobalSymbol, m_sTransitionType);
    SCHEMA_FIELD(bool, m_bConnectionsEnabled);
    SCHEMA_FIELD(float, m_flTargetAreaSearchRadius);
    SCHEMA_FIELD(float, m_flUpdateDistance);
    SCHEMA_FIELD(float, m_flMaxConnectionDistance);
};
