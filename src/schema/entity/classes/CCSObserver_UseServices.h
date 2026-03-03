#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPlayer_UseServices.h"

class CCSObserver_UseServices : public CPlayer_UseServices
{
public:
    DECLARE_SCHEMA_CLASS(CCSObserver_UseServices);

};
