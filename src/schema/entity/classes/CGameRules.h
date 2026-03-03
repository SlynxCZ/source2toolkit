#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CNetworkVarChainer.h"

class CGameRules
{
public:
    DECLARE_SCHEMA_CLASS(CGameRules);

    SCHEMA_FIELD(CNetworkVarChainer, __m_pChainEntity);
    SCHEMA_FIELD_POINTER(char, m_szQuestName);
    SCHEMA_FIELD(int32_t, m_nQuestPhase);
    SCHEMA_FIELD(uint32_t, m_nLastMatchTime);
    SCHEMA_FIELD(uint64_t, m_nLastMatchTime_MatchID64);
    SCHEMA_FIELD(int32_t, m_nTotalPausedTicks);
    SCHEMA_FIELD(int32_t, m_nPauseStartTick);
    SCHEMA_FIELD(bool, m_bGamePaused);
};
