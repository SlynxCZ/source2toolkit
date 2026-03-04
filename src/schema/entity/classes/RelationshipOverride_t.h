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

#include "../enums/Class_T.h"
#include "Relationship_t.h"

class CBaseEntity;

class RelationshipOverride_t : public Relationship_t
{
public:
    DECLARE_SCHEMA_CLASS(RelationshipOverride_t);

    SCHEMA_FIELD(CHandle<CBaseEntity>, entity);
    SCHEMA_FIELD(Class_T, classType);
};
