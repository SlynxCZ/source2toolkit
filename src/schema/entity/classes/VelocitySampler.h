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

class VelocitySampler : public CBaseEntity::Factory<VelocitySampler>
{
public:
    DECLARE_SCHEMA_CLASS(VelocitySampler);

    SCHEMA_FIELD(Vector, m_prevSample);
    SCHEMA_FIELD(float, m_fPrevSampleTime);
    SCHEMA_FIELD(float, m_fIdealSampleRate);
};
