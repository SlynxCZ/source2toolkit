#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CFuncWall.h"

class CFuncWallToggle : public CFuncWall
{
public:
    DECLARE_SCHEMA_CLASS(CFuncWallToggle);

};
