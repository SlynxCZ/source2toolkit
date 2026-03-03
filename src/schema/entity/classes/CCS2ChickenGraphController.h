#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CAnimGraphControllerBase.h"

class CCS2ChickenGraphController : public CAnimGraphControllerBase
{
public:
    DECLARE_SCHEMA_CLASS(CCS2ChickenGraphController);

    SCHEMA_FIELD(CAnimGraph2ParamAutoResetOptionalRef, m_bActionReset);
    SCHEMA_FIELD(bool, m_bHasActionCompletedEvent);
    SCHEMA_FIELD(bool, m_bWaitingForCompletedEvent);
};
