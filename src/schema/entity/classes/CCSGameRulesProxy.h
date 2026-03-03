#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CGameRulesProxy.h"

class CCSGameRules;

class CCSGameRulesProxy : public CGameRulesProxy
{
public:
    DECLARE_SCHEMA_CLASS(CCSGameRulesProxy);

    SCHEMA_FIELD(CCSGameRules*, m_pGameRules);
};
