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

#include "CMarkupVolume.h"

class CMarkupVolumeTagged : public CMarkupVolume, public CBaseEntity::Factory<CMarkupVolumeTagged>
{
public:
    DECLARE_SCHEMA_CLASS(CMarkupVolumeTagged);

    SCHEMA_FIELD(CUtlVector<CGlobalSymbol>, m_GroupNames);
    SCHEMA_FIELD(CUtlVector<CGlobalSymbol>, m_Tags);
    SCHEMA_FIELD(bool, m_bIsGroup);
    SCHEMA_FIELD(bool, m_bGroupByPrefab);
    SCHEMA_FIELD(bool, m_bGroupByVolume);
    SCHEMA_FIELD(bool, m_bGroupOtherGroups);
    SCHEMA_FIELD(bool, m_bIsInGroup);
};
