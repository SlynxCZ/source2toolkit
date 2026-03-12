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

#include "CPointEntity.h"

class CBaseEntity;

class CEnvEntityMaker : public CPointEntity, public CBaseEntity::Factory<CEnvEntityMaker>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvEntityMaker);

    SCHEMA_FIELD(Vector, m_vecEntityMins);
    SCHEMA_FIELD(Vector, m_vecEntityMaxs);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hCurrentInstance);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hCurrentBlocker);
    SCHEMA_FIELD(Vector, m_vecBlockerOrigin);
    SCHEMA_FIELD(QAngle, m_angPostSpawnDirection);
    SCHEMA_FIELD(float, m_flPostSpawnDirectionVariance);
    SCHEMA_FIELD(float, m_flPostSpawnSpeed);
    SCHEMA_FIELD(bool, m_bPostSpawnUseAngles);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszTemplate);
    SCHEMA_FIELD(CEntityIOOutput, m_pOutputOnSpawned);
    SCHEMA_FIELD(CEntityIOOutput, m_pOutputOnFailedSpawn);
};
