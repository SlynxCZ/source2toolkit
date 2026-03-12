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

#include "CPlayerPawnComponent.h"

class CCSPlayer_RadioServices : public CPlayerPawnComponent, public CBaseEntity::Factory<CCSPlayer_RadioServices>
{
public:
    DECLARE_SCHEMA_CLASS(CCSPlayer_RadioServices);

    SCHEMA_FIELD(float, m_flGotHostageTalkTimer);
    SCHEMA_FIELD(float, m_flDefusingTalkTimer);
    SCHEMA_FIELD(float, m_flC4PlantTalkTimer);
    SCHEMA_FIELD_POINTER(float, m_flRadioTokenSlots);
    SCHEMA_FIELD(bool, m_bIgnoreRadio);
};
