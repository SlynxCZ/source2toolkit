#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CFuncTrackTrain.h"

class CFuncTankTrain : public CFuncTrackTrain
{
public:
    DECLARE_SCHEMA_CLASS(CFuncTankTrain);

    SCHEMA_FIELD(CEntityIOOutput, m_OnDeath);
};
