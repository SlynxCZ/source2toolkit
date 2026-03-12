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

#include "../enums/Disposition_t.h"

class Relationship_t : public CBaseEntity::Factory<Relationship_t>
{
public:
    DECLARE_SCHEMA_CLASS(Relationship_t);

    SCHEMA_FIELD(Disposition_t, disposition);
    SCHEMA_FIELD(int32_t, priority);
};
