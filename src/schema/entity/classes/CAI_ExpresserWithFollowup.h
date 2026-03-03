#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CAI_Expresser.h"

class CAI_ExpresserWithFollowup : public CAI_Expresser
{
public:
    DECLARE_SCHEMA_CLASS(CAI_ExpresserWithFollowup);

};
