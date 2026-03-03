#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "../enums/HitGroup_t.h"

class CTakeDamageInfo;

class CTakeDamageResult
{
public:
    DECLARE_SCHEMA_CLASS(CTakeDamageResult);

    SCHEMA_FIELD(CTakeDamageInfo*, m_pOriginatingInfo);
    SCHEMA_FIELD(int32_t, m_nHealthLost);
    SCHEMA_FIELD(int32_t, m_nHealthBefore);
    SCHEMA_FIELD(int32_t, m_nDamageDealt);
    SCHEMA_FIELD(float, m_flPreModifiedDamage);
    SCHEMA_FIELD(int32_t, m_nTotalledHealthLost);
    SCHEMA_FIELD(int32_t, m_nTotalledDamageDealt);
    SCHEMA_FIELD(float, m_flTotalledPreModifiedDamage);
    SCHEMA_FIELD(bool, m_bWasDamageSuppressed);
    SCHEMA_FIELD(bool, m_bSuppressFlinch);
    SCHEMA_FIELD(HitGroup_t, m_nOverrideFlinchHitGroup);
};
