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

#include "CBaseModelEntity.h"

class CInfoLadderDismount;

class CFuncLadder : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFuncLadder);

    SCHEMA_FIELD(Vector, m_vecLadderDir);
    SCHEMA_FIELD(CUtlVector<CHandle<CInfoLadderDismount>>, m_Dismounts);
    SCHEMA_FIELD(Vector, m_vecLocalTop);
    SCHEMA_FIELD(Vector, m_vecPlayerMountPositionTop);
    SCHEMA_FIELD(Vector, m_vecPlayerMountPositionBottom);
    SCHEMA_FIELD(float, m_flAutoRideSpeed);
    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(bool, m_bFakeLadder);
    SCHEMA_FIELD(bool, m_bHasSlack);
    SCHEMA_FIELD(CUtlSymbolLarge, m_surfacePropName);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPlayerGotOnLadder);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPlayerGotOffLadder);
};
