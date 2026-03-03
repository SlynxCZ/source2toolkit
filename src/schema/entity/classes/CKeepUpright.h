#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CBaseEntity;

class CKeepUpright : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CKeepUpright);

    SCHEMA_FIELD(Vector, m_worldGoalAxis);
    SCHEMA_FIELD(Vector, m_localTestAxis);
    SCHEMA_FIELD(CUtlSymbolLarge, m_nameAttach);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_attachedObject);
    SCHEMA_FIELD(float, m_angularLimit);
    SCHEMA_FIELD(bool, m_bActive);
    SCHEMA_FIELD(bool, m_bDampAllRotation);
};
