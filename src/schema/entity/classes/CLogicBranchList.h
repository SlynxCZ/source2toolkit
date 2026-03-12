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

#include "CLogicalEntity.h"

class CBaseEntity;

class CLogicBranchList : public CLogicalEntity, public CBaseEntity::Factory<CLogicBranchList>
{
public:
    DECLARE_SCHEMA_CLASS(CLogicBranchList);

    SCHEMA_FIELD_POINTER(CUtlSymbolLarge, m_nLogicBranchNames);
    SCHEMA_FIELD(CUtlVector<CHandle<CBaseEntity>>, m_LogicBranchList);
    SCHEMA_FIELD(CEntityIOOutput, m_OnAllTrue);
    SCHEMA_FIELD(CEntityIOOutput, m_OnAllFalse);
    SCHEMA_FIELD(CEntityIOOutput, m_OnMixed);
};
