#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CInfoInteraction : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CInfoInteraction);

    SCHEMA_FIELD_POINTER(CUtlSymbolLarge, m_strSlotEntityName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_strInteractVData);
    SCHEMA_FIELD(float, m_flInteractRadius);
};
