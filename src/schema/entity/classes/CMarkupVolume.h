#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"

class CMarkupVolume : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CMarkupVolume);

    SCHEMA_FIELD(bool, m_bDisabled);
};
