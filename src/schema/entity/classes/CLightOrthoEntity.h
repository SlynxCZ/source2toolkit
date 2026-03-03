#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CLightEntity.h"

class CLightOrthoEntity : public CLightEntity
{
public:
    DECLARE_SCHEMA_CLASS(CLightOrthoEntity);

};
