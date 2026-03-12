#pragma once
#include "CBaseEntity.h"
#include "igameevents.h"
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

#include "CTeam.h"

class CCSTeam : public CTeam, public CBaseEntity::Factory<CCSTeam>
{
public:
    DECLARE_SCHEMA_CLASS(CCSTeam);

    SCHEMA_FIELD(int32_t, m_nLastRecievedShorthandedRoundBonus);
    SCHEMA_FIELD(int32_t, m_nShorthandedRoundBonusStartRound);
    SCHEMA_FIELD(bool, m_bSurrendered);
    SCHEMA_FIELD_POINTER(char, m_szTeamMatchStat);
    SCHEMA_FIELD(int32_t, m_numMapVictories);
    SCHEMA_FIELD(int32_t, m_scoreFirstHalf);
    SCHEMA_FIELD(int32_t, m_scoreSecondHalf);
    SCHEMA_FIELD(int32_t, m_scoreOvertime);
    SCHEMA_FIELD_POINTER(char, m_szClanTeamname);
    SCHEMA_FIELD(uint32_t, m_iClanID);
    SCHEMA_FIELD_POINTER(char, m_szTeamFlagImage);
    SCHEMA_FIELD_POINTER(char, m_szTeamLogoImage);
    SCHEMA_FIELD(float, m_flNextResourceTime);
    SCHEMA_FIELD(int32_t, m_iLastUpdateSentAt);
};
