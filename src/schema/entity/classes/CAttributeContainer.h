#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
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
