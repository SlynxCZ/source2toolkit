#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "SpawnPoint.h"

class CInfoDeathmatchSpawn : public SpawnPoint
{
public:
    DECLARE_SCHEMA_CLASS(CInfoDeathmatchSpawn);

};
