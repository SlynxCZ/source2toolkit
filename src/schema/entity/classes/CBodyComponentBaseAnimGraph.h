#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseAnimGraphController.h"
#include "CBodyComponentSkeletonInstance.h"

class CBodyComponentBaseAnimGraph : public CBodyComponentSkeletonInstance
{
public:
    DECLARE_SCHEMA_CLASS(CBodyComponentBaseAnimGraph);

    SCHEMA_FIELD(CBaseAnimGraphController, m_animationController);
};
