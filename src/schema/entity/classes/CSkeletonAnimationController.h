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

#include "ISkeletonAnimationController.h"

class CSkeletonInstance;

class CSkeletonAnimationController : public ISkeletonAnimationController, public CBaseEntity::Factory<CSkeletonAnimationController>
{
public:
    DECLARE_SCHEMA_CLASS(CSkeletonAnimationController);

    SCHEMA_FIELD(CSkeletonInstance*, m_pSkeletonInstance);
};
