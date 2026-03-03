#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseToggle.h"

class CBaseEntity;

class CGunTarget : public CBaseToggle
{
public:
    DECLARE_SCHEMA_CLASS(CGunTarget);

    SCHEMA_FIELD(bool, m_on);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hTargetEnt);
    SCHEMA_FIELD(CEntityIOOutput, m_OnDeath);
};
