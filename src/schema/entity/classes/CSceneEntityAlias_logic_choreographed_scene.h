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

#include "CSceneEntity.h"

class CSceneEntityAlias_logic_choreographed_scene : public CSceneEntity, public CBaseEntity::Factory<CSceneEntityAlias_logic_choreographed_scene>
{
public:
    DECLARE_SCHEMA_CLASS(CSceneEntityAlias_logic_choreographed_scene);

};
