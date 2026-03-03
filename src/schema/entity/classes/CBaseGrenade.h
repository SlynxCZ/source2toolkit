#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseFlex.h"

class CCSPlayerPawn;

class CBaseGrenade : public CBaseFlex
{
public:
    DECLARE_SCHEMA_CLASS(CBaseGrenade);

    SCHEMA_FIELD(CEntityIOOutput, m_OnPlayerPickup);
    SCHEMA_FIELD(CEntityIOOutput, m_OnExplode);
    SCHEMA_FIELD(bool, m_bHasWarnedAI);
    SCHEMA_FIELD(bool, m_bIsSmokeGrenade);
    SCHEMA_FIELD(bool, m_bIsLive);
    SCHEMA_FIELD(float, m_DmgRadius);
    SCHEMA_FIELD(float, m_flDetonateTime);
    SCHEMA_FIELD(float, m_flWarnAITime);
    SCHEMA_FIELD(float, m_flDamage);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszBounceSound);
    SCHEMA_FIELD(CUtlString, m_ExplosionSound);
    SCHEMA_FIELD(CHandle<CCSPlayerPawn>, m_hThrower);
    SCHEMA_FIELD(float, m_flNextAttack);
    SCHEMA_FIELD(CHandle<CCSPlayerPawn>, m_hOriginalThrower);
};
