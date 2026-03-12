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

#include "CBaseFlex.h"

class CBaseFlexAlias_funCBaseFlex : public CBaseFlex, public CBaseEntity::Factory<CBaseFlexAlias_funCBaseFlex>
{
public:
    DECLARE_SCHEMA_CLASS(CBaseFlexAlias_funCBaseFlex);

};
