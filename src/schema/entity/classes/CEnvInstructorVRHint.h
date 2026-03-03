#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CEnvInstructorVRHint : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvInstructorVRHint);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszHintTargetEntity);
    SCHEMA_FIELD(int32_t, m_iTimeout);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszCaption);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszStartSound);
    SCHEMA_FIELD(int32_t, m_iLayoutFileType);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszCustomLayoutFile);
    SCHEMA_FIELD(int32_t, m_iAttachType);
    SCHEMA_FIELD(float, m_flHeightOffset);
};
