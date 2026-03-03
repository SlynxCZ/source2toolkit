#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CEntityComponent.h"

class CTouchExpansionComponent : public CEntityComponent
{
public:
    DECLARE_SCHEMA_CLASS(CTouchExpansionComponent);

};
