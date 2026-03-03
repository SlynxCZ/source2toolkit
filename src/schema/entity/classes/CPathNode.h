#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CPathWithDynamicNodes;

class CPathNode : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CPathNode);

    SCHEMA_FIELD(Vector, m_vInTangentLocal);
    SCHEMA_FIELD(Vector, m_vOutTangentLocal);
    SCHEMA_FIELD(CUtlString, m_strParentPathUniqueID);
    SCHEMA_FIELD(CUtlString, m_strPathNodeParameter);
    SCHEMA_FIELD(CTransform, m_xWSPrevParent);
    SCHEMA_FIELD(CHandle<CPathWithDynamicNodes>, m_hPath);
};
