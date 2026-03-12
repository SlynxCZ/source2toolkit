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

#include "CBaseEntity.h"

class CSkyCamera;

class CSkyboxReference : public CBaseEntity, public CBaseEntity::Factory<CSkyboxReference>
{
public:
    DECLARE_SCHEMA_CLASS(CSkyboxReference);

    SCHEMA_FIELD(WorldGroupId_t, m_worldGroupId);
    SCHEMA_FIELD(CHandle<CSkyCamera>, m_hSkyCamera);
};
