#pragma once
#include "CBaseEntity.h"
#include "igameevents.h"
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

#include "CPhysHinge.h"

class CPhysHingeAlias_phys_hinge_local : public CPhysHinge, public CBaseEntity::Factory<CPhysHingeAlias_phys_hinge_local>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysHingeAlias_phys_hinge_local);

};
