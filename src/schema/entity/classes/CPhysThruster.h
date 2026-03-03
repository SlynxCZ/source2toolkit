#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPhysForce.h"

class CPhysThruster : public CPhysForce
{
public:
    DECLARE_SCHEMA_CLASS(CPhysThruster);

    SCHEMA_FIELD(Vector, m_localOrigin);
};
