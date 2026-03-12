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

#include "CBaseModelEntity.h"
#include "InfoForResourceTypeIParticleSystemDefinition.h"

class CBaseEntity;

class CParticleSystem : public CBaseModelEntity, public CBaseEntity::Factory<CParticleSystem>
{
public:
    DECLARE_SCHEMA_CLASS(CParticleSystem);

    SCHEMA_FIELD_POINTER(char, m_szSnapshotFileName);
    SCHEMA_FIELD(bool, m_bActive);
    SCHEMA_FIELD(bool, m_bFrozen);
    SCHEMA_FIELD(float, m_flFreezeTransitionDuration);
    SCHEMA_FIELD(int32_t, m_nStopType);
    SCHEMA_FIELD(bool, m_bAnimateDuringGameplayPause);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeIParticleSystemDefinition >, m_iEffectIndex);
    SCHEMA_FIELD(float, m_flStartTime);
    SCHEMA_FIELD(float, m_flPreSimTime);
    SCHEMA_FIELD_POINTER(Vector, m_vServerControlPoints);
    SCHEMA_FIELD_POINTER(uint8_t, m_iServerControlPointAssignments);
    SCHEMA_FIELD_POINTER(CHandle<CBaseEntity>, m_hControlPointEnts);
    SCHEMA_FIELD(bool, m_bNoSave);
    SCHEMA_FIELD(bool, m_bNoFreeze);
    SCHEMA_FIELD(bool, m_bNoRamp);
    SCHEMA_FIELD(bool, m_bStartActive);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszEffectName);
    SCHEMA_FIELD_POINTER(CUtlSymbolLarge, m_iszControlPointNames);
    SCHEMA_FIELD(int32_t, m_nDataCP);
    SCHEMA_FIELD(Vector, m_vecDataCPValue);
    SCHEMA_FIELD(int32_t, m_nTintCP);
    SCHEMA_FIELD(Color, m_clrTint);
};
