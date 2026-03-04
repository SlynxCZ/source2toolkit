namespace Source2Toolkit.SchemaGen;

public static class CustomMethods
{
    public static readonly Dictionary<string, List<string>> ManualMethods = new()
    {
        ["CBaseEntity"] = new()
        {
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
            "void Teleport(const Vector* position, const QAngle* angles, const Vector* velocity);",
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
        }
    };
}
