#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLightEntity.h"

class CLightDirectionalEntity : public CLightEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLightDirectionalEntity);

};
