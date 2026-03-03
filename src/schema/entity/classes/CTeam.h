#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CBasePlayerController;
class CBasePlayerPawn;

class CTeam : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CTeam);

    SCHEMA_FIELD(CUtlVector<CHandle<CBasePlayerController>>, m_aPlayerControllers);
    SCHEMA_FIELD(CUtlVector<CHandle<CBasePlayerPawn>>, m_aPlayers);
    SCHEMA_FIELD(int32_t, m_iScore);
    SCHEMA_FIELD_POINTER(char, m_szTeamname);
};
