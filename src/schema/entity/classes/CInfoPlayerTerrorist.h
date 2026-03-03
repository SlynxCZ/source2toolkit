#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "SpawnPoint.h"

class CInfoPlayerTerrorist : public SpawnPoint
{
public:
    DECLARE_SCHEMA_CLASS(CInfoPlayerTerrorist);

};
