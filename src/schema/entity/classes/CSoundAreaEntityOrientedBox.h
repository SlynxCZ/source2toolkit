#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CSoundAreaEntityBase.h"

class CSoundAreaEntityOrientedBox : public CSoundAreaEntityBase
{
public:
    DECLARE_SCHEMA_CLASS(CSoundAreaEntityOrientedBox);

    SCHEMA_FIELD(Vector, m_vMin);
    SCHEMA_FIELD(Vector, m_vMax);
};
