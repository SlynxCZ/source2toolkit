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

// The hooks are KHook objects -- metamod's detour library, on the one engine
// the toolkit shares with metamod (TOOLKIT_SAVEVARS() fetched it), so they
// land next to every other plugin's hooks and can call through their originals.
// Each holds the member function it hooks, the context and the Pre/Post
// callbacks (Pre runs before the original, Post after), and comes down in its
// destructor, so it lives behind a plain pointer: new here, delete in Unload().
//
// A Virtual hook is placed on an instance (Add) or on a whole vtable
// (AddGlobal); a Member hook patches a function at its address (Configure),
// for anything a signature scan found. KHOOK_NEW takes the hook's type from the
// member it is stored in, since MSVC cannot deduce it from the arguments.
SamplePlugin::SamplePlugin() :
    KHOOK_NEW(m_hGameFrame, &ISource2Server::GameFrame, this, nullptr, &SamplePlugin::Hook_GameFrame),
    KHOOK_NEW(m_hClientActive, &ISource2GameClients::ClientActive, this, nullptr, &SamplePlugin::Hook_ClientActive),
    KHOOK_NEW(m_hClientDisconnect, &ISource2GameClients::ClientDisconnect, this, nullptr, &SamplePlugin::Hook_ClientDisconnect),
    KHOOK_NEW(m_hClientPutInServer, &ISource2GameClients::ClientPutInServer, this, nullptr, &SamplePlugin::Hook_ClientPutInServer),
    KHOOK_NEW(m_hClientSettingsChanged, &ISource2GameClients::ClientSettingsChanged, this, &SamplePlugin::Hook_ClientSettingsChanged, nullptr),
    KHOOK_NEW(m_hOnClientConnected, &ISource2GameClients::OnClientConnected, this, &SamplePlugin::Hook_OnClientConnected, nullptr),
    KHOOK_NEW(m_hClientConnect, &ISource2GameClients::ClientConnect, this, &SamplePlugin::Hook_ClientConnect, nullptr),
    KHOOK_NEW(m_hClientCommand, &ISource2GameClients::ClientCommand, this, &SamplePlugin::Hook_ClientCommand, nullptr),
    KHOOK_NEW(m_hTakeDamageOld, this, &SamplePlugin::Hook_TakeDamageOld, nullptr),
    KHOOK_NEW(m_hPostThink, this, &SamplePlugin::Hook_PostThink, nullptr)
{
}

bool SamplePlugin::Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late)
{
    TOOLKIT_SAVEVARS();

    g_pSource2Server = api->GetSource2Server();
    g_pSource2GameClients = api->GetSource2GameClients();
    g_pEngineServer = api->GetEngineServer();
    g_pCVar = api->GetCVar();

    TOOLKIT_LOG(this, "Starting plugin.\n");

    // Virtual hooks go onto the engine's own interface instances.
    m_hGameFrame->Add(g_pSource2Server);
    m_hClientActive->Add(g_pSource2GameClients);
    m_hClientDisconnect->Add(g_pSource2GameClients);
    m_hClientPutInServer->Add(g_pSource2GameClients);
    m_hClientSettingsChanged->Add(g_pSource2GameClients);
    m_hOnClientConnected->Add(g_pSource2GameClients);
    m_hClientConnect->Add(g_pSource2GameClients);
    m_hClientCommand->Add(g_pSource2GameClients);

    TOOLKIT_LOG(this, "All hooks started!\n");

    // A console command, and the same thing again as a chat command -- the
    // toolkit routes "!sample" and "/sample" to the same handler.
    REGISTER_CON_COMMAND("sample_command", [](const CCommandContext &context, const CCommand &args, bool post)
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

    // Two function hooks, each showing a different way to get the address.
    //
    // First: the toolkit already resolved this one, so just ask for it. Every
    // entry in IToolkitAddresses works this way and costs no scan of your own.
    if (void *pTakeDamageOld = reinterpret_cast<void *>(ADDR_TAKE_DAMAGE_OLD()))
    {
        m_hTakeDamageOld->Configure(pTakeDamageOld);
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
        m_hPostThink->Configure(pPostThink);
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
    m_hGameFrame->Remove(g_pSource2Server);
    m_hClientActive->Remove(g_pSource2GameClients);
    m_hClientDisconnect->Remove(g_pSource2GameClients);
    m_hClientPutInServer->Remove(g_pSource2GameClients);
    m_hClientSettingsChanged->Remove(g_pSource2GameClients);
    m_hOnClientConnected->Remove(g_pSource2GameClients);
    m_hClientConnect->Remove(g_pSource2GameClients);
    m_hClientCommand->Remove(g_pSource2GameClients);

    // Deleting a hook is what takes its detour down -- after this nothing in
    // the engine points into this library any more.
    delete m_hGameFrame;
    delete m_hClientActive;
    delete m_hClientDisconnect;
    delete m_hClientPutInServer;
    delete m_hClientSettingsChanged;
    delete m_hOnClientConnected;
    delete m_hClientConnect;
    delete m_hClientCommand;
    delete m_hTakeDamageOld;
    delete m_hPostThink;
    m_hGameFrame = nullptr;
    m_hClientActive = nullptr;
    m_hClientDisconnect = nullptr;
    m_hClientPutInServer = nullptr;
    m_hClientSettingsChanged = nullptr;
    m_hOnClientConnected = nullptr;
    m_hClientConnect = nullptr;
    m_hClientCommand = nullptr;
    m_hTakeDamageOld = nullptr;
    m_hPostThink = nullptr;

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

KHook::Return<void> SamplePlugin::Hook_ClientActive(ISource2GameClients* pThis, CPlayerSlot slot, bool bLoadGame, const char* pszName, uint64 xuid)
{
    TOOLKIT_LOG(this, "Hook_ClientActive(%d, %d, \"%s\", %lld)\n", slot.Get(), bLoadGame, pszName, xuid);

    return { KHook::Action::Ignore };
}

KHook::Return<void> SamplePlugin::Hook_ClientCommand(ISource2GameClients* pThis, CPlayerSlot slot, const CCommand& args)
{
    TOOLKIT_LOG(this, "Hook_ClientCommand(%d, \"%s\")\n", slot.Get(), args.GetCommandString());

    // Supersede blocks the original entirely -- the engine never sees this
    // command. Use it to take a command over, not to "handle it as well".
    if (!V_strcmp(args.Arg(0), "sample_blocked"))
    {
        TOOLKIT_LOG(this, "Swallowing \"sample_blocked\" -- the engine will never see it.\n");
        return { KHook::Action::Supersede };
    }

    // Ignore says "I did nothing": the original runs, and so does whatever else
    // is hooked here. The right answer for a hook that only looks.
    return { KHook::Action::Ignore };
}

KHook::Return<void> SamplePlugin::Hook_ClientSettingsChanged(ISource2GameClients* pThis, CPlayerSlot slot)
{
    TOOLKIT_LOG(this, "Hook_ClientSettingsChanged(%d)\n", slot.Get());

    // Acting on the call and still letting the original run is also Ignore --
    // KHook has no separate "handled" state.
    return { KHook::Action::Ignore };
}

KHook::Return<void> SamplePlugin::Hook_OnClientConnected(ISource2GameClients* pThis, CPlayerSlot slot, const char* pszName, uint64 xuid, const char* pszNetworkID, const char* pszAddress, bool bFakePlayer)
{
    TOOLKIT_LOG(this, "Hook_OnClientConnected(%d, \"%s\", %lld, \"%s\", \"%s\", %d)\n", slot.Get(), pszName, xuid, pszNetworkID, pszAddress, bFakePlayer);

    return { KHook::Action::Ignore };
}

KHook::Return<bool> SamplePlugin::Hook_ClientConnect(ISource2GameClients* pThis, CPlayerSlot slot, const char* pszName, uint64 xuid, const char* pszNetworkID, bool unk1, CBufferString* pRejectReason)
{
    TOOLKIT_LOG(this, "Hook_ClientConnect(%d, \"%s\", %lld, \"%s\", %d, \"%s\")\n", slot.Get(), pszName, xuid, pszNetworkID, unk1, pRejectReason->Get());

    // A hook on a function that returns something returns the value alongside
    // the action. With Override the original still runs but the value below is
    // what the caller gets -- here: refuse the connection and hand back the
    // reason. Try it by connecting with "sample_rejected" as your name.
    if (!V_strcmp(pszName, "sample_rejected"))
    {
        pRejectReason->Insert(0, "Rejected by the sample plugin.");
        return { KHook::Action::Override, false };
    }

    // Ignore with a value still returns whatever the original returns -- the
    // value passed here is discarded. Only Supersede/Override make it count.
    return { KHook::Action::Ignore, true };
}

KHook::Return<void> SamplePlugin::Hook_ClientPutInServer(ISource2GameClients* pThis, CPlayerSlot slot, char const* pszName, int type, uint64 xuid)
{
    TOOLKIT_LOG(this, "Hook_ClientPutInServer(%d, \"%s\", %d, %lld)\n", slot.Get(), pszName, type, xuid);

    return { KHook::Action::Ignore };
}

KHook::Return<void> SamplePlugin::Hook_ClientDisconnect(ISource2GameClients* pThis, CPlayerSlot slot, ENetworkDisconnectionReason reason, const char* pszName, uint64 xuid, const char* pszNetworkID)
{
    TOOLKIT_LOG(this, "Hook_ClientDisconnect(%d, %d, \"%s\", %lld, \"%s\")\n", slot.Get(), reason, pszName, xuid, pszNetworkID);

    return { KHook::Action::Ignore };
}

KHook::Return<void> SamplePlugin::Hook_GameFrame(ISource2Server* pThis, bool simulating, bool bFirstTick, bool bLastTick)
{
    // Runs every tick. Whatever goes in here runs 64 times a second, per frame,
    // right after the game's own GameFrame (a Post hook) -- keep it cheap.
    /**
     * simulating:
     * ***********
     * true  | game is ticking
     * false | game is not ticking
     */

    return { KHook::Action::Ignore };
}

KHook::Return<int64_t> SamplePlugin::Hook_TakeDamageOld(CBaseEntity* pThis, CTakeDamageInfo *pInfo, CTakeDamageResult *pResult)
{
    // The hooked object arrives as the first parameter. Ignore lets the original
    // run untouched; change pInfo here and the original sees your version,
    // while { KHook::Action::Supersede, 0 } would block the damage outright.
    TOOLKIT_LOG(this, "TakeDamageOld: %p entity, %.1f damage\n", pThis, pInfo ? pInfo->m_flDamage : 0.0f);

    return { KHook::Action::Ignore, 0 };
}

KHook::Return<void> SamplePlugin::Hook_PostThink(CCSPlayerPawn* pThis, double flFrameTime, float flUnknown)
{
    // Runs for every pawn every tick, so do as little as possible here. Left
    // empty on purpose -- logging would flood the console.
    return { KHook::Action::Ignore };
}

void SamplePlugin::OnLevelInit(const char* pMapName, const char* pMapEntities, const char* pOldLevel, const char* pLandmarkName, bool loadGame, bool background)
{
    TOOLKIT_LOG(this, "OnLevelInit(%s)\n", pMapName);
}

void SamplePlugin::OnLevelShutdown()
{
    TOOLKIT_LOG(this, "OnLevelShutdown()\n");
}
