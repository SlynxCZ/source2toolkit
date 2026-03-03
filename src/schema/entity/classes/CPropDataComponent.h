#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CEntityComponent.h"

class CPropDataComponent : public CEntityComponent
{
public:
    DECLARE_SCHEMA_CLASS(CPropDataComponent);

    SCHEMA_FIELD(float, m_flDmgModBullet);
    SCHEMA_FIELD(float, m_flDmgModClub);
    SCHEMA_FIELD(float, m_flDmgModExplosive);
    SCHEMA_FIELD(float, m_flDmgModFire);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszPhysicsDamageTableName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszBasePropData);
    SCHEMA_FIELD(int32_t, m_nInteractions);
    SCHEMA_FIELD(bool, m_bSpawnMotionDisabled);
    SCHEMA_FIELD(int32_t, m_nDisableTakePhysicsDamageSpawnFlag);
    SCHEMA_FIELD(int32_t, m_nMotionDisabledSpawnFlag);
};
