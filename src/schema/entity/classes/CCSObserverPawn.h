#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CCSPlayerPawnBase.h"

class CCSObserverPawn : public CCSPlayerPawnBase
{
public:
    DECLARE_SCHEMA_CLASS(CCSObserverPawn);

};
