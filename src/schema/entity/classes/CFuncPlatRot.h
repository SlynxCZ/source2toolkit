#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CFuncPlat.h"

class CFuncPlatRot : public CFuncPlat
{
public:
    DECLARE_SCHEMA_CLASS(CFuncPlatRot);

    SCHEMA_FIELD(QAngle, m_end);
    SCHEMA_FIELD(QAngle, m_start);
};
