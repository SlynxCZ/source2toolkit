#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "vector.h"
#include "utlsymbol.h"
#include "utlsymbollarge.h"
#include "utlstring.h"
#include "utlstringtoken.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CBaseEntity;

class magnetted_objects_t : public CBaseEntity::Factory<magnetted_objects_t>
{
public:
    DECLARE_SCHEMA_CLASS(magnetted_objects_t);

    SCHEMA_FIELD(CHandle<CBaseEntity>, hEntity);
};
