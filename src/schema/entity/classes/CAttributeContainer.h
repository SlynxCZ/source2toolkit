#pragma once
#include "igameevents.h"
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

#include "CAttributeManager.h"
#include "CEconItemView.h"

class CAttributeContainer : public CAttributeManager
{
public:
    DECLARE_SCHEMA_CLASS(CAttributeContainer);

    SCHEMA_FIELD(CEconItemView, m_Item);
};
