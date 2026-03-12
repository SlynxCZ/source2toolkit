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

#include "CCSGO_TeamIntroCharacterPosition.h"

class CCSGO_WingmanIntroCharacterPosition : public CCSGO_TeamIntroCharacterPosition, public CBaseEntity::Factory<CCSGO_WingmanIntroCharacterPosition>
{
public:
    DECLARE_SCHEMA_CLASS(CCSGO_WingmanIntroCharacterPosition);

};
