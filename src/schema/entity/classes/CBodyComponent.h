#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CEntityComponent.h"
#include "CNetworkVarChainer.h"

class CGameSceneNode;

class CBodyComponent : public CEntityComponent
{
public:
    DECLARE_SCHEMA_CLASS(CBodyComponent);

    SCHEMA_FIELD(CGameSceneNode*, m_pSceneNode);
    SCHEMA_FIELD(CNetworkVarChainer, __m_pChainEntity);
};
