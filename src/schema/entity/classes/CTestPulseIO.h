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

class CTestPulseIO : public CLogicalEntity
{
public:
    DECLARE_SCHEMA_CLASS(CTestPulseIO);

    SCHEMA_FIELD(CEntityIOOutput, m_OnVariantVoid);
    SCHEMA_FIELD(bool, m_bAllowEmptyInputs);
};
