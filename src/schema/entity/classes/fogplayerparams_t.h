#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

class CFogController;

class fogplayerparams_t
{
public:
    DECLARE_SCHEMA_CLASS(fogplayerparams_t);

    SCHEMA_FIELD(CHandle<CFogController>, m_hCtrl);
    SCHEMA_FIELD(float, m_flTransitionTime);
    SCHEMA_FIELD(Color, m_OldColor);
    SCHEMA_FIELD(float, m_flOldStart);
    SCHEMA_FIELD(float, m_flOldEnd);
    SCHEMA_FIELD(float, m_flOldMaxDensity);
    SCHEMA_FIELD(float, m_flOldHDRColorScale);
    SCHEMA_FIELD(float, m_flOldFarZ);
    SCHEMA_FIELD(Color, m_NewColor);
    SCHEMA_FIELD(float, m_flNewStart);
    SCHEMA_FIELD(float, m_flNewEnd);
    SCHEMA_FIELD(float, m_flNewMaxDensity);
    SCHEMA_FIELD(float, m_flNewHDRColorScale);
    SCHEMA_FIELD(float, m_flNewFarZ);
};
