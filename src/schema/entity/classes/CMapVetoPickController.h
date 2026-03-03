#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CMapVetoPickController : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CMapVetoPickController);

    SCHEMA_FIELD(bool, m_bPlayedIntroVcd);
    SCHEMA_FIELD(bool, m_bNeedToPlayFiveSecondsRemaining);
    SCHEMA_FIELD(double, m_dblPreMatchDraftSequenceTime);
    SCHEMA_FIELD(bool, m_bPreMatchDraftStateChanged);
    SCHEMA_FIELD(int32_t, m_nDraftType);
    SCHEMA_FIELD(int32_t, m_nTeamWinningCoinToss);
    SCHEMA_FIELD_POINTER(int32_t, m_nTeamWithFirstChoice);
    SCHEMA_FIELD_POINTER(int32_t, m_nVoteMapIdsList);
    SCHEMA_FIELD_POINTER(int32_t, m_nAccountIDs);
    SCHEMA_FIELD_POINTER(int32_t, m_nMapId0);
    SCHEMA_FIELD_POINTER(int32_t, m_nMapId1);
    SCHEMA_FIELD_POINTER(int32_t, m_nMapId2);
    SCHEMA_FIELD_POINTER(int32_t, m_nMapId3);
    SCHEMA_FIELD_POINTER(int32_t, m_nMapId4);
    SCHEMA_FIELD_POINTER(int32_t, m_nMapId5);
    SCHEMA_FIELD_POINTER(int32_t, m_nStartingSide0);
    SCHEMA_FIELD(int32_t, m_nCurrentPhase);
    SCHEMA_FIELD(int32_t, m_nPhaseStartTick);
    SCHEMA_FIELD(int32_t, m_nPhaseDurationTicks);
};
