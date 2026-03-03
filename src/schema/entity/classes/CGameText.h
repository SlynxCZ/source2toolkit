#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CRulePointEntity.h"
#include "hudtextparms_t.h"

class CGameText : public CRulePointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CGameText);

    SCHEMA_FIELD(CUtlSymbolLarge, m_iszMessage);
    SCHEMA_FIELD(hudtextparms_t, m_textParms);
};
