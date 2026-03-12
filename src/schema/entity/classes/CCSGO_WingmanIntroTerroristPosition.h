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

#include "CCSGO_WingmanIntroCharacterPosition.h"

class CCSGO_WingmanIntroTerroristPosition : public CCSGO_WingmanIntroCharacterPosition, public CBaseEntity::Factory<CCSGO_WingmanIntroTerroristPosition>
{
public:
    DECLARE_SCHEMA_CLASS(CCSGO_WingmanIntroTerroristPosition);

};
