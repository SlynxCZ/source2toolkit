#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointClientUIWorldPanel.h"

class CPointClientUIWorldTextPanel : public CPointClientUIWorldPanel
{
public:
    DECLARE_SCHEMA_CLASS(CPointClientUIWorldTextPanel);

    SCHEMA_FIELD_POINTER(char, m_messageText);
};
