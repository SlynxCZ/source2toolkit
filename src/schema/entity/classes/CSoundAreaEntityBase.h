#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseEntity.h"

class CSoundAreaEntityBase : public CBaseEntity
{
public:
    DECLARE_SCHEMA_CLASS(CSoundAreaEntityBase);

    SCHEMA_FIELD(bool, m_bDisabled);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszSoundAreaType);
    SCHEMA_FIELD(Vector, m_vPos);
};
