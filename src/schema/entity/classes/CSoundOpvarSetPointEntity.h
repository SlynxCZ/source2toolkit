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

#include "CSoundOpvarSetPointBase.h"

class CSoundOpvarSetPointEntity : public CSoundOpvarSetPointBase
{
public:
    DECLARE_SCHEMA_CLASS(CSoundOpvarSetPointEntity);

    SCHEMA_FIELD(CEntityIOOutput, m_OnEnter);
    SCHEMA_FIELD(CEntityIOOutput, m_OnExit);
    SCHEMA_FIELD(bool, m_bAutoDisable);
    SCHEMA_FIELD(float, m_flDistanceMin);
    SCHEMA_FIELD(float, m_flDistanceMax);
    SCHEMA_FIELD(float, m_flDistanceMapMin);
    SCHEMA_FIELD(float, m_flDistanceMapMax);
    SCHEMA_FIELD(float, m_flOcclusionRadius);
    SCHEMA_FIELD(float, m_flOcclusionMin);
    SCHEMA_FIELD(float, m_flOcclusionMax);
    SCHEMA_FIELD(float, m_flValSetOnDisable);
    SCHEMA_FIELD(bool, m_bSetValueOnDisable);
    SCHEMA_FIELD(bool, m_bReloading);
    SCHEMA_FIELD(int32_t, m_nSimulationMode);
    SCHEMA_FIELD(int32_t, m_nVisibilitySamples);
    SCHEMA_FIELD(Vector, m_vDynamicProxyPoint);
    SCHEMA_FIELD(float, m_flDynamicMaximumOcclusion);
    SCHEMA_FIELD(CEntityHandle, m_hDynamicEntity);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszDynamicEntityName);
    SCHEMA_FIELD(float, m_flPathingDistanceNormFactor);
    SCHEMA_FIELD(Vector, m_vPathingSourcePos);
    SCHEMA_FIELD(Vector, m_vPathingListenerPos);
    SCHEMA_FIELD(Vector, m_vPathingDirection);
    SCHEMA_FIELD(int32_t, m_nPathingSourceIndex);
};
