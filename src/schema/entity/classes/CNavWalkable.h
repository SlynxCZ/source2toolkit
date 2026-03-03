#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CNavWalkable : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CNavWalkable);

};
