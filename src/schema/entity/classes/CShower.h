#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CModelPointEntity.h"

class CShower : public CModelPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CShower);

};
