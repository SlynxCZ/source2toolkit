#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CRuleEntity.h"

class CRulePointEntity : public CRuleEntity
{
public:
    DECLARE_SCHEMA_CLASS(CRulePointEntity);

    SCHEMA_FIELD(int32_t, m_Score);
};
