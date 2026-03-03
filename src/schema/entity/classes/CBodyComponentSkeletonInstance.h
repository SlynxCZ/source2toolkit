#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBodyComponent.h"
#include "CSkeletonInstance.h"

class CBodyComponentSkeletonInstance : public CBodyComponent
{
public:
    DECLARE_SCHEMA_CLASS(CBodyComponentSkeletonInstance);

    SCHEMA_FIELD(CSkeletonInstance, m_skeletonInstance);
};
