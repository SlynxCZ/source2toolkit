#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CRulePointEntity.h"

class CGamePlayerEquip : public CRulePointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CGamePlayerEquip);

};
