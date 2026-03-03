#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CAnimGraphControllerBase.h"

class CEmptyGraphController : public CAnimGraphControllerBase
{
public:
    DECLARE_SCHEMA_CLASS(CEmptyGraphController);

};
