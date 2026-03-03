#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CFuncBrush.h"

class CFuncElectrifiedVolume : public CFuncBrush
{
public:
    DECLARE_SCHEMA_CLASS(CFuncElectrifiedVolume);

    SCHEMA_FIELD(CUtlSymbolLarge, m_EffectName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_EffectInterpenetrateName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_EffectZapName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iszEffectSource);
};
