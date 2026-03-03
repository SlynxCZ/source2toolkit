#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CFuncPlat;

class CPlatTrigger : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPlatTrigger);

    SCHEMA_FIELD(CHandle<CFuncPlat>, m_pPlatform);
};
