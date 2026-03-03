#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CTankTargetChange : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CTankTargetChange);

    SCHEMA_FIELD(CUtlSymbolLarge, m_newTargetName);
};
