namespace Source2Toolkit.SchemaGen;

public static class CustomMethods
{
    public static readonly Dictionary<string, List<string>> ManualMethods = new()
    {
        ["CBaseEntity"] = new()
        {
            "static CBaseEntity* CreateEntityByName(const char* pszClassName);",
            "template<typename T>\n    struct Factory\n    {\n        static T* New(const char* className)\n        {\n            return reinterpret_cast<T*>(CBaseEntity::CreateEntityByName(className));\n        }\n    };",
            "template<typename T>\n    static T* New(const char* className)\n    {    \n        return reinterpret_cast<T*>(CreateEntityByName(className));\n    }",
            "Vector GetAbsOrigin();",
            "QAngle GetAngRotation();",
            "QAngle GetAbsRotation();",
            "Vector GetAbsVelocity();",
            "void SetAbsOrigin(Vector vecOrigin);",
            "void SetAbsRotation(QAngle angAbsRotation);",
            "void SetAngRotation(QAngle angRotation);",
            "void SetAbsVelocity(Vector vecVelocity);",
            "void SetBaseVelocity(Vector vecVelocity);",
            "CEntitySubclassVDataBase* GetVData();",
            "void DispatchSpawn(CEntityKeyValues* pEntityKeyValues = nullptr);",
            "void Teleport(const Vector* pPosition, const QAngle* pAngles, const Vector* pVelocity);",
            "void SetMoveType(MoveType_t nMoveType);",
            "uint8 GetCollisionGroup();",
            "void SetCollisionGroup(uint8 nCollisionGroup);",
            "void CollisionRulesChanged();",
            "CHandle<CBaseEntity> GetHandle();",
            "const char* GetName() const;"
        },
        ["CBaseModelEntity"] = new()
        {
            "CUtlSymbolLarge GetModelName();",
            "Vector GetEyePosition();",
            "void SetModel(const char* pszModel);"
        },
        ["CBasePlayerController"] = new()
        {
            "void SetPawn(CBasePlayerPawn* pPawn);"
        },
        ["CBasePlayerPawn"] = new()
        {
            "void CommitSuicide(bool bExplode, bool bForce);",
            "void RemovePlayerItem(CBasePlayerWeapon* pWeapon);"
        },
        ["CBasePlayerWeapon"] = new()
        {
            "CCSWeaponBaseVData* GetWeaponVData();",
            "const char* GetWeaponClassname();"
        },
        ["CCSGameRules"] = new()
        {
            "void TerminateRound(float flDelay, int32_t eRoundEndReason);",
            "CBaseEntity* FindPickerEntity(CBasePlayerController* pPlayer);",
            "CCSPlayerController* GetClientAimTarget(CCSPlayerController* pPlayer);",
        },
        ["CCSPlayer_ItemServices"] = new()
        {
            "void DropActivePlayerWeapon(CBasePlayerWeapon* pActiveWeapon);",
            "void RemoveWeapons();",
            "CBasePlayerWeapon* GiveNamedItem(const char* pszItem);"
        },
    };
}