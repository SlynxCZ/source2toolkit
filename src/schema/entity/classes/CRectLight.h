#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBarnLight.h"

class CRectLight : public CBarnLight
{
public:
    DECLARE_SCHEMA_CLASS(CRectLight);

    SCHEMA_FIELD(bool, m_bShowLight);
};
