#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseCSGrenadeProjectile.h"

class CFlashbangProjectile : public CBaseCSGrenadeProjectile
{
public:
    DECLARE_SCHEMA_CLASS(CFlashbangProjectile);

    SCHEMA_FIELD(float, m_flTimeToDetonate);
    SCHEMA_FIELD(uint8_t, m_numOpponentsHit);
    SCHEMA_FIELD(uint8_t, m_numTeammatesHit);
};
