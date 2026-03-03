#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"
#include "dynpitchvol_t.h"
#include "../enums/soundlevel_t.h"

class CBaseEntity;

class CAmbientGeneric : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CAmbientGeneric);

    SCHEMA_FIELD(float, m_radius);
    SCHEMA_FIELD(float, m_flMaxRadius);
    SCHEMA_FIELD(soundlevel_t, m_iSoundLevel);
    SCHEMA_FIELD(dynpitchvol_t, m_dpv);
    SCHEMA_FIELD(bool, m_fActive);
    SCHEMA_FIELD(bool, m_fLooping);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszSound);
    SCHEMA_FIELD(CUtlSymbolLarge, m_sSourceEntName);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hSoundSource);
    SCHEMA_FIELD(CEntityIndex, m_nSoundSourceEntIndex);
};
