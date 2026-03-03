#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CInfoLandmark : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CInfoLandmark);

};
