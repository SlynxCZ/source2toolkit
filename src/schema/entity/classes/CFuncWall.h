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

#include "CBaseModelEntity.h"

class CFuncWall : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFuncWall);

    SCHEMA_FIELD(int32_t, m_nState);
};
