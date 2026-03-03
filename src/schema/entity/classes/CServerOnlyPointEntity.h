#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CServerOnlyEntity.h"

class CServerOnlyPointEntity : public CServerOnlyEntity
{
public:
    DECLARE_SCHEMA_CLASS(CServerOnlyPointEntity);

};
