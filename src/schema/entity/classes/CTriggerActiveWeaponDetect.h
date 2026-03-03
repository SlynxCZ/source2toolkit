#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CTriggerActiveWeaponDetect : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerActiveWeaponDetect);

    SCHEMA_FIELD(CEntityIOOutput, m_OnTouchedActiveWeapon);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszWeaponClassName);
};
