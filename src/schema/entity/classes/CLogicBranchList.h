#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLogicalEntity.h"
#include "../enums/CLogicBranchList::LogicBranchListenerLastState_t.h"

class CBaseEntity;

class CLogicBranchList : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicBranchList);

    SCHEMA_FIELD_POINTER(CUtlSymbolLarge, m_nLogicBranchNames);
    SCHEMA_FIELD(CUtlVector<CHandle<CBaseEntity>>, m_LogicBranchList);
    SCHEMA_FIELD(CLogicBranchList::LogicBranchListenerLastState_t, m_eLastState);
    SCHEMA_FIELD(CEntityIOOutput, m_OnAllTrue);
    SCHEMA_FIELD(CEntityIOOutput, m_OnAllFalse);
    SCHEMA_FIELD(CEntityIOOutput, m_OnMixed);
};
