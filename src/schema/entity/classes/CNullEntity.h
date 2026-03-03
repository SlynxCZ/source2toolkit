#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CNullEntity : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CNullEntity);

};
