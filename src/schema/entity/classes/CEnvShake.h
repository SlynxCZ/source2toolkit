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

#include "CPhysicsShake.h"
#include "CPointEntity.h"

class CEnvShake : public CPointEntity
{
public:
    DECLARE_SCHEMA_CLASS(CEnvShake);

    SCHEMA_FIELD(CUtlSymbolLarge, m_limitToEntity);
    SCHEMA_FIELD(float, m_Amplitude);
    SCHEMA_FIELD(float, m_Frequency);
    SCHEMA_FIELD(float, m_Duration);
    SCHEMA_FIELD(float, m_Radius);
    SCHEMA_FIELD(float, m_stopTime);
    SCHEMA_FIELD(float, m_nextShake);
    SCHEMA_FIELD(float, m_currentAmp);
    SCHEMA_FIELD(Vector, m_maxForce);
    SCHEMA_FIELD(CPhysicsShake, m_shakeCallback);
};
