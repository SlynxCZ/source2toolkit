#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "IChoreoServices.h"
#include "../enums/IChoreoServices::ChoreoState_t.h"
#include "../enums/IChoreoServices::ScriptState_t.h"

class CBaseAnimGraph;
class CScriptedSequence;

class CGameChoreoServices : public IChoreoServices
{
public:
    DECLARE_SCHEMA_CLASS(CGameChoreoServices);

    SCHEMA_FIELD(CHandle<CBaseAnimGraph>, m_hOwner);
    SCHEMA_FIELD(CHandle<CScriptedSequence>, m_hScriptedSequence);
    SCHEMA_FIELD(IChoreoServices::ScriptState_t, m_scriptState);
    SCHEMA_FIELD(IChoreoServices::ChoreoState_t, m_choreoState);
    SCHEMA_FIELD(float, m_flTimeStartedState);
};
