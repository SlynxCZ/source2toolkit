#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CEntityComponent.h"

class CHitboxComponent : public CEntityComponent
{
public:
    DECLARE_SCHEMA_CLASS(CHitboxComponent);

    SCHEMA_FIELD(float, m_flBoundsExpandRadius);
};
