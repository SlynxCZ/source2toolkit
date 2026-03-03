#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CEntityComponent.h"

class CPathQueryComponent : public CEntityComponent
{
public:
    DECLARE_SCHEMA_CLASS(CPathQueryComponent);

};
