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

#include "CBaseEntity.h"
#include "../enums/ChatIgnoreType_t.h"
#include "../enums/PlayerConnectedState.h"

class CBasePlayerPawn;

class CBasePlayerController : public CBaseEntity, public CBaseEntity::Factory<CBasePlayerController>
{
public:
    DECLARE_SCHEMA_CLASS(CBasePlayerController);

    SCHEMA_FIELD(uint64_t, m_nInButtonsWhichAreToggles);
    SCHEMA_FIELD(uint32_t, m_nTickBase);
    SCHEMA_FIELD(CHandle<CBasePlayerPawn>, m_hPawn);
    SCHEMA_FIELD(bool, m_bKnownTeamMismatch);
    SCHEMA_FIELD(int32_t, m_nSplitScreenSlot);
    SCHEMA_FIELD(CHandle<CBasePlayerController>, m_hSplitOwner);
    SCHEMA_FIELD(CUtlVector<CHandle<CBasePlayerController>>, m_hSplitScreenPlayers);
    SCHEMA_FIELD(bool, m_bIsHLTV);
    SCHEMA_FIELD(PlayerConnectedState, m_iConnected);
    SCHEMA_FIELD_POINTER(char, m_iszPlayerName);
    SCHEMA_FIELD(CUtlString, m_szNetworkIDString);
    SCHEMA_FIELD(float, m_fLerpTime);
    SCHEMA_FIELD(bool, m_bLagCompensation);
    SCHEMA_FIELD(bool, m_bPredict);
    SCHEMA_FIELD(bool, m_bIsLowViolence);
    SCHEMA_FIELD(bool, m_bGamePaused);
    SCHEMA_FIELD(ChatIgnoreType_t, m_iIgnoreGlobalChat);
    SCHEMA_FIELD(float, m_flLastPlayerTalkTime);
    SCHEMA_FIELD(float, m_flLastEntitySteadyState);
    SCHEMA_FIELD(int32_t, m_nAvailableEntitySteadyState);
    SCHEMA_FIELD(bool, m_bHasAnySteadyStateEnts);
    SCHEMA_FIELD(uint64_t, m_steamID);
    SCHEMA_FIELD(bool, m_bNoClipEnabled);
    SCHEMA_FIELD(uint32_t, m_iDesiredFOV);

public:
    void SetPawn(CBasePlayerPawn* pPawn);
};
