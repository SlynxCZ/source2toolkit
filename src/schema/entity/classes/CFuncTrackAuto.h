#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CFuncTrackChange.h"

class CFuncTrackAuto : public CFuncTrackChange
{
public:
    DECLARE_SCHEMA_CLASS(CFuncTrackAuto);

};
