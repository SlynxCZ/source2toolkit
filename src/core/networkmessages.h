/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
 * AlliedModders LLC. All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
 * AlliedModders LLC give you permission to link the code of this program
 * (as well as its derivative works) to "Counter-Strike 2," "Source 2,"
 * "Steam," and any Game MODs or server software running on software by
 * Valve Corporation. You must obey the GNU General Public License in all
 * respects for all other code used.
 *
 * Additionally, this exception applies to all derivative works unless
 * otherwise stated in LICENSE.txt.
 *
 * Authors:
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */
#pragma once
#include "shared.h"

#include "source2toolkit/IToolkitNetworkMessages.h"

#include <unordered_map>

namespace networkmessages
{
    class NetworkMessagesManager : public IToolkitNetworkMessages
    {
    public:
        void* AllocateNetMessageByID(int msgid) override;
        void* AllocateNetMessageByPartialName(const char* name) override;
        void DeallocateNetMessage(void* msg) override;

        bool HasField(void* msg, const char* fieldName) override;

        int GetInt32(void* msg, const char* fieldName) override;
        int GetRepeatedInt32(void* msg, const char* fieldName, int index) override;
        void SetInt32(void* msg, const char* fieldName, int value) override;
        void SetRepeatedInt32(void* msg, const char* fieldName, int index, int value) override;
        void AddInt32(void* msg, const char* fieldName, int value) override;

        int64_t GetInt64(void* msg, const char* fieldName) override;
        int64_t GetRepeatedInt64(void* msg, const char* fieldName, int index) override;
        void SetInt64(void* msg, const char* fieldName, int64_t value) override;
        void SetRepeatedInt64(void* msg, const char* fieldName, int index, int64_t value) override;
        void AddInt64(void* msg, const char* fieldName, int64_t value) override;

        uint32_t GetUInt32(void* msg, const char* fieldName) override;
        uint32_t GetRepeatedUInt32(void* msg, const char* fieldName, int index) override;
        void SetUInt32(void* msg, const char* fieldName, uint32_t value) override;
        void SetRepeatedUInt32(void* msg, const char* fieldName, int index, uint32_t value) override;
        void AddUInt32(void* msg, const char* fieldName, uint32_t value) override;

        uint64_t GetUInt64(void* msg, const char* fieldName) override;
        uint64_t GetRepeatedUInt64(void* msg, const char* fieldName, int index) override;
        void SetUInt64(void* msg, const char* fieldName, uint64_t value) override;
        void SetRepeatedUInt64(void* msg, const char* fieldName, int index, uint64_t value) override;
        void AddUInt64(void* msg, const char* fieldName, uint64_t value) override;

        bool GetBool(void* msg, const char* fieldName) override;
        bool GetRepeatedBool(void* msg, const char* fieldName, int index) override;
        void SetBool(void* msg, const char* fieldName, bool value) override;
        void SetRepeatedBool(void* msg, const char* fieldName, int index, bool value) override;
        void AddBool(void* msg, const char* fieldName, bool value) override;

        float GetFloat(void* msg, const char* fieldName) override;
        float GetRepeatedFloat(void* msg, const char* fieldName, int index) override;
        void SetFloat(void* msg, const char* fieldName, float value) override;
        void SetRepeatedFloat(void* msg, const char* fieldName, int index, float value) override;
        void AddFloat(void* msg, const char* fieldName, float value) override;

        double GetDouble(void* msg, const char* fieldName) override;
        double GetRepeatedDouble(void* msg, const char* fieldName, int index) override;
        void SetDouble(void* msg, const char* fieldName, double value) override;
        void SetRepeatedDouble(void* msg, const char* fieldName, int index, double value) override;
        void AddDouble(void* msg, const char* fieldName, double value) override;

        std::string GetString(void* msg, const char* fieldName) override;
        std::string GetRepeatedString(void* msg, const char* fieldName, int index) override;
        void SetString(void* msg, const char* fieldName, const char* value) override;
        void SetRepeatedString(void* msg, const char* fieldName, int index, const char* value) override;
        void AddString(void* msg, const char* fieldName, const char* value) override;

        Vector2D GetVector2D(void* msg, const char* fieldName) override;
        Vector2D GetRepeatedVector2D(void* msg, const char* fieldName, int index) override;
        void SetVector2D(void* msg, const char* fieldName, Vector2D value) override;
        void SetRepeatedVector2D(void* msg, const char* fieldName, int index, Vector2D value) override;
        void AddVector2D(void* msg, const char* fieldName, Vector2D value) override;

        Vector GetVector(void* msg, const char* fieldName) override;
        Vector GetRepeatedVector(void* msg, const char* fieldName, int index) override;
        void SetVector(void* msg, const char* fieldName, Vector value) override;
        void SetRepeatedVector(void* msg, const char* fieldName, int index, Vector value) override;
        void AddVector(void* msg, const char* fieldName, Vector value) override;

        Color GetColor(void* msg, const char* fieldName) override;
        Color GetRepeatedColor(void* msg, const char* fieldName, int index) override;
        void SetColor(void* msg, const char* fieldName, Color value) override;
        void SetRepeatedColor(void* msg, const char* fieldName, int index, Color value) override;
        void AddColor(void* msg, const char* fieldName, Color value) override;

        QAngle GetQAngle(void* msg, const char* fieldName) override;
        QAngle GetRepeatedQAngle(void* msg, const char* fieldName, int index) override;
        void SetQAngle(void* msg, const char* fieldName, QAngle value) override;
        void SetRepeatedQAngle(void* msg, const char* fieldName, int index, QAngle value) override;
        void AddQAngle(void* msg, const char* fieldName, QAngle value) override;

        int GetBytes(uint8_t* out, void* msg, const char* fieldName) override;
        int GetRepeatedBytes(uint8_t* out, void* msg, const char* fieldName, int index) override;
        void SetBytes(void* msg, const char* fieldName, const char* value, int valueLength) override;
        void SetRepeatedBytes(void* msg, const char* fieldName, int index, const char* value, int valueLength) override;
        void AddBytes(void* msg, const char* fieldName, const char* value, int valueLength) override;

        void* GetNestedMessage(void* msg, const char* fieldName) override;
        void* GetRepeatedNestedMessage(void* msg, const char* fieldName, int index) override;
        void* AddNestedMessage(void* msg, const char* fieldName) override;

        int GetRepeatedFieldSize(void* msg, const char* fieldName) override;
        void ClearRepeatedField(void* msg, const char* fieldName) override;
        void Clear(void* msg) override;

        void SendMessage(void* msg, int msgid, CPlayerSlot slot) override;
        void SendMessageToPlayers(void* msg, int msgid, uint64_t playermask) override;

        void HookServerMessage(PluginId owner, NetMessageServerHook handler) override;
        void UnhookServerMessage(PluginId owner) override;

        void HookClientMessage(PluginId owner, NetMessageClientHook handler) override;
        void UnhookClientMessage(PluginId owner) override;

        void HookServerInternalMessage(PluginId owner, NetMessageClientHook handler) override;
        void UnhookServerInternalMessage(PluginId owner) override;

        // Called when a plugin unloads, like every other plugin-owned registry.
        void RemoveAllForPlugin(PluginId id);

    public:

        std::unordered_map<PluginId, NetMessageServerHook> m_serverHooks;
        std::unordered_map<PluginId, NetMessageClientHook> m_clientHooks;
        std::unordered_map<PluginId, NetMessageClientHook> m_serverInternalHooks;
    };

    extern NetworkMessagesManager networkMessagesManager;

    META_RES DispatchServerHook(uint64_t* clients, int messageid, void* msg);
    META_RES DispatchClientHook(CPlayerSlot slot, int messageid, void* msg);
    META_RES DispatchServerInternalHook(CPlayerSlot slot, int messageid, void* msg);
}
