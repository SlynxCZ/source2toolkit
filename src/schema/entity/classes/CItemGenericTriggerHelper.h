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

class CItemGeneric;

class CItemGenericTriggerHelper : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CItemGenericTriggerHelper);

    SCHEMA_FIELD(CHandle<CItemGeneric>, m_hParentItem);
};
