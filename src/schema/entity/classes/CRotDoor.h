#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseDoor.h"

class CRotDoor : public CBaseDoor
{
public:
    DECLARE_SCHEMA_CLASS(CRotDoor);

    SCHEMA_FIELD(bool, m_bSolidBsp);
};
