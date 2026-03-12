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

#include "CLogicalEntity.h"

class CPathKeyFrame : public CLogicalEntity, public CBaseEntity::Factory<CPathKeyFrame>
{
public:
    DECLARE_SCHEMA_CLASS(CPathKeyFrame);

    SCHEMA_FIELD(Vector, m_Origin);
    SCHEMA_FIELD(QAngle, m_Angles);
    SCHEMA_FIELD(Quaternion, m_qAngle);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iNextKey);
    SCHEMA_FIELD(float, m_flNextTime);
    SCHEMA_FIELD(CPathKeyFrame*, m_pNextKey);
    SCHEMA_FIELD(CPathKeyFrame*, m_pPrevKey);
    SCHEMA_FIELD(float, m_flMoveSpeed);
};
