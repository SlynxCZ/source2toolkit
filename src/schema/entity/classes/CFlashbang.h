#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseCSGrenade.h"

class CFlashbang : public CBaseCSGrenade
{
public:
    DECLARE_SCHEMA_CLASS(CFlashbang);

};
