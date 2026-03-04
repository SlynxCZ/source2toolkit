#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "vector.h"
#include "utlsymbol.h"
#include "utlsymbollarge.h"
#include "utlstring.h"
#include "utlstringtoken.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPlayer_MovementServices.h"

class CCSObserver_MovementServices : public CPlayer_MovementServices
{
public:
    DECLARE_SCHEMA_CLASS(CCSObserver_MovementServices);

};
