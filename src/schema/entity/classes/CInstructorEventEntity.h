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

class CBasePlayerPawn;

class CInstructorEventEntity : public CPointEntity, public CBaseEntity::Factory<CInstructorEventEntity>
{
public:
    DECLARE_SCHEMA_CLASS(CInstructorEventEntity);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszHintTargetEntity);
    SCHEMA_FIELD(CHandle<CBasePlayerPawn>, m_hTargetPlayer);
};
