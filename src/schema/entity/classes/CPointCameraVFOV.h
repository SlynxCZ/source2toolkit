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

#include "CPointCamera.h"

class CPointCameraVFOV : public CPointCamera, public CBaseEntity::Factory<CPointCameraVFOV>
{
public:
    DECLARE_SCHEMA_CLASS(CPointCameraVFOV);

    SCHEMA_FIELD(float, m_flVerticalFOV);
};
