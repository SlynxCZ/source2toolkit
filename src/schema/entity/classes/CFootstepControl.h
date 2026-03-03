#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"

class CFootstepControl : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CFootstepControl);

    SCHEMA_FIELD(CUtlSymbolLarge, m_source);
    SCHEMA_FIELD(CUtlSymbolLarge, m_destination);
};
