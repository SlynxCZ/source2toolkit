#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CBasePlayerPawn;

class CInstructorEventEntity : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CInstructorEventEntity);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszHintTargetEntity);
    SCHEMA_FIELD(CHandle<CBasePlayerPawn>, m_hTargetPlayer);
};
