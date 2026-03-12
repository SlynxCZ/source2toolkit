#pragma once
#include "CBaseEntity.h"
#include "igameevents.h"
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

#include "CPointEntity.h"

class CBaseEntity;
class CFuncTrackTrain;

class CTankTrainAI : public CPointEntity, public CBaseEntity::Factory<CTankTrainAI>
{
public:
    DECLARE_SCHEMA_CLASS(CTankTrainAI);

    SCHEMA_FIELD(CHandle<CFuncTrackTrain>, m_hTrain);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hTargetEntity);
    SCHEMA_FIELD(int32_t, m_soundPlaying);
    SCHEMA_FIELD(CUtlSymbolLarge, m_startSoundName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_engineSoundName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_movementSoundName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_targetEntityName);
};
