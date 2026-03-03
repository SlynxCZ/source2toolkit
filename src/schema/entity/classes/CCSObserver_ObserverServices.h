#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPlayer_ObserverServices.h"

class CCSObserver_ObserverServices : public CPlayer_ObserverServices
{
public:
    DECLARE_SCHEMA_CLASS(CCSObserver_ObserverServices);

};
