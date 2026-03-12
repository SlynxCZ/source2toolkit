#pragma once
#include "CBaseEntity.h"
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

#include "CBarnLight.h"

class CRectLight : public CBarnLight, public CBaseEntity::Factory<CRectLight>
{
public:
    DECLARE_SCHEMA_CLASS(CRectLight);

    SCHEMA_FIELD(bool, m_bShowLight);
};
