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

class CHandleTest : public CBaseEntity, public CBaseEntity::Factory<CHandleTest>
{
public:
    DECLARE_SCHEMA_CLASS(CHandleTest);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_Handle);
    SCHEMA_FIELD(bool, m_bSendHandle);
};
