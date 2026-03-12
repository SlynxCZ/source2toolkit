#pragma once
#include "CBaseEntity.h"
#include "igameevents.h"
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

#include "CBaseModelEntity.h"
#include "InfoForResourceTypeCTextureBase.h"

class CTextureBasedAnimatable : public CBaseModelEntity, public CBaseEntity::Factory<CTextureBasedAnimatable>
{
public:
    DECLARE_SCHEMA_CLASS(CTextureBasedAnimatable);

    SCHEMA_FIELD(bool, m_bLoop);
    SCHEMA_FIELD(float, m_flFPS);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_hPositionKeys);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeCTextureBase >, m_hRotationKeys);
    SCHEMA_FIELD(Vector, m_vAnimationBoundsMin);
    SCHEMA_FIELD(Vector, m_vAnimationBoundsMax);
    SCHEMA_FIELD(float, m_flStartTime);
    SCHEMA_FIELD(float, m_flStartFrame);
};
