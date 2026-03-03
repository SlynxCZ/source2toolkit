#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CItem.h"

class CScriptItem : public CItem
{
public:
    DECLARE_SCHEMA_CLASS(CScriptItem);

    SCHEMA_FIELD(MoveType_t, m_MoveTypeOverride);
};
