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

#include "CPulseGraphInstance_ServerEntity.h"

class CPulseGraphInstance_GameBlackboard : public CPulseGraphInstance_ServerEntity, public CBaseEntity::Factory<CPulseGraphInstance_GameBlackboard>
{
public:
    DECLARE_SCHEMA_CLASS(CPulseGraphInstance_GameBlackboard);

};
