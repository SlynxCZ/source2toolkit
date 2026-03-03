#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CLogicProximity : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLogicProximity);

};
