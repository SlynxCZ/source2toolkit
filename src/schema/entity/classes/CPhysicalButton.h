#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseButton.h"

class CPhysicalButton : public CBaseButton
{
public:
    DECLARE_SCHEMA_CLASS(CPhysicalButton);

};
