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

#include "CBaseEntity.h"

class CBeam;

class CTestEffect : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CTestEffect);

    SCHEMA_FIELD(int32_t, m_iLoop);
    SCHEMA_FIELD(int32_t, m_iBeam);
    SCHEMA_FIELD_POINTER(CHandle<CBeam>, m_pBeam);
    SCHEMA_FIELD_POINTER(float, m_flBeamTime);
    SCHEMA_FIELD(float, m_flStartTime);
};
