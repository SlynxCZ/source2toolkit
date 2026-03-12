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

class CGlowProperty : public CBaseEntity::Factory<CGlowProperty>
{
public:
    DECLARE_SCHEMA_CLASS(CGlowProperty);

    SCHEMA_FIELD(Vector, m_fGlowColor);
    SCHEMA_FIELD(int32_t, m_iGlowType);
    SCHEMA_FIELD(int32_t, m_iGlowTeam);
    SCHEMA_FIELD(int32_t, m_nGlowRange);
    SCHEMA_FIELD(int32_t, m_nGlowRangeMin);
    SCHEMA_FIELD(Color, m_glowColorOverride);
    SCHEMA_FIELD(bool, m_bFlashing);
    SCHEMA_FIELD(float, m_flGlowTime);
    SCHEMA_FIELD(float, m_flGlowStartTime);
    SCHEMA_FIELD(bool, m_bEligibleForScreenHighlight);
    SCHEMA_FIELD(bool, m_bGlowing);
};
