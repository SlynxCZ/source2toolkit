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

class CAnimGraphControllerBase;

class CAnimGraphControllerManager : public CBaseEntity::Factory<CAnimGraphControllerManager>
{
public:
    DECLARE_SCHEMA_CLASS(CAnimGraphControllerManager);

    SCHEMA_FIELD(CUtlVector<CAnimGraphControllerBase*>, m_controllers);
    SCHEMA_FIELD(bool, m_bGraphBindingsCreated);
};
