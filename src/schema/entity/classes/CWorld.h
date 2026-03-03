#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CWorld : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CWorld);

};
