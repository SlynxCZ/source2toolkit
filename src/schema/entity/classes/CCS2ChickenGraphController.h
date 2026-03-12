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

#include "CAnimGraphControllerBase.h"

class CCS2ChickenGraphController : public CAnimGraphControllerBase, public CBaseEntity::Factory<CCS2ChickenGraphController>
{
public:
    DECLARE_SCHEMA_CLASS(CCS2ChickenGraphController);

    SCHEMA_FIELD(bool, m_bHasActionCompletedEvent);
    SCHEMA_FIELD(bool, m_bWaitingForCompletedEvent);
};
