#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CServerOnlyEntity.h"

class CLogicalEntity : public CServerOnlyEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicalEntity);

};
