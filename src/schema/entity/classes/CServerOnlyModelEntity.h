#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CServerOnlyModelEntity : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CServerOnlyModelEntity);

};
