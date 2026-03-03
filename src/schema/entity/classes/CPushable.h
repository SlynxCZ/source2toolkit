#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBreakable.h"

class CPushable : public CBreakable
{
public:
    DECLARE_SCHEMA_CLASS(CPushable);

};
