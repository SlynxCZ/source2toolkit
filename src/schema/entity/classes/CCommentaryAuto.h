#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CCommentaryAuto : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CCommentaryAuto);

    SCHEMA_FIELD(CEntityIOOutput, m_OnCommentaryNewGame);
    SCHEMA_FIELD(CEntityIOOutput, m_OnCommentaryMidGame);
    SCHEMA_FIELD(CEntityIOOutput, m_OnCommentaryMultiplayerSpawn);
};
