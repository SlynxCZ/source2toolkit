#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CInfoPlayerStart : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CInfoPlayerStart);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(bool, m_bIsMaster);
    SCHEMA_FIELD(CGlobalSymbol, m_pPawnSubclass);
};
