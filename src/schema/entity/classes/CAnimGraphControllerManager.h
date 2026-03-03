#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CAnimGraphControllerBase;

class CAnimGraphControllerManager
{
public:
    DECLARE_SCHEMA_CLASS(CAnimGraphControllerManager);

    SCHEMA_FIELD(CUtlVector<CAnimGraphControllerBase*>, m_controllers);
    SCHEMA_FIELD(bool, m_bGraphBindingsCreated);
};
