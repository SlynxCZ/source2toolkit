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

#include "CBaseAnimGraph.h"
#include "magnetted_objects_t.h"

class CPhysMagnet : public CBaseAnimGraph, public CBaseEntity::Factory<CPhysMagnet>
{
public:
    DECLARE_SCHEMA_CLASS(CPhysMagnet);

    SCHEMA_FIELD(CEntityIOOutput, m_OnMagnetAttach);
    SCHEMA_FIELD(CEntityIOOutput, m_OnMagnetDetach);
    SCHEMA_FIELD(float, m_massScale);
    SCHEMA_FIELD(float, m_forceLimit);
    SCHEMA_FIELD(float, m_torqueLimit);
    SCHEMA_FIELD(CUtlVector<magnetted_objects_t>, m_MagnettedEntities);
    SCHEMA_FIELD(bool, m_bActive);
    SCHEMA_FIELD(bool, m_bHasHitSomething);
    SCHEMA_FIELD(float, m_flTotalMass);
    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(float, m_flNextSuckTime);
    SCHEMA_FIELD(int32_t, m_iMaxObjectsAttached);
};
