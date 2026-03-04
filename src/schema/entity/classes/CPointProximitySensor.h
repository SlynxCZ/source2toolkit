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

#include "CPointEntity.h"

class CBaseEntity;

class CPointProximitySensor : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointProximitySensor);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hTargetEntity);
};
