#pragma once
#include "ehandle.h"
#include "entityhandle.h"
#include "utlsymbollarge.h"
#include "schema/entityio.h"
#include "schema/schema.h"
#include <cstdint>

#include "CBaseModelEntity.h"
#include "InfoForResourceTypeIMaterial2.h"

class CFuncShatterglass : public CBaseModelEntity
{
public:
    DECLARE_SCHEMA_CLASS(CFuncShatterglass);

    SCHEMA_FIELD(matrix3x4_t, m_matPanelTransform);
    SCHEMA_FIELD(matrix3x4_t, m_matPanelTransformWsTemp);
    SCHEMA_FIELD(CUtlVector<uint32_t>, m_vecShatterGlassShards);
    SCHEMA_FIELD(Vector2D, m_PanelSize);
    SCHEMA_FIELD(float, m_flLastShatterSoundEmitTime);
    SCHEMA_FIELD(float, m_flLastCleanupTime);
    SCHEMA_FIELD(float, m_flInitAtTime);
    SCHEMA_FIELD(float, m_flGlassThickness);
    SCHEMA_FIELD(float, m_flSpawnInvulnerability);
    SCHEMA_FIELD(bool, m_bBreakSilent);
    SCHEMA_FIELD(bool, m_bBreakShardless);
    SCHEMA_FIELD(bool, m_bBroken);
    SCHEMA_FIELD(bool, m_bGlassNavIgnore);
    SCHEMA_FIELD(bool, m_bGlassInFrame);
    SCHEMA_FIELD(bool, m_bStartBroken);
    SCHEMA_FIELD(uint8_t, m_iInitialDamageType);
    SCHEMA_FIELD(CUtlSymbolLarge, m_szDamagePositioningEntityName01);
    SCHEMA_FIELD(CUtlSymbolLarge, m_szDamagePositioningEntityName02);
    SCHEMA_FIELD(CUtlSymbolLarge, m_szDamagePositioningEntityName03);
    SCHEMA_FIELD(CUtlSymbolLarge, m_szDamagePositioningEntityName04);
    SCHEMA_FIELD(CUtlVector<Vector>, m_vInitialDamagePositions);
    SCHEMA_FIELD(CUtlVector<Vector>, m_vExtraDamagePositions);
    SCHEMA_FIELD(CUtlVector<Vector4D>, m_vInitialPanelVertices);
    SCHEMA_FIELD(CEntityIOOutput, m_OnBroken);
    SCHEMA_FIELD(uint8_t, m_iSurfaceType);
    SCHEMA_FIELD(CStrongHandle< InfoForResourceTypeIMaterial2 >, m_hMaterialDamageBase);
};
