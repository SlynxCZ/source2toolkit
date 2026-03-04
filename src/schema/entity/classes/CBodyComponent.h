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


class CGameSceneNode;

class CBodyComponent : public CEntityComponent
{
public:
    DECLARE_SCHEMA_CLASS(CBodyComponent);

    SCHEMA_FIELD(CGameSceneNode*, m_pSceneNode);
    SCHEMA_FIELD(CEntityInstance*, __m_pChainEntity);
};
