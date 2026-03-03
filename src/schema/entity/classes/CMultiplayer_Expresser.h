#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CAI_ExpresserWithFollowup.h"

class CMultiplayer_Expresser : public CAI_ExpresserWithFollowup
{
public:
    DECLARE_SCHEMA_CLASS(CMultiplayer_Expresser);

    SCHEMA_FIELD(bool, m_bAllowMultipleScenes);
};
