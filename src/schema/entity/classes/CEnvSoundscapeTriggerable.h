#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CEnvSoundscape.h"

class CEnvSoundscapeTriggerable : public CEnvSoundscape
{
public:
    DECLARE_SCHEMA_CLASS(CEnvSoundscapeTriggerable);

};
