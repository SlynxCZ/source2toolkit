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

#include "CRagdollProp.h"

class CRagdollPropAttached : public CRagdollProp
{
public:
    DECLARE_SCHEMA_CLASS(CRagdollPropAttached);

    SCHEMA_FIELD(uint32_t, m_boneIndexAttached);
    SCHEMA_FIELD(uint32_t, m_ragdollAttachedObjectIndex);
    SCHEMA_FIELD(Vector, m_attachmentPointBoneSpace);
    SCHEMA_FIELD(Vector, m_attachmentPointRagdollSpace);
    SCHEMA_FIELD(bool, m_bShouldDetach);
    SCHEMA_FIELD(bool, m_bShouldDeleteAttachedActivationRecord);
};
