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

#include "CRotButton.h"

class CMomentaryRotButton : public CRotButton, public CBaseEntity::Factory<CMomentaryRotButton>
{
public:
    DECLARE_SCHEMA_CLASS(CMomentaryRotButton);

    SCHEMA_FIELD(CEntityIOOutput, m_OnUnpressed);
    SCHEMA_FIELD(CEntityIOOutput, m_OnFullyOpen);
    SCHEMA_FIELD(CEntityIOOutput, m_OnFullyClosed);
    SCHEMA_FIELD(CEntityIOOutput, m_OnReachedPosition);
    SCHEMA_FIELD(int32_t, m_lastUsed);
    SCHEMA_FIELD(QAngle, m_start);
    SCHEMA_FIELD(QAngle, m_end);
    SCHEMA_FIELD(float, m_IdealYaw);
    SCHEMA_FIELD(CUtlSymbolLarge, m_sNoise);
    SCHEMA_FIELD(bool, m_bUpdateTarget);
    SCHEMA_FIELD(int32_t, m_direction);
    SCHEMA_FIELD(float, m_returnSpeed);
    SCHEMA_FIELD(float, m_flStartPosition);
};
