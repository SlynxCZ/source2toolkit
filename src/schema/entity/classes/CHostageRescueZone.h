#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CHostageRescueZoneShim.h"

class CHostageRescueZone : public CHostageRescueZoneShim
{
public:
    DECLARE_SCHEMA_CLASS(CHostageRescueZone);

};
