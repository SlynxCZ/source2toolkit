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

#include "CBaseEntity.h"
#include "InfoForResourceTypeIParticleSystemDefinition.h"

class CPathParticleRope : public CBaseEntity, public CBaseEntity::Factory<CPathParticleRope>
{
public:
    DECLARE_SCHEMA_CLASS(CPathParticleRope);

    SCHEMA_FIELD(bool, m_bStartActive);
    SCHEMA_FIELD(float, m_flMaxSimulationTime);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszEffectName);
    SCHEMA_FIELD(CUtlVector<CUtlSymbolLarge>, m_PathNodes_Name);
    SCHEMA_FIELD(float, m_flParticleSpacing);
    SCHEMA_FIELD(float, m_flSlack);
    SCHEMA_FIELD(float, m_flRadius);
    SCHEMA_FIELD(Color, m_ColorTint);
    SCHEMA_FIELD(int32_t, m_nEffectState);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeIParticleSystemDefinition >, m_iEffectIndex);
    SCHEMA_FIELD(CUtlVector<Vector>, m_PathNodes_Position);
    SCHEMA_FIELD(CUtlVector<Vector>, m_PathNodes_TangentIn);
    SCHEMA_FIELD(CUtlVector<Vector>, m_PathNodes_TangentOut);
    SCHEMA_FIELD(CUtlVector<Vector>, m_PathNodes_Color);
    SCHEMA_FIELD(CUtlVector<bool>, m_PathNodes_PinEnabled);
    SCHEMA_FIELD(CUtlVector<float>, m_PathNodes_RadiusScale);
};
