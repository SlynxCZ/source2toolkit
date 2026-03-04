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

#include "CInfoDynamicShadowHint.h"

class CInfoDynamicShadowHintBox : public CInfoDynamicShadowHint
{
public:
    DECLARE_SCHEMA_CLASS(CInfoDynamicShadowHintBox);

    SCHEMA_FIELD(Vector, m_vBoxMins);
    SCHEMA_FIELD(Vector, m_vBoxMaxs);
};
