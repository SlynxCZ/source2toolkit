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

#include "CBarnLight.h"

class COmniLight : public CBarnLight, public CBaseEntity::Factory<COmniLight>
{
public:
    DECLARE_SCHEMA_CLASS(COmniLight);

    SCHEMA_FIELD(float, m_flInnerAngle);
    SCHEMA_FIELD(float, m_flOuterAngle);
    SCHEMA_FIELD(bool, m_bShowLight);
};
