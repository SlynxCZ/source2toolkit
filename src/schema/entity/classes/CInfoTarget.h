#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CInfoTarget : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CInfoTarget);

};
