#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CMarkupVolumeTagged.h"

class CSimpleMarkupVolumeTagged : public CMarkupVolumeTagged
{
public:
    DECLARE_SCHEMA_CLASS(CSimpleMarkupVolumeTagged);

};
