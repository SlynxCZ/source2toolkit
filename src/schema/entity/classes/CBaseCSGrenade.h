#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CCSWeaponBase.h"

class CBaseCSGrenade : public CCSWeaponBase
{
public:
    DECLARE_SCHEMA_CLASS(CBaseCSGrenade);

    SCHEMA_FIELD(bool, m_bRedraw);
    SCHEMA_FIELD(bool, m_bIsHeldByPlayer);
    SCHEMA_FIELD(bool, m_bPinPulled);
    SCHEMA_FIELD(bool, m_bJumpThrow);
    SCHEMA_FIELD(bool, m_bThrowAnimating);
    SCHEMA_FIELD(float, m_fThrowTime);
    SCHEMA_FIELD(float, m_flThrowStrength);
    SCHEMA_FIELD(float, m_fDropTime);
    SCHEMA_FIELD(float, m_fPinPullTime);
    SCHEMA_FIELD(bool, m_bJustPulledPin);
    SCHEMA_FIELD(int32_t, m_nNextHoldTick);
    SCHEMA_FIELD(float, m_flNextHoldFrac);
    SCHEMA_FIELD(CHandle<CCSWeaponBase>, m_hSwitchToWeaponAfterThrow);
};
