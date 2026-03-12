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

#include "CModelPointEntity.h"

class CShower : public CModelPointEntity, public CBaseEntity::Factory<CShower>
{
public:
    DECLARE_SCHEMA_CLASS(CShower);

};
