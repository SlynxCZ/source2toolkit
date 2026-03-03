#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"
#include "InfoForResourceTypeIMaterial2.h"

class CBaseEntity;

class CRopeKeyframe : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CRopeKeyframe);

    SCHEMA_FIELD(uint16_t, m_RopeFlags);
    SCHEMA_FIELD(CUtlSymbolLarge, m_iNextLinkName);
    SCHEMA_FIELD(int16_t, m_Slack);
    SCHEMA_FIELD(float, m_Width);
    SCHEMA_FIELD(float, m_TextureScale);
    SCHEMA_FIELD(uint8_t, m_nSegments);
    SCHEMA_FIELD(bool, m_bConstrainBetweenEndpoints);
    SCHEMA_FIELD(CUtlSymbolLarge, m_strRopeMaterialModel);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeIMaterial2 >, m_iRopeMaterialModelIndex);
    SCHEMA_FIELD(uint8_t, m_Subdiv);
    SCHEMA_FIELD(uint8_t, m_nChangeCount);
    SCHEMA_FIELD(int16_t, m_RopeLength);
    SCHEMA_FIELD(uint8_t, m_fLockedPoints);
    SCHEMA_FIELD(bool, m_bCreatedFromMapFile);
    SCHEMA_FIELD(float, m_flScrollSpeed);
    SCHEMA_FIELD(bool, m_bStartPointValid);
    SCHEMA_FIELD(bool, m_bEndPointValid);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hStartPoint);
    SCHEMA_FIELD(CHandle<CBaseEntity>, m_hEndPoint);
};
