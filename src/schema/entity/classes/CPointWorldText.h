#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CModelPointEntity.h"
#include "../enums/PointWorldTextJustifyHorizontal_t.h"
#include "../enums/PointWorldTextJustifyVertical_t.h"
#include "../enums/PointWorldTextReorientMode_t.h"

class CPointWorldText : public CModelPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointWorldText);

    SCHEMA_FIELD_POINTER(char, m_messageText);
    SCHEMA_FIELD_POINTER(char, m_FontName);
    SCHEMA_FIELD_POINTER(char, m_BackgroundMaterialName);
    SCHEMA_FIELD(bool, m_bEnabled);
    SCHEMA_FIELD(bool, m_bFullbright);
    SCHEMA_FIELD(float, m_flWorldUnitsPerPx);
    SCHEMA_FIELD(float, m_flFontSize);
    SCHEMA_FIELD(float, m_flDepthOffset);
    SCHEMA_FIELD(bool, m_bDrawBackground);
    SCHEMA_FIELD(float, m_flBackgroundBorderWidth);
    SCHEMA_FIELD(float, m_flBackgroundBorderHeight);
    SCHEMA_FIELD(float, m_flBackgroundWorldToUV);
    SCHEMA_FIELD(Color, m_Color);
    SCHEMA_FIELD(PointWorldTextJustifyHorizontal_t, m_nJustifyHorizontal);
    SCHEMA_FIELD(PointWorldTextJustifyVertical_t, m_nJustifyVertical);
    SCHEMA_FIELD(PointWorldTextReorientMode_t, m_nReorientMode);
};
