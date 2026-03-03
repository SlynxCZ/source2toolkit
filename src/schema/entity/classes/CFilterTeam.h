#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseFilter.h"

class CFilterTeam : public CBaseFilter
{
public:
    DECLARE_SCHEMA_CLASS(CFilterTeam);

    SCHEMA_FIELD(int32_t, m_iFilterTeam);
};
