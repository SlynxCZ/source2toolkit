#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "ISkeletonAnimationController.h"

class CSkeletonInstance;

class CSkeletonAnimationController : public ISkeletonAnimationController
{
public:
    DECLARE_SCHEMA_CLASS(CSkeletonAnimationController);

    SCHEMA_FIELD(CSkeletonInstance*, m_pSkeletonInstance);
};
