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

#include "CSceneEntity.h"

class CBaseEntity;

class CInstancedSceneEntity : public CSceneEntity, public CBaseEntity::Factory<CInstancedSceneEntity>
{
public:
    DECLARE_SCHEMA_CLASS(CInstancedSceneEntity);

    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hOwner);
    SCHEMA_FIELD(bool, m_bHadOwner);
    SCHEMA_FIELD(float, m_flPostSpeakDelay);
    SCHEMA_FIELD(float, m_flPreDelay);
    SCHEMA_FIELD(bool, m_bIsBackground);
    SCHEMA_FIELD(bool, m_bRemoveOnCompletion);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hTarget);
};
