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

#include "CBaseTrigger.h"

class CServerRagdollTrigger : public CBaseTrigger, public CBaseEntity::Factory<CServerRagdollTrigger>
{
public:
    DECLARE_SCHEMA_CLASS(CServerRagdollTrigger);

};
