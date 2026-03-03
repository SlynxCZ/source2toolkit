#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CServerOnlyPointEntity.h"

class CInfoTargetServerOnly : public CServerOnlyPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CInfoTargetServerOnly);

};
