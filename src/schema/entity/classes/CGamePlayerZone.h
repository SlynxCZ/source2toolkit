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

#include "CRuleBrushEntity.h"

class CGamePlayerZone : public CRuleBrushEntity, public CBaseEntity::Factory<CGamePlayerZone>
{
public:
    DECLARE_SCHEMA_CLASS(CGamePlayerZone);

    SCHEMA_FIELD(CEntityIOOutput, m_OnPlayerInZone);
    SCHEMA_FIELD(CEntityIOOutput, m_OnPlayerOutZone);
};
