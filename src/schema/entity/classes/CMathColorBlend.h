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

#include "CLogicalEntity.h"

class CMathColorBlend : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CMathColorBlend);

    SCHEMA_FIELD(float, m_flInMin);
    SCHEMA_FIELD(float, m_flInMax);
    SCHEMA_FIELD(Color, m_OutColor1);
    SCHEMA_FIELD(Color, m_OutColor2);
};
