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

#include "CBaseFlex.h"
#include "CMovementStatsProperty.h"
#include "../enums/Hull_t.h"
#include "RelationshipOverride_t.h"

class CEconWearable;

class CBaseCombatCharacter : public CBaseFlex, public CBaseEntity::Factory<CBaseCombatCharacter>
{
public:
    DECLARE_SCHEMA_CLASS(CBaseCombatCharacter);

    SCHEMA_FIELD(bool, m_bForceServerRagdoll);
    SCHEMA_FIELD(CUtlVector<CHandle<CEconWearable>>, m_hMyWearables);
    SCHEMA_FIELD(float, m_impactEnergyScale);
    SCHEMA_FIELD(bool, m_bApplyStressDamage);
    SCHEMA_FIELD(bool, m_bDeathEventsDispatched);
    SCHEMA_FIELD(CUtlVector<RelationshipOverride_t>*, m_pVecRelationships);
    SCHEMA_FIELD(CUtlSymbolLarge, m_strRelationships);
    SCHEMA_FIELD(Hull_t, m_eHull);
    SCHEMA_FIELD(uint32_t, m_nNavHullIdx);
    SCHEMA_FIELD(CMovementStatsProperty, m_movementStats);
};
