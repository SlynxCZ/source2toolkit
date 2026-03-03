#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CGameRules.h"

class CMultiplayRules : public CGameRules
{
public:
    DECLARE_SCHEMA_CLASS(CMultiplayRules);

};
