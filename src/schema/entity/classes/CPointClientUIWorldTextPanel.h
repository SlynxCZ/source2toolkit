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

#include "CPointClientUIWorldPanel.h"

class CPointClientUIWorldTextPanel : public CPointClientUIWorldPanel, public CBaseEntity::Factory<CPointClientUIWorldTextPanel>
{
public:
    DECLARE_SCHEMA_CLASS(CPointClientUIWorldTextPanel);

    SCHEMA_FIELD_POINTER(char, m_messageText);
};
