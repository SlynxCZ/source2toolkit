//
// Created by Michal Přikryl on 03.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once
#include "source2toolkit/IToolkitConVars.h"

namespace convars {
    class ConVarsManager final : public IToolkitConVars
    {
    public:
        uint16 GetConvarAccessIndexByName(const char* name) override;
        ConVarRefAbstract GetConvarRef(uint16 accessIndex) override;

        const char* GetName(uint16 accessIndex) override;
        const char* GetHelpText(uint16 accessIndex) override;

        EConVarType GetType(uint16 accessIndex) override;

        uint64 GetFlags(uint16 accessIndex) override;
        void SetFlags(uint16 accessIndex, uint64 flags) override;

        void* GetValueAddress(uint16 accessIndex, CSplitScreenSlot slot) override;

        const char* GetString(uint16 accessIndex, CSplitScreenSlot slot) override;
        void SetString(uint16 accessIndex, const char* value, CSplitScreenSlot slot) override;

        bool GetBool(uint16 accessIndex, CSplitScreenSlot slot) override;
        int32 GetInt(uint16 accessIndex, CSplitScreenSlot slot) override;
        float GetFloat(uint16 accessIndex, CSplitScreenSlot slot) override;
        double GetDouble(uint16 accessIndex, CSplitScreenSlot slot) override;

        void SetBool(uint16 accessIndex, bool value, CSplitScreenSlot slot) override;
        void SetInt(uint16 accessIndex, int32 value, CSplitScreenSlot slot) override;
        void SetFloat(uint16 accessIndex, float value, CSplitScreenSlot slot) override;
        void SetDouble(uint16 accessIndex, double value, CSplitScreenSlot slot) override;

        Vector2D GetVector2(uint16 accessIndex, CSplitScreenSlot slot) override;
        Vector GetVector3(uint16 accessIndex, CSplitScreenSlot slot) override;
        Vector4D GetVector4(uint16 accessIndex, CSplitScreenSlot slot) override;
        QAngle GetQAngle(uint16 accessIndex, CSplitScreenSlot slot) override;
        Color GetColor(uint16 accessIndex, CSplitScreenSlot slot) override;

        void SetVector2(uint16 accessIndex, const Vector2D& value, CSplitScreenSlot slot) override;
        void SetVector3(uint16 accessIndex, const Vector& value, CSplitScreenSlot slot) override;
        void SetVector4(uint16 accessIndex, const Vector4D& value, CSplitScreenSlot slot) override;
        void SetQAngle(uint16 accessIndex, const QAngle& value, CSplitScreenSlot slot) override;
        void SetColor(uint16 accessIndex, const Color& value, CSplitScreenSlot slot) override;

        void GetValue(uint16 accessIndex, void* outValue, CSplitScreenSlot slot) override;
        void SetValue(uint16 accessIndex, const void* value, CSplitScreenSlot slot) override;

        uint16 CreateConVar(const char* name, EConVarType type, const char* help, uint64 flags,
                            bool hasMin, bool hasMax,
                            void* defaultValue, const void* minValue, const void* maxValue) override;

        void DeleteConVar(uint16 accessIndex) override;

    private:
        inline ConVarRefAbstract GetRef(uint16 idx)
        {
            return ConVarRefAbstract(idx);
        }
    };

    extern ConVarsManager convarsManager;
}
