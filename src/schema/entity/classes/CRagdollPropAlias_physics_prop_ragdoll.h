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

#include "CRagdollProp.h"

class CRagdollPropAlias_physics_prop_ragdoll : public CRagdollProp, public CBaseEntity::Factory<CRagdollPropAlias_physics_prop_ragdoll>
{
public:
    DECLARE_SCHEMA_CLASS(CRagdollPropAlias_physics_prop_ragdoll);

};
