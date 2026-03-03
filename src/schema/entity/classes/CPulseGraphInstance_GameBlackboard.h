#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPulseGraphInstance_ServerEntity.h"

class CPulseGraphInstance_GameBlackboard : public CPulseGraphInstance_ServerEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPulseGraphInstance_GameBlackboard);

};
