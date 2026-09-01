/**
 * vim: set ts=4 sw=4 tw=99 noet :
 * ======================================================
 * Source2Toolkit Sample Plugin
 * ======================================================
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * This sample plugin is public domain.
 */

#include <cstdio>
#include "plugin.h"

#include "iserver.h"
#include "eiface.h"

SamplePlugin g_Plugin;
TOOLKIT_EXPOSE(cs2_sample, g_Plugin);

CConVar<int> sample_cvari("sample_cvari", FCVAR_NONE, "help string", 42);
CConVar<float> sample_cvarf("sample_cvarf", FCVAR_NONE, "help string", 69.69f, true, 10.0f, true, 100.0f);

// The stock SourceHook macros. TOOLKIT_SAVEVARS() has already pointed g_SHPtr
// at the toolkit's engine, so these need no setup of their own -- and the hooks
// they place land on the same instance every other plugin hooks on.
//
// Inline hooks patch a function at its address, so each needs a dispatcher
// declared up front: name, the class the function belongs to, its return type,
// then its parameters. The _void suffix is for functions returning nothing.
//
SH_DECL_INLINEHOOK2(TakeDamageOldHook, CBaseEntity, int64_t, CTakeDamageInfo*, CTakeDamageResult*);
// If you are unsure if function is member or just first arg, you can declare
// thistype as void and pass one more arg that is a1 and, also works for member functions.
SH_DECL_INLINEHOOK3_void(PostThinkHook, void, CCSPlayerPawn*, double, float);
//
SH_DECL_HOOK3_void(ISource2Server, GameFrame, SH_NOATTRIB, 0, bool, bool, bool);
SH_DECL_HOOK4_void(ISource2GameClients, ClientActive, SH_NOATTRIB, 0, CPlayerSlot, bool, const char*, uint64);
SH_DECL_HOOK5_void(ISource2GameClients, ClientDisconnect, SH_NOATTRIB, 0, CPlayerSlot, ENetworkDisconnectionReason, const char*, uint64, const char*);
SH_DECL_HOOK4_void(ISource2GameClients, ClientPutInServer, SH_NOATTRIB, 0, CPlayerSlot, char const*, int, uint64);
SH_DECL_HOOK1_void(ISource2GameClients, ClientSettingsChanged, SH_NOATTRIB, 0, CPlayerSlot);
SH_DECL_HOOK6_void(ISource2GameClients, OnClientConnected, SH_NOATTRIB, 0, CPlayerSlot, const char*, uint64, const char*, const char*, bool);
SH_DECL_HOOK6(ISource2GameClients, ClientConnect, SH_NOATTRIB, 0, bool, CPlayerSlot, const char*, uint64, const char*, bool, CBufferString*);
SH_DECL_HOOK2_void(ISource2GameClients, ClientCommand, SH_NOATTRIB, 0, CPlayerSlot, const CCommand &);

bool SamplePlugin::Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late)
{
    TOOLKIT_SAVEVARS();

    g_pSource2Server = api->GetSource2Server();
    g_pSource2GameClients = api->GetSource2GameClients();
    g_pEngineServer = api->GetEngineServer();
    g_pCVar = api->GetCVar();

    TOOLKIT_LOG(this, "Starting plugin.\n");

    SH_ADD_HOOK(ISource2Server, GameFrame, g_pSource2Server, SH_MEMBER(this, &SamplePlugin::Hook_GameFrame), true);
    SH_ADD_HOOK(ISource2GameClients, ClientActive, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientActive), true);
    SH_ADD_HOOK(ISource2GameClients, ClientDisconnect, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientDisconnect), true);
    SH_ADD_HOOK(ISource2GameClients, ClientPutInServer, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientPutInServer), true);
    SH_ADD_HOOK(ISource2GameClients, ClientSettingsChanged, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientSettingsChanged), false);
    SH_ADD_HOOK(ISource2GameClients, OnClientConnected, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_OnClientConnected), false);
    SH_ADD_HOOK(ISource2GameClients, ClientConnect, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientConnect), false);
    SH_ADD_HOOK(ISource2GameClients, ClientCommand, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientCommand), false);

    TOOLKIT_LOG(this, "All hooks started!\n");

    // A console command, and the same thing again as a chat command -- the
    // toolkit routes "!sample" and "/sample" to the same handler.
    REG_CON_COMMAND("sample_command", [](const CCommandContext &context, const CCommand &args, bool post)
    {
        TOOLKIT_LOG(&g_Plugin, "Sample command called by %d. Command: %s\n", context.GetPlayerSlot().Get(), args.GetCommandString());
    });

    // The engine only takes plain function pointers for this, and keeps one
    // list of them for the whole process. The toolkit installs a single one and
    // fans out, so a capturing lambda works here.
    HOOK_CONVAR_CHANGE([](ConVarRefAbstract *ref, CSplitScreenSlot slot, const char *pszNewValue, const char *pszOldValue)
    {
        if (V_strcmp(ref->GetName(), "sample_cvarf") != 0)
            return;

        TOOLKIT_LOG(&g_Plugin, "Sample convar \"%s\" was changed from %s to %s\n", ref->GetName(), pszOldValue, pszNewValue);
    });

    api->AddListener(this, this);
    ConVar_Register(FCVAR_RELEASE | FCVAR_CLIENT_CAN_EXECUTE | FCVAR_GAMEDLL);

    // Two inline hooks, each showing a different way to get the address.
    //
    // First: the toolkit already resolved this one, so just ask for it. Every
    // entry in IToolkitAddresses works this way and costs no scan of your own.
    if (void *pTakeDamageOld = reinterpret_cast<void *>(ADDR_TAKE_DAMAGE_OLD()))
    {
        m_iTakeDamageOldHookID = SH_ADD_INLINEHOOK(TakeDamageOldHook, pTakeDamageOld, SH_MEMBER(this, &SamplePlugin::Hook_TakeDamageOld), false);
    }
    else
    {
        TOOLKIT_LOG(this, "CBaseEntity::TakeDamageOld was not resolved; hook skipped\n");
    }

    // Second: anything in the shared gamedata, whether or not the toolkit has a
    // typed getter for it. ResolveSignature reads the entry's library, then
    // finds it by exported symbol or by pattern -- you do not care which.
    if (void *pPostThink = GAMECONFIG_RESOLVE("CCSPlayerPawn::PostThink"))
    {
        m_iPostThinkHookID = SH_ADD_INLINEHOOK(PostThinkHook, pPostThink, SH_MEMBER(this, &SamplePlugin::Hook_PostThink), false);
    }
    else
    {
        TOOLKIT_LOG(this, "CCSPlayerPawn::PostThink was not found in gamedata; hook skipped\n");
    }

    // You can get a convar reference to an already existing cvar via CConVarRef.
    // This will pre-register it if it's not yet registered and would use default
    // data until the actual cvar is registered. You can assert data existance via
    // IsConVarDataAvailable(). Make sure the type is correct here otherwise it
    // might prevent actual convar being registered, since you pre-registered it
    // with a different type or if convar already exists you'd be left with an
    // invalid ref, so a check for IsValidRef() is also nice to have.
    //
    // Side Note: Always make sure you are working with a valid ref (IsValidRef())
    // before reading/writing to it as otherwise you'd be reading/writing off of
    // default convar data which is shared across all the invalid convar refs.
    CConVarRef<int> ccvar_ref_example("mp_limitteams");

    if (ccvar_ref_example.IsValidRef() && ccvar_ref_example.IsConVarDataAvailable())
    {
        TOOLKIT_LOG(this, "CConVarRef \"%s\" got value pre = %d [float = %f, bool = %d, string = \"%s\"]\n",
                    ccvar_ref_example.GetName(), ccvar_ref_example.Get(), ccvar_ref_example.GetFloat(),
                    ccvar_ref_example.GetBool(), ccvar_ref_example.GetString().Get());

        // By default if you are using CConVar or CConVarRef you should be using
        // Get()/Set() methods to read/write values, as these are templated for the
        // particular type the cvar is of. It also is usually faster since it skips
        // all the type conversion logic of non templated methods
        ccvar_ref_example.Set(5);

        // As noted above there are methods that support value conversion between
        // certain types so stuff like this is possible on an int typed cvar for
        // example, refer to ConVarRefAbstract declaration for more info on these
        ccvar_ref_example.SetFloat(8.5f);

        TOOLKIT_LOG(this, "CConVarRef \"%s\" got value after = %d [float = %f, bool = %d, string = \"%s\"]\n",
                    ccvar_ref_example.GetName(), ccvar_ref_example.Get(), ccvar_ref_example.GetFloat(),
                    ccvar_ref_example.GetBool(), ccvar_ref_example.GetString().Get());
    }

    // You can also use ConVarRefAbstract class if you don't want typisation
    // support or don't know the actual type used, since you are responsible for
    // picking the correct type there! And ConVarRefAbstract won't pre-register the
    // convar in the system, as it acts as a plain ref, so make sure to check the
    // ref for validity before usage via IsValidRef()
    ConVarRefAbstract cvar_ref_example("mp_limitteams");

    if (cvar_ref_example.IsValidRef())
    {
        TOOLKIT_LOG(this, "ConVarRefAbstract \"%s\" got value pre [float = %f, bool = %d, string = \"%s\"]\n",
                    cvar_ref_example.GetName(), cvar_ref_example.GetFloat(), cvar_ref_example.GetBool(),
                    cvar_ref_example.GetString().Get());

        // Since the ref is not typed, you can't use direct Get() and Set() methods,
        // instead you need to use methods with type conversion support.
        cvar_ref_example.SetFloat(10.0f);

        // If you work with convars of non primitive types, you can also use SetAs()
        // methods to try to set the value as a specific type, if type mismatches it
        // would try to do conversion if possible and if not it would do nothing.
        // There's also an equvialent methods for reading the value, GetAs()
        cvar_ref_example.SetAs<Vector>(Vector(1.0f, 2.0f, 3.0f));

        // Alternatively you can "promote" plain ref to a typed variant by passing
        // plain ref to a constructor but be careful, as there's a type checker in
        // place that would invalidate convar ref if cast to a wrong type was
        // attempted, you can check for that either via IsValidRef() or
        // IsConVarDataValid() afterwards, but generally you should just know the
        // correct type of the cvar you are casting to beforehand.
        CConVarRef<int> promoted_ref(cvar_ref_example);
        if (promoted_ref.IsValidRef() && promoted_ref.IsConVarDataValid())
        {
            promoted_ref.Set(5);
        }

        TOOLKIT_LOG(this, "ConVarRefAbstract \"%s\" got value after [float = %f, bool = %d, string = \"%s\"]\n",
                    cvar_ref_example.GetName(), cvar_ref_example.GetFloat(), cvar_ref_example.GetBool(),
                    cvar_ref_example.GetString().Get());
    }

    return true;
}

bool SamplePlugin::Unload(char* error, size_t maxlen)
{
    SH_REMOVE_HOOK(ISource2Server, GameFrame, g_pSource2Server, SH_MEMBER(this, &SamplePlugin::Hook_GameFrame), true);
    SH_REMOVE_HOOK(ISource2GameClients, ClientActive, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientActive), true);
    SH_REMOVE_HOOK(ISource2GameClients, ClientDisconnect, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientDisconnect), true);
    SH_REMOVE_HOOK(ISource2GameClients, ClientPutInServer, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientPutInServer), true);
    SH_REMOVE_HOOK(ISource2GameClients, ClientSettingsChanged, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientSettingsChanged), false);
    SH_REMOVE_HOOK(ISource2GameClients, OnClientConnected, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_OnClientConnected), false);
    SH_REMOVE_HOOK(ISource2GameClients, ClientConnect, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientConnect), false);
    SH_REMOVE_HOOK(ISource2GameClients, ClientCommand, g_pSource2GameClients, SH_MEMBER(this, &SamplePlugin::Hook_ClientCommand), false);

    SH_REMOVE_HOOK_ID(m_iTakeDamageOldHookID);
    SH_REMOVE_HOOK_ID(m_iPostThinkHookID);

    // The CConVars above are objects in this library, and ConVar_Register handed
    // the engine pointers to them. Without this the engine keeps those pointers
    // after the library is unloaded, and the next thing to touch one -- the
    // console autocompleting, a config exec -- reads freed memory.
    //
    // ConVar_Unregister only walks the list held by the caller's own library, so
    // the toolkit cannot do this on a plugin's behalf. Every plugin that
    // declares a CConVar has to make this call.
    // Inline hooks patch the game's own code, so leaving one installed past
    // unload jumps into a library that is no longer mapped.
    ConVar_Unregister();

    return true;
}

void SamplePlugin::OnAllToolkitPluginsLoaded()
{
    /* This is where we'd do stuff that relies on the mod or other plugins
     * being initialized (for example, cvars added and events registered).
     */
}

void SamplePlugin::Hook_ClientActive(CPlayerSlot slot, bool bLoadGame, const char* pszName, uint64 xuid)
{
    TOOLKIT_LOG(this, "Hook_ClientActive(%d, %d, \"%s\", %lld)\n", slot.Get(), bLoadGame, pszName, xuid);
}

void SamplePlugin::Hook_ClientCommand(CPlayerSlot slot, const CCommand& args)
{
    TOOLKIT_LOG(this, "Hook_ClientCommand(%d, \"%s\")\n", slot.Get(), args.GetCommandString());

    // MRES_SUPERCEDE blocks the original entirely -- the engine never sees this
    // command. Use it to take a command over, not to "handle it as well".
    if (!V_strcmp(args.Arg(0), "sample_blocked"))
    {
        TOOLKIT_LOG(this, "Swallowing \"sample_blocked\" -- the engine will never see it.\n");
        RETURN_META(MRES_SUPERCEDE);
    }

    // MRES_IGNORED says "I did nothing" and is the right answer for a hook that
    // only looks. MRES_HANDLED would mean "I acted, but let the original run".
    RETURN_META(MRES_IGNORED);
}

void SamplePlugin::Hook_ClientSettingsChanged(CPlayerSlot slot)
{
    TOOLKIT_LOG(this, "Hook_ClientSettingsChanged(%d)\n", slot.Get());

    // MRES_HANDLED: we acted on this, but the original still has to run. It
    // differs from MRES_IGNORED only in what later hooks in the chain are told.
    RETURN_META(MRES_HANDLED);
}

void SamplePlugin::Hook_OnClientConnected(CPlayerSlot slot, const char* pszName, uint64 xuid, const char* pszNetworkID, const char* pszAddress, bool bFakePlayer)
{
    TOOLKIT_LOG(this, "Hook_OnClientConnected(%d, \"%s\", %lld, \"%s\", \"%s\", %d)\n", slot.Get(), pszName, xuid, pszNetworkID, pszAddress, bFakePlayer);
}

bool SamplePlugin::Hook_ClientConnect(CPlayerSlot slot, const char* pszName, uint64 xuid, const char* pszNetworkID, bool unk1, CBufferString* pRejectReason)
{
    TOOLKIT_LOG(this, "Hook_ClientConnect(%d, \"%s\", %lld, \"%s\", %d, \"%s\")\n", slot.Get(), pszName, xuid, pszNetworkID, unk1, pRejectReason->Get());

    // A hook on a function that returns something uses RETURN_META_VALUE. With
    // MRES_OVERRIDE the original runs but the value below is what the
    // caller gets -- here: refuse the connection and hand back the reason. Try
    // it by connecting with "sample_rejected" as your name.
    if (!V_strcmp(pszName, "sample_rejected"))
    {
        pRejectReason->Insert(0, "Rejected by the sample plugin.");
        RETURN_META_VALUE(MRES_OVERRIDE, false);
    }

    // MRES_IGNORED with a value still returns whatever the original returns --
    // the value passed here is discarded. Only SUPERCEDE/OVERRIDE make it count.
    RETURN_META_VALUE(MRES_IGNORED, true);
}

void SamplePlugin::Hook_ClientPutInServer(CPlayerSlot slot, char const* pszName, int type, uint64 xuid)
{
    TOOLKIT_LOG(this, "Hook_ClientPutInServer(%d, \"%s\", %d, %lld)\n", slot.Get(), pszName, type, xuid);
}

void SamplePlugin::Hook_ClientDisconnect(CPlayerSlot slot, ENetworkDisconnectionReason reason, const char* pszName, uint64 xuid, const char* pszNetworkID)
{
    TOOLKIT_LOG(this, "Hook_ClientDisconnect(%d, %d, \"%s\", %lld, \"%s\")\n", slot.Get(), reason, pszName, xuid, pszNetworkID);
}

void SamplePlugin::Hook_GameFrame(bool simulating, bool bFirstTick, bool bLastTick)
{
    // Runs every tick. Whatever goes in here runs 64 times a second, per frame,
    // before the game's own GameFrame -- keep it cheap.
    /**
     * simulating:
     * ***********
     * true  | game is ticking
     * false | game is not ticking
     */
}

int64_t SamplePlugin::Hook_TakeDamageOld(CTakeDamageInfo *pInfo, CTakeDamageResult *pResult)
{
    CBaseEntity* pThis = META_IFACEPTR(CBaseEntity);

    // MRES_IGNORED lets the original run untouched. Change pInfo here and the
    // original sees your version; RETURN_META_VALUE(MRES_SUPERCEDE, 0) would
    // block the damage outright.
    TOOLKIT_LOG(this, "TakeDamageOld: %p entity, %.1f damage\n", pThis, pInfo ? pInfo->m_flDamage : 0.0f);

    RETURN_META_VALUE(MRES_IGNORED, 0);
}

void SamplePlugin::Hook_PostThink(CCSPlayerPawn* pThis, double flFrameTime, float flUnknown)
{
    // Runs for every pawn every tick, so do as little as possible here. Left
    // empty on purpose -- logging would flood the console.
    RETURN_META(MRES_IGNORED);
}

void SamplePlugin::OnLevelInit(const char* pMapName, const char* pMapEntities, const char* pOldLevel, const char* pLandmarkName, bool loadGame, bool background)
{
    TOOLKIT_LOG(this, "OnLevelInit(%s)\n", pMapName);
}

void SamplePlugin::OnLevelShutdown()
{
    TOOLKIT_LOG(this, "OnLevelShutdown()\n");
}
