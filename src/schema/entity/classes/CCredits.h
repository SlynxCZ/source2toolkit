#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CPointEntity.h"

class CCredits : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CCredits);

    SCHEMA_FIELD(CEntityIOOutput, m_OnCreditsDone);
    SCHEMA_FIELD(bool, m_bRolledOutroCredits);
    SCHEMA_FIELD(float, m_flLogoLength);
};
