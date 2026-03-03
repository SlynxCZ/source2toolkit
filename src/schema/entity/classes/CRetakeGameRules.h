#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CCSPlayerPawn;

class CRetakeGameRules
{
public:
    DECLARE_SCHEMA_CLASS(CRetakeGameRules);

    SCHEMA_FIELD(int32_t, m_nMatchSeed);
    SCHEMA_FIELD(bool, m_bBlockersPresent);
    SCHEMA_FIELD(bool, m_bRoundInProgress);
    SCHEMA_FIELD(int32_t, m_iFirstSecondHalfRound);
    SCHEMA_FIELD(int32_t, m_iBombSite);
    SCHEMA_FIELD(CHandle<CCSPlayerPawn>, m_hBombPlanter);
};
