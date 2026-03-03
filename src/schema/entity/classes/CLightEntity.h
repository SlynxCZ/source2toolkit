#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CLightComponent;

class CLightEntity : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLightEntity);

    SCHEMA_FIELD(CLightComponent*, m_CLightComponent);
};
