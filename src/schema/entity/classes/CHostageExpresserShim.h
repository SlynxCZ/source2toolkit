#pragma once
#include "ehandle.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseCombatCharacter.h"

class CAI_Expresser;

class CHostageExpresserShim : public CBaseCombatCharacter
{
public:
    DECLARE_SCHEMA_CLASS(CHostageExpresserShim);

    SCHEMA_FIELD(CAI_Expresser*, m_pExpresser);
};
