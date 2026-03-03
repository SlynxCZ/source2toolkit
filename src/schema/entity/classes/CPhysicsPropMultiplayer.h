#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPhysicsProp.h"

class CPhysicsPropMultiplayer : public CPhysicsProp
{
public:
    DECLARE_SCHEMA_CLASS(CPhysicsPropMultiplayer);

};
