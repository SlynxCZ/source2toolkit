#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CSoundEventEntity.h"

class CSoundEventSphereEntity : public CSoundEventEntity
{
public:
    DECLARE_SCHEMA_CLASS(CSoundEventSphereEntity);

    SCHEMA_FIELD(float, m_flRadius);
};
