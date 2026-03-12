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

#include "CBeam.h"

class CSprite;

class CEnvLaser : public CBeam, public CBaseEntity::Factory<CEnvLaser>
{
public:
    DECLARE_SCHEMA_CLASS(CEnvLaser);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszLaserTarget);
    SCHEMA_FIELD(CSprite*, m_pSprite);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszSpriteName);
    SCHEMA_FIELD(Vector, m_firePosition);
    SCHEMA_FIELD(float, m_flStartFrame);
};
