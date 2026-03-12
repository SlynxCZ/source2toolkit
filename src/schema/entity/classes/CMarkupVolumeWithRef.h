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

#include "CMarkupVolumeTagged.h"

class CMarkupVolumeWithRef : public CMarkupVolumeTagged, public CBaseEntity::Factory<CMarkupVolumeWithRef>
{
public:
    DECLARE_SCHEMA_CLASS(CMarkupVolumeWithRef);

    SCHEMA_FIELD(bool, m_bUseRef);
    SCHEMA_FIELD(Vector, m_vRefPosEntitySpace);
    SCHEMA_FIELD(Vector, m_vRefPosWorldSpace);
    SCHEMA_FIELD(float, m_flRefDot);
};
