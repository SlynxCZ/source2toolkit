#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CMessageEntity : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CMessageEntity);

    SCHEMA_FIELD(int32_t, m_radius);
    SCHEMA_FIELD(CUtlSymbolLarge, m_messageText);
    SCHEMA_FIELD(bool, m_drawText);
    SCHEMA_FIELD(bool, m_bDeveloperOnly);
    SCHEMA_FIELD(bool, m_bEnabled);
};
