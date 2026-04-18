#include "main.h"

#include "source2toolkit/IToolkitApi.h"
#include "source2toolkit/IToolkitCommands.h"
#include "source2toolkit/IToolkitEvents.h"
#include "source2toolkit/IToolkitTypes.h"

#include "source2toolkit/utils/addresses.h"
#include "source2toolkit/utils/commands.h"
#include "source2toolkit/utils/convars.h"
#include "source2toolkit/utils/events.h"
#include "source2toolkit/utils/gameconfig.h"

#include "sdk/CLCMsg_ListenEvents.h"
#include "sdk/CSource1LegacyGameEventGameSystem.h"

#include "source2toolkit/schema/schema.h"
#include "source2toolkit/schema/serversideclient.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"

#include "khook.hpp"
#include "eiface.h"
#include "igameeventsystem.h"
#include "schemasystem.h"
#include "interfaces/interfaces.h"
#include "networksystem/inetworkmessages.h"
#include "source2toolkit/utils/scheduler.h"

TOOLKIT_EXPOSE(source2toolkit_test, g_Plugin);

Plugin g_Plugin;
IGameEventSystem* g_pGameEventSystem = nullptr;

static std::unordered_map<int, std::string> g_EventIdToName;
static std::unordered_set<int> g_kBlacklistIds;
static const std::unordered_set<std::string> g_kBlacklist = {
    "gameui_hidden", "player_chat", "player_score", "player_shoot",
    "game_init", "game_start", "game_end", "warmup_end",
    "ugc_map_info_received", "ugc_map_unsubscribed",
    "ugc_map_download_error", "ugc_file_download_finished",
    "ugc_file_download_start", "dm_bonus_weapon_start",
    "survival_announce_phase", "break_prop", "player_decal",
    "instructor_server_hint_create",
    "instructor_server_hint_stop", "reset_game_titledata",
    "vote_ended", "vote_started", "vote_options",
    "endmatch_mapvote_selecting_map",
    "endmatch_cmm_start_reveal_items",
    "inventory_updated", "client_loadout_changed",
    "add_player_sonar_icon", "door_open", "door_closed",
    "door_break", "other_death", "bullet_damage",
    "item_purchase", "bomb_beginplant", "bomb_abortplant",
    "bullet_impact", "bomb_begindefuse", "bomb_abortdefuse",
    "hostage_stops_following", "hostage_rescued_all",
    "hostage_call_for_help", "vip_escaped", "vip_killed",
    "player_radio", "bomb_beep", "weapon_fire_on_empty",
    "weapon_zoom", "silencer_detach", "inspect_weapon",
    "weapon_zoom_rifle", "player_spawned",
    "item_pickup_slerp", "item_pickup_failed", "item_remove",
    "item_equip", "enter_buyzone", "exit_buyzone",
    "buytime_ended", "enter_bombzone", "exit_bombzone",
    "enter_rescue_zone", "exit_rescue_zone",
    "silencer_off", "silencer_on", "buymenu_open",
    "buymenu_close", "round_prestart", "round_poststart",
    "grenade_bounce", "molotov_detonate",
    "tagrenade_detonate", "inferno_extinguish",
    "decoy_firing", "player_footstep",
    "player_jump", "player_blind", "player_falldamage",
    "door_moving", "mb_input_lock_success",
    "mb_input_lock_cancel", "nav_blocked", "nav_generate",
    "achievement_info_loaded", "hltv_changed_mode",
    "show_deathpanel", "hide_deathpanel",
    "player_avenged_teammate", "achievement_earned_local",
    "repost_xbox_achievements", "match_end_conditions",
    "write_profile_data", "trial_time_expired",
    "update_matchmaking_stats", "enable_restart_voting",
    "sfuievent", "start_vote", "teamchange_pending",
    "material_default_complete", "cs_prev_next_spectator",
    "tournament_reward", "start_halftime", "ammo_refill",
    "parachute_pickup", "parachute_deploy",
    "dronegun_attack", "drone_dispatched",
    "loot_crate_visible", "loot_crate_opened",
    "open_crate_instr", "smoke_beacon_paradrop",
    "drone_cargo_detached", "drone_above_roof",
    "dz_item_interaction", "survival_teammate_respawn",
    "guardian_wave_restart", "bullet_flight_resolution",
    "server_shutdown", "server_message",
    "player_full_update", "local_player_team",
    "local_player_controller_team", "local_player_pawn_changed",
    "ragdoll_dissolved", "team_info", "team_score",
    "hltv_rank_camera", "hltv_rank_entity", "demo_stop",
    "map_shutdown", "map_transition", "hostname_changed",
    "game_message", "round_start_pre_entity",
    "round_start_post_nav", "teamplay_round_start",
    "player_hintmessage", "break_breakable",
    "broken_breakable", "door_close", "vote_failed",
    "vote_passed", "vote_cast_yes", "vote_cast_no",
    "achievement_event", "achievement_write_failed",
    "bonus_updated", "gameinstructor_draw",
    "gameinstructor_nodraw", "flare_ignite_npc",
    "helicopter_grenade_punt_miss", "physgun_pickup",
    "cart_updated", "store_pricesheet_updated",
    "item_schema_initialized", "drop_rate_modified",
    "event_ticket_modified", "gc_connected",
    "instructor_start_lesson", "instructor_close_lesson",
    "set_instructor_group_enabled",
    "clientside_lesson_closed", "dynamic_shadow_light_changed"
};

Plugin::Plugin() :
    m_hListenBitsReceived(this, &Plugin::Hook_ListenBitsReceived, nullptr),
    m_hLoadEventsFromFile(&IGameEventManager2::LoadEventsFromFile, this, nullptr, &Plugin::Hook_LoadEventsFromFile)
{
}

bool Plugin::Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late)
{
    TOOLKIT_SAVEVARS();

    GET_IFACE_CURRENT(GetEngineFactory, g_pEngineServer, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
    GET_IFACE_CURRENT(GetEngineFactory, g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
    GET_IFACE_CURRENT(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService,
                      GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
    GET_IFACE_ANY(GetServerFactory, g_pSource2Server, ISource2Server, INTERFACEVERSION_SERVERGAMEDLL);
    GET_IFACE_ANY(GetServerFactory, g_pSource2GameClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
    GET_IFACE_ANY(GetEngineFactory, g_pNetworkServerService, INetworkServerService,
                  NETWORKSERVERSERVICE_INTERFACE_VERSION);
    GET_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, CSchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_IFACE_ANY(GetEngineFactory, g_pGameEventSystem, IGameEventSystem, GAMEEVENTSYSTEM_INTERFACE_VERSION);
    GET_IFACE_ANY(GetEngineFactory, g_pNetworkMessages, INetworkMessages, NETWORKMESSAGES_INTERFACE_VERSION);
    GET_IFACE_ANY(GetServerFactory, g_pSource2GameEntities, ISource2GameEntities,
                  SOURCE2GAMEENTITIES_INTERFACE_VERSION);

    api->AddListener(this, this);

    {
        m_pListenBitsReceived = UTIL_FindPattern(g_pSource2Server, UTIL_GetSignature("CSource1LegacyGameEventGameSystem_ListenBitsReceived"));
        if (m_pListenBitsReceived)
        {
            m_hListenBitsReceived.Configure(reinterpret_cast<bool(*)(CSource1LegacyGameEventGameSystem*, CLCMsg_ListenEvents*)>(m_pListenBitsReceived));
        }
    }

    {
        m_pCGameEventManagerVTable = (IGameEventManager2*)UTIL_GetVirtualTableByName(g_pSource2Server, "CGameEventManager");
        if (m_pCGameEventManagerVTable)
        {
            m_hLoadEventsFromFile.AddGlobal((IGameEventManager2*)&m_pCGameEventManagerVTable);
        }
    }

    TOOLKIT_LOG(this, "Load() done\n");

    return true;
}

bool Plugin::Unload(char* error, size_t maxlen)
{
    {
        m_hListenBitsReceived.~Function();
    }

    {
        m_hLoadEventsFromFile.RemoveGlobal((IGameEventManager2*)&m_pCGameEventManagerVTable);
    }

    TOOLKIT_LOG(this, "Unload() done\n");

    return true;
}

KHook::Return<bool> Plugin::Hook_ListenBitsReceived(CSource1LegacyGameEventGameSystem* pThis, CLCMsg_ListenEvents* pMsg)
{
    TOOLKIT_LOG(this, "[ListenBits] called (%p %p)\n", pThis, pMsg);

    auto mgr = GetGameEventManager();
    if (!mgr)
    {
        TOOLKIT_LOG(this, "[ListenBits] GameEventManager is null\n");
        return { KHook::Action::Ignore };
    }

    CPlayerSlot slot = pMsg->GetPlayerSlot();
    int iSlot = slot.Get();

    TOOLKIT_LOG(this, "[ListenBits] slot: %d\n", iSlot);

    auto player = CCSPlayerController::FromSlot(slot);
    if (!player || player->IsBot())
    {
        TOOLKIT_LOG(this, "[ListenBits] invalid player or bot\n");
        return { KHook::Action::Ignore };
    }

    const char* playerName = player->GetPlayerName();

    int count = pMsg->GetEventMaskSize();
    uint32_t* data = pMsg->GetEventMaskData();

    TOOLKIT_LOG(this, "Player: %s // mask size: %d\n", playerName, count);

    bool bDetected = false;
    std::vector<int> activeEvents;

    for (int i = 0; i < count; i++)
    {
        uint32_t bits = data[i];
        if (!bits)
            continue;

        for (int b = 0; b < 32; b++)
        {
            if (bits & (1 << b))
            {
                int eventId = i * 32 + b;
                activeEvents.push_back(eventId);

                const char* name = "unknown";
                auto it = g_EventIdToName.find(eventId);
                if (it != g_EventIdToName.end())
                    name = it->second.c_str();

                TOOLKIT_LOG(this, "[ListenBits] Player %s listens to: %s (%d)\n", playerName, name, eventId);

                if (g_kBlacklistIds.contains(eventId))
                {
                    const char* name = "unknown";

                    auto it = g_EventIdToName.find(eventId);
                    if (it != g_EventIdToName.end()) name = it->second.c_str();

                    TOOLKIT_LOG(this, "BLACKLIST HIT: %s (%d)\n", name, eventId);

                    bDetected = true;
                }
            }
        }
    }

    if (bDetected)
    {
        TOOLKIT_LOG(this, "Player: %s // DETECTED blacklisted events\n", playerName);

        return { KHook::Action::Ignore, false };
    }

    TOOLKIT_LOG(this, "[ListenBits] allowed\n");
    return { KHook::Action::Ignore, false };
}

KHook::Return<int> Plugin::Hook_LoadEventsFromFile(IGameEventManager2* pThis, const char* filename, bool bSearchAlls)
{
    TOOLKIT_LOG(this, "[GameEvents] Loaded: %s\n", filename);

    UTIL_AddTimer(0.1f, [this, pThis, filename = std::string(filename)]()
    {
        const char* pchKvName = nullptr;

        if (filename == "resource/core.gameevents")
            pchKvName = "core game events";
        else if (filename == "resource/game.gameevents")
            pchKvName = "gameevents";
        else if (filename == "resource/mod.gameevents")
            pchKvName = "cstrikeevents";

        KeyValues::AutoDelete kv(pchKvName ? pchKvName : "");

        if (!kv->LoadFromFile(g_pFullFileSystem, filename.c_str(), "GAME"))
        {
            TOOLKIT_LOG(this, "FAILED to load KV (deferred): %s\n", filename.c_str());
            return;
        }

        for (KeyValues* event = kv->GetFirstSubKey(); event; event = event->GetNextKey())
        {
            const char* name = event->GetName();
            if (!name || !*name)
                continue;

            int id = pThis->LookupEventId(name);

            if (id != -1)
            {
                g_EventIdToName[id] = name;
                TOOLKIT_LOG(this, "[KV MAP] %s -> %d\n", name, id);
            }
        }
    });

    return { KHook::Action::Ignore, 0 };
}

const char* Plugin::GetVersion()
{
    return "1.0.0";
}

const char* Plugin::GetAuthor()
{
    return "Slynx";
}

const char* Plugin::GetDescription()
{
    return "Source2Toolkit test plugin";
}

const char* Plugin::GetName()
{
    return "Source2Toolkit test";
}
