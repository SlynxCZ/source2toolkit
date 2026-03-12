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

#include "CCSGO_TeamPreviewCharacterPosition.h"

class CCSGO_TeamIntroCharacterPosition : public CCSGO_TeamPreviewCharacterPosition, public CBaseEntity::Factory<CCSGO_TeamIntroCharacterPosition>
{
public:
    DECLARE_SCHEMA_CLASS(CCSGO_TeamIntroCharacterPosition);

};
