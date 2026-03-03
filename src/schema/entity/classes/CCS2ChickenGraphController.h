#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CAnimGraphControllerBase.h"

class CCS2ChickenGraphController : public CAnimGraphControllerBase
{
public:
    DECLARE_SCHEMA_CLASS(CCS2ChickenGraphController);

    SCHEMA_FIELD(bool, m_bHasActionCompletedEvent);
    SCHEMA_FIELD(bool, m_bWaitingForCompletedEvent);
};
