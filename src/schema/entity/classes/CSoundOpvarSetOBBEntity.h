#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CSoundOpvarSetAABBEntity.h"

class CSoundOpvarSetOBBEntity : public CSoundOpvarSetAABBEntity
{
public:
    DECLARE_SCHEMA_CLASS(CSoundOpvarSetOBBEntity);

};
