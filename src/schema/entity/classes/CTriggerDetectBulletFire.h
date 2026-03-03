#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CTriggerDetectBulletFire : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CTriggerDetectBulletFire);

    SCHEMA_FIELD(bool, m_bPlayerFireOnly);
    SCHEMA_FIELD(CEntityIOOutput, m_OnDetectedBulletFire);
};
