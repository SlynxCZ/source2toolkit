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

#include "CBaseEntity.h"

class CCommentaryAuto : public CBaseEntity, public CBaseEntity::Factory<CCommentaryAuto>
{
public:
    DECLARE_SCHEMA_CLASS(CCommentaryAuto);

    SCHEMA_FIELD(CEntityIOOutput, m_OnCommentaryNewGame);
    SCHEMA_FIELD(CEntityIOOutput, m_OnCommentaryMidGame);
    SCHEMA_FIELD(CEntityIOOutput, m_OnCommentaryMultiplayerSpawn);
};
