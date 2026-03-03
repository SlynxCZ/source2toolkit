#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPathSimple.h"

class CPathNode;

class CPathWithDynamicNodes : public CPathSimple
{
public:
    DECLARE_SCHEMA_CLASS(CPathWithDynamicNodes);

    SCHEMA_FIELD(CUtlVector<CHandle<CPathNode>>, m_vecPathNodes);
    SCHEMA_FIELD(CTransform, m_xInitialPathWorldToLocal);
};
