#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBodyComponent.h"
#include "CGameSceneNode.h"

class CBodyComponentPoint : public CBodyComponent
{
public:
    DECLARE_SCHEMA_CLASS(CBodyComponentPoint);

    SCHEMA_FIELD(CGameSceneNode, m_sceneNode);
};
