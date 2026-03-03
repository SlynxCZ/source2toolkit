#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseClientUIEntity.h"

class CBaseEntity;

class CPointClientUIDialog : public CBaseClientUIEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPointClientUIDialog);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hActivator);
    SCHEMA_FIELD(bool, m_bStartEnabled);
};
