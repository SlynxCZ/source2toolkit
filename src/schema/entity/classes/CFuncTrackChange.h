#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CFuncPlatRot.h"
#include "../enums/TRAIN_CODE.h"

class CFuncTrackTrain;
class CPathTrack;

class CFuncTrackChange : public CFuncPlatRot
{
public:
    DECLARE_SCHEMA_CLASS(CFuncTrackChange);

    SCHEMA_FIELD(CPathTrack*, m_trackTop);
    SCHEMA_FIELD(CPathTrack*, m_trackBottom);
    SCHEMA_FIELD(CFuncTrackTrain*, m_train);
    SCHEMA_FIELD(CUtlSymbolLarge, m_trackTopName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_trackBottomName);
    SCHEMA_FIELD(CUtlSymbolLarge, m_trainName);
    SCHEMA_FIELD(TRAIN_CODE, m_code);
    SCHEMA_FIELD(int32_t, m_targetState);
    SCHEMA_FIELD(int32_t, m_use);
};
