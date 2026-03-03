#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseFilter.h"

class CFilterProximity : public CBaseFilter
{
public:
    DECLARE_SCHEMA_CLASS(CFilterProximity);

    SCHEMA_FIELD(float, m_flRadius);
};
