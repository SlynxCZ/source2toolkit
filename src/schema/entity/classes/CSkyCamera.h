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

#include "CBaseEntity.h"
#include "sky3dparams_t.h"

class CSkyCamera : public CBaseEntity, public CBaseEntity::Factory<CSkyCamera>
{
public:
    DECLARE_SCHEMA_CLASS(CSkyCamera);

    SCHEMA_FIELD(sky3dparams_t, m_skyboxData);
    SCHEMA_FIELD_POINTER(CUtlStringToken, m_skyboxSlotToken);
    SCHEMA_FIELD(bool, m_bUseAngles);
    SCHEMA_FIELD(CSkyCamera*, m_pNext);
};
