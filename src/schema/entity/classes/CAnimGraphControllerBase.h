#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "ExternalAnimGraphHandle_t.h"

class CAnimGraphControllerBase
{
public:
    DECLARE_SCHEMA_CLASS(CAnimGraphControllerBase);

    SCHEMA_FIELD(ExternalAnimGraphHandle_t, m_hExternalGraph);
};
