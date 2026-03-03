#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CFuncNavObstruction : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFuncNavObstruction);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(bool, m_bUseAsyncObstacleUpdate);
};
