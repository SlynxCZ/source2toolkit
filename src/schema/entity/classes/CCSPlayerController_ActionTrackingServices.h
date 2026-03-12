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

#include "CPlayerControllerComponent.h"
#include "CSMatchStats_t.h"
#include "CSPerRoundStats_t.h"

class CCSPlayerController_ActionTrackingServices : public CPlayerControllerComponent, public CBaseEntity::Factory<CCSPlayerController_ActionTrackingServices>
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayerController_ActionTrackingServices);

    SCHEMA_FIELD(CUtlVector<CSPerRoundStats_t>, m_perRoundStats);
    SCHEMA_FIELD(CSMatchStats_t, m_matchStats);
    SCHEMA_FIELD(int32_t, m_iNumRoundKills);
    SCHEMA_FIELD(int32_t, m_iNumRoundKillsHeadshots);
    SCHEMA_FIELD(float, m_flTotalRoundDamageDealt);
};
