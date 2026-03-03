#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPhysicsProp.h"

class CPhysicsPropOverride : public CPhysicsProp
{
public:
    DECLARE_SCHEMA_CLASS(CPhysicsPropOverride);

};
