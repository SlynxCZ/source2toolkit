#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CDynamicProp.h"

class CFuncRetakeBarrier : public CDynamicProp
{
public:
    DECLARE_SCHEMA_CLASS(CFuncRetakeBarrier);

};
