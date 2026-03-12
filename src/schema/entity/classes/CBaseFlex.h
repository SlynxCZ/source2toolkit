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
#include "SceneEventId_t.h"

class CBaseFlex : public CBaseAnimGraph, public CBaseEntity::Factory<CBaseFlex>
{
public:
    DECLARE_SCHEMA_CLASS(CBaseFlex);

    SCHEMA_FIELD(CUtlVector<float>, m_flexWeight);
    SCHEMA_FIELD(Vector, m_vLookTargetPosition);
    SCHEMA_FIELD(float, m_flAllowResponsesEndTime);
    SCHEMA_FIELD(float, m_flLastFlexAnimationTime);
    SCHEMA_FIELD(SceneEventId_t, m_nNextSceneEventId);
    SCHEMA_FIELD(bool, m_bUpdateLayerPriorities);
};
