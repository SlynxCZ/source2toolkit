#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CEnvSoundscape.h"

class CEnvSoundscapeProxy : public CEnvSoundscape
{
public:
    DECLARE_SCHEMA_CLASS(CEnvSoundscapeProxy);

    SCHEMA_FIELD(CUtlSymbolLarge, m_MainSoundscapeName);
};
