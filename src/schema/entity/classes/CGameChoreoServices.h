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

#include "IChoreoServices.h"

class CBaseAnimGraph;
class CScriptedSequence;

class CGameChoreoServices : public IChoreoServices, public CBaseEntity::Factory<CGameChoreoServices>
{
public:
    DECLARE_SCHEMA_CLASS(CGameChoreoServices);

    SCHEMA_FIELD(CHandle<CBaseAnimGraph>, m_hOwner);
    SCHEMA_FIELD(CHandle<CScriptedSequence>, m_hScriptedSequence);
    SCHEMA_FIELD(float, m_flTimeStartedState);
};
