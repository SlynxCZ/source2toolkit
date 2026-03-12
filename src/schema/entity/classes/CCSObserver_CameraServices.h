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

#include "CCSPlayerBase_CameraServices.h"

class CCSObserver_CameraServices : public CCSPlayerBase_CameraServices, public CBaseEntity::Factory<CCSObserver_CameraServices>
{
public:
    DECLARE_SCHEMA_CLASS(CCSObserver_CameraServices);

};
