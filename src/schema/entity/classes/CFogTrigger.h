#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseTrigger.h"
#include "fogparams_t.h"

class CFogTrigger : public CBaseTrigger
{
public:
    DECLARE_SCHEMA_CLASS(CFogTrigger);

    SCHEMA_FIELD(fogparams_t, m_fog);
};
