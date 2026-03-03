#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CModelPointEntity.h"

class CRevertSaved : public CModelPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CRevertSaved);

    SCHEMA_FIELD(float, m_loadTime);
    SCHEMA_FIELD(float, m_Duration);
    SCHEMA_FIELD(float, m_HoldTime);
};
