#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLightDirectionalEntity.h"

class CLightEnvironmentEntity : public CLightDirectionalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLightEnvironmentEntity);

};
