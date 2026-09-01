/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
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
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
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
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */
#include "addresses.h"

#include "shared.h"

namespace addresses
{
    Addresses toolkitAddresses;

    bool Initialize()
    {
        RESOLVE_SIG(g_pSource2Server, "CBaseEntity::CreateEntityByName", shared::g_pGameConfig->GetSignature("UTIL::CreateEntityByName"), toolkitAddresses.CreateEntityByName);
        RESOLVE_SIG(g_pSource2Server, "CBaseEntity::DispatchSpawn", shared::g_pGameConfig->GetSignature("CBaseEntity::DispatchSpawn"), toolkitAddresses.DispatchSpawn);
        RESOLVE_SIG(g_pSource2Server, "CBaseEntity::TakeDamageOld", shared::g_pGameConfig->GetSignature("CBaseEntity::TakeDamage"), toolkitAddresses.TakeDamageOld);
        RESOLVE_SIG(g_pSource2Server, "CBaseModelEntity::SetModel", shared::g_pGameConfig->GetSignature("CBaseModelEntity::SetModel"), toolkitAddresses.SetModel);
        RESOLVE_SIG(g_pSource2Server, "CBasePlayerController::SetPawn", shared::g_pGameConfig->GetSignature("CBasePlayerController::SetPawn"), toolkitAddresses.SetPawn);
        RESOLVE_SIG(g_pSource2Server, "CBasePlayerPawn::SnapViewAngles", shared::g_pGameConfig->GetSignature("CBasePlayerPawn::SnapViewAngles"), toolkitAddresses.SnapViewAngles);
        RESOLVE_SIG(g_pSource2Server, "CGameRules::TerminateRound", shared::g_pGameConfig->GetSignature("CGameRules::TerminateRound"), toolkitAddresses.TerminateRound);
        RESOLVE_SIG(g_pSource2Server, "CCSPlayer_WeaponServices::Destroy", shared::g_pGameConfig->GetSignature("CCSPlayer_WeaponServices::Destroy"), toolkitAddresses.Destroy);
        RESOLVE_SIG(g_pSource2Server, "LegacyGameEventListener", shared::g_pGameConfig->GetSignature("LegacyGameEventListener"), toolkitAddresses.LegacyGameEventListenerAddr);
        RESOLVE_SIG(g_pSource2Server, "CCSPlayerController::SwitchTeam", shared::g_pGameConfig->GetSignature("CCSPlayerController::SwitchTeam"), toolkitAddresses.SwitchTeam);
        RESOLVE_SIG(g_pSource2Server, "CEntityInstance::AcceptInput", shared::g_pGameConfig->GetSignature("CEntityInstance::AcceptInput"), toolkitAddresses.AcceptInput);
        RESOLVE_SIG(g_pSource2Server, "CEntityIOOutput::FireOutputInternal", shared::g_pGameConfig->GetSignature("CEntityIOOutput::FireOutputInternal"), toolkitAddresses.FireOutputInternal);
        RESOLVE_SIG(g_pSource2Server, "CEntitySystem::AddEntityIOEvent", shared::g_pGameConfig->GetSignature("CEntitySystem::AddEntityIOEvent"), toolkitAddresses.AddEntityIOEvent);
        RESOLVE_SIG(g_pSource2Server, "CGameEntitySystem::FindEntityByClassName", shared::g_pGameConfig->GetSignature("CGameEntitySystem::FindEntityByClassName"), toolkitAddresses.FindEntityByClassName);
        RESOLVE_SIG(g_pSource2Server, "CGameEntitySystem::FindEntityByName", shared::g_pGameConfig->GetSignature("CGameEntitySystem::FindEntityByName"), toolkitAddresses.FindEntityByName);
        RESOLVE_SIG(g_pSource2Server, "CTakeDamageInfo::CTakeDamageInfo", shared::g_pGameConfig->GetSignature("CTakeDamageInfo::Constructor"), toolkitAddresses.CTakeDamageInfo);
        RESOLVE_SIG(shared::g_pGameEventSystem, "INetworkMessageProcessingPreFilter::FilterMessage", shared::g_pGameConfig->GetSignature("INetworkMessageProcessingPreFilter::FilterMessage"), toolkitAddresses.FilterMessage);

        // Ported from SwiftlyS2. Resolved optionally: these are a library for
        // plugins rather than something the toolkit itself needs, so a pattern
        // that stops matching after a game update must not block startup.
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CEntityIdentity::AcceptInput", shared::g_pGameConfig->GetSignature("CEntityIdentity::AcceptInput"), toolkitAddresses.IdentityAcceptInput);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_ItemServices::CanAcquire", shared::g_pGameConfig->GetSignature("CCSPlayer_ItemServices::CanAcquire"), toolkitAddresses.CanAcquire);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayerPawn::CanMove", shared::g_pGameConfig->GetSignature("CCSPlayerPawn::CanMove"), toolkitAddresses.CanMove);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayerController::ProcessUserCmd", shared::g_pGameConfig->GetSignature("CCSPlayerController::ProcessUserCmd"), toolkitAddresses.ProcessUserCmd);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CBasePlayerController::OnSimulateUserCommands", shared::g_pGameConfig->GetSignature("CBasePlayerController::OnSimulateUserCommands"), toolkitAddresses.OnSimulateUserCommands);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::AirAccelerate", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::AirAccelerate"), toolkitAddresses.AirAccelerate);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::AirMove", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::AirMove"), toolkitAddresses.AirMove);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::CanUnduck", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::CanUnduck"), toolkitAddresses.CanUnduck);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::CategorizePosition", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::CategorizePosition"), toolkitAddresses.CategorizePosition);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::CheckFalling", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::CheckFalling"), toolkitAddresses.CheckFalling);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::CheckParameters", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::CheckParameters"), toolkitAddresses.CheckParameters);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::CheckVelocity", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::CheckVelocity"), toolkitAddresses.CheckVelocity);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::CheckWater", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::CheckWater"), toolkitAddresses.CheckWater);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::Duck", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::Duck"), toolkitAddresses.Duck);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::Friction", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::Friction"), toolkitAddresses.Friction);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::FullWalkMove", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::FullWalkMove"), toolkitAddresses.FullWalkMove);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::GroundAccelerate", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::GroundAccelerate"), toolkitAddresses.GroundAccelerate);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::LadderMove", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::LadderMove"), toolkitAddresses.LadderMove);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::MoveInit", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::MoveInit"), toolkitAddresses.MoveInit);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::PlayerMove", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::PlayerMove"), toolkitAddresses.PlayerMove);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::ProcessMovement", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::ProcessMovement"), toolkitAddresses.ProcessMovement);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::SetupMove", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::SetupMove"), toolkitAddresses.SetupMove);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::TryPlayerMove", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::TryPlayerMove"), toolkitAddresses.TryPlayerMove);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::WalkMove", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::WalkMove"), toolkitAddresses.WalkMove);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::WaterMove", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::WaterMove"), toolkitAddresses.WaterMove);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::OnJumpLegacy", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::OnJumpLegacy"), toolkitAddresses.OnJumpLegacy);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::OnJumpModern", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::OnJumpModern"), toolkitAddresses.OnJumpModern);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::CheckJumpButtonLegacy", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::CheckJumpButtonLegacy"), toolkitAddresses.CheckJumpButtonLegacy);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CCSPlayer_MovementServices::CheckJumpButtonModern", shared::g_pGameConfig->GetSignature("CCSPlayer_MovementServices::CheckJumpButtonModern"), toolkitAddresses.CheckJumpButtonModern);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CAttributeList::SetOrAddAttributeValueByName", shared::g_pGameConfig->GetSignature("CAttributeList::SetOrAddAttributeValueByName"), toolkitAddresses.SetOrAddAttributeValueByName);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CDecoyProjectile::EmitGrenade", shared::g_pGameConfig->GetSignature("CDecoyProjectile::EmitGrenade"), toolkitAddresses.EmitDecoy);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CFlashbangProjectile::EmitGrenade", shared::g_pGameConfig->GetSignature("CFlashbangProjectile::EmitGrenade"), toolkitAddresses.EmitFlashbang);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CHEGrenadeProjectile::EmitGrenade", shared::g_pGameConfig->GetSignature("CHEGrenadeProjectile::EmitGrenade"), toolkitAddresses.EmitHEGrenade);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CMolotovProjectile::EmitGrenade", shared::g_pGameConfig->GetSignature("CMolotovProjectile::EmitGrenade"), toolkitAddresses.EmitMolotov);
        RESOLVE_SIG_OPTIONAL(g_pSource2Server, "CSmokeGrenadeProjectile::EmitGrenade", shared::g_pGameConfig->GetSignature("CSmokeGrenadeProjectile::EmitGrenade"), toolkitAddresses.EmitSmoke);

        return true;
    }

    DynLibUtils::CModule& Addresses::GetOrLoadModule(void* ptr)
    {
        uintptr_t key = reinterpret_cast<uintptr_t>(ptr);

        auto it = m_Modules.find(key);
        if (it != m_Modules.end())
            return it->second;

        auto [iter, _] = m_Modules.emplace(key, DynLibUtils::CModule(DynLibUtils::CMemory(ptr)));
        return iter->second;
    }

    CBaseEntity_CreateEntityByName_t Addresses::CBaseEntity_CreateEntityByName()
    {
        return CreateEntityByName.RCast<CBaseEntity_CreateEntityByName_t>();
    }

    CBaseEntity_DispatchSpawn_t Addresses::CBaseEntity_DispatchSpawn()
    {
        return DispatchSpawn.RCast<CBaseEntity_DispatchSpawn_t>();
    }

    CBaseEntity_TakeDamageOld_t Addresses::CBaseEntity_TakeDamageOld()
    {
        return TakeDamageOld.RCast<CBaseEntity_TakeDamageOld_t>();
    }

    CBaseModelEntity_SetModel_t Addresses::CBaseModelEntity_SetModel()
    {
        return SetModel.RCast<CBaseModelEntity_SetModel_t>();
    }

    CBasePlayerController_SetPawn_t Addresses::CBasePlayerController_SetPawn()
    {
        return SetPawn.RCast<CBasePlayerController_SetPawn_t>();
    }

    CBasePlayerPawn_SnapViewAngles_t Addresses::CBasePlayerPawn_SnapViewAngles()
    {
        return SnapViewAngles.RCast<CBasePlayerPawn_SnapViewAngles_t>();
    }

    CGameRules_TerminateRound_t Addresses::CGameRules_TerminateRound()
    {
        return TerminateRound.RCast<CGameRules_TerminateRound_t>();
    }

    CCSPlayer_WeaponServices_Destroy_t Addresses::CCSPlayer_WeaponServices_Destroy()
    {
        return Destroy.RCast<CCSPlayer_WeaponServices_Destroy_t>();
    }

    LegacyGameEventListener_t Addresses::LegacyGameEventListener()
    {
        return LegacyGameEventListenerAddr.RCast<LegacyGameEventListener_t>();
    }

    CCSPlayerController_SwitchTeam_t Addresses::CCSPlayerController_SwitchTeam()
    {
        return SwitchTeam.RCast<CCSPlayerController_SwitchTeam_t>();
    }

    CEntityInstance_AcceptInput_t Addresses::CEntityInstance_AcceptInput()
    {
        return AcceptInput.RCast<CEntityInstance_AcceptInput_t>();
    }

    CEntityIOOutput_FireOutputInternal_t Addresses::CEntityIOOutput_FireOutputInternal()
    {
        return FireOutputInternal.RCast<CEntityIOOutput_FireOutputInternal_t>();
    }

    CEntitySystem_AddEntityIOEvent_t Addresses::CEntitySystem_AddEntityIOEvent()
    {
        return AddEntityIOEvent.RCast<CEntitySystem_AddEntityIOEvent_t>();
    }

    CGameEntitySystem_FindEntityByClassName_t Addresses::CGameEntitySystem_FindEntityByClassName()
    {
        return FindEntityByClassName.RCast<CGameEntitySystem_FindEntityByClassName_t>();
    }

    CGameEntitySystem_FindEntityByName_t Addresses::CGameEntitySystem_FindEntityByName()
    {
        return FindEntityByName.RCast<CGameEntitySystem_FindEntityByName_t>();
    }

    CTakeDamageInfo_CTakeDamageInfo_t Addresses::CTakeDamageInfo_CTakeDamageInfo()
    {
        return CTakeDamageInfo.RCast<CTakeDamageInfo_CTakeDamageInfo_t>();
    }

    INetworkMessageProcessingPreFilter_FilterMessage_t Addresses::INetworkMessageProcessingPreFilter_FilterMessage()
    {
        return FilterMessage.RCast<INetworkMessageProcessingPreFilter_FilterMessage_t>();
    }

    CEntityIdentity_AcceptInput_t Addresses::CEntityIdentity_AcceptInput()
    {
        return IdentityAcceptInput.RCast<CEntityIdentity_AcceptInput_t>();
    }

    CCSPlayer_ItemServices_CanAcquire_t Addresses::CCSPlayer_ItemServices_CanAcquire()
    {
        return CanAcquire.RCast<CCSPlayer_ItemServices_CanAcquire_t>();
    }

    CCSPlayerPawn_CanMove_t Addresses::CCSPlayerPawn_CanMove()
    {
        return CanMove.RCast<CCSPlayerPawn_CanMove_t>();
    }

    CCSPlayerController_ProcessUserCmd_t Addresses::CCSPlayerController_ProcessUserCmd()
    {
        return ProcessUserCmd.RCast<CCSPlayerController_ProcessUserCmd_t>();
    }

    CBasePlayerController_OnSimulateUserCommands_t Addresses::CBasePlayerController_OnSimulateUserCommands()
    {
        return OnSimulateUserCommands.RCast<CBasePlayerController_OnSimulateUserCommands_t>();
    }

    CCSPlayer_MovementServices_AirAccelerate_t Addresses::CCSPlayer_MovementServices_AirAccelerate()
    {
        return AirAccelerate.RCast<CCSPlayer_MovementServices_AirAccelerate_t>();
    }

    CCSPlayer_MovementServices_AirMove_t Addresses::CCSPlayer_MovementServices_AirMove()
    {
        return AirMove.RCast<CCSPlayer_MovementServices_AirMove_t>();
    }

    CCSPlayer_MovementServices_CanUnduck_t Addresses::CCSPlayer_MovementServices_CanUnduck()
    {
        return CanUnduck.RCast<CCSPlayer_MovementServices_CanUnduck_t>();
    }

    CCSPlayer_MovementServices_CategorizePosition_t Addresses::CCSPlayer_MovementServices_CategorizePosition()
    {
        return CategorizePosition.RCast<CCSPlayer_MovementServices_CategorizePosition_t>();
    }

    CCSPlayer_MovementServices_CheckFalling_t Addresses::CCSPlayer_MovementServices_CheckFalling()
    {
        return CheckFalling.RCast<CCSPlayer_MovementServices_CheckFalling_t>();
    }

    CCSPlayer_MovementServices_CheckParameters_t Addresses::CCSPlayer_MovementServices_CheckParameters()
    {
        return CheckParameters.RCast<CCSPlayer_MovementServices_CheckParameters_t>();
    }

    CCSPlayer_MovementServices_CheckVelocity_t Addresses::CCSPlayer_MovementServices_CheckVelocity()
    {
        return CheckVelocity.RCast<CCSPlayer_MovementServices_CheckVelocity_t>();
    }

    CCSPlayer_MovementServices_CheckWater_t Addresses::CCSPlayer_MovementServices_CheckWater()
    {
        return CheckWater.RCast<CCSPlayer_MovementServices_CheckWater_t>();
    }

    CCSPlayer_MovementServices_Duck_t Addresses::CCSPlayer_MovementServices_Duck()
    {
        return Duck.RCast<CCSPlayer_MovementServices_Duck_t>();
    }

    CCSPlayer_MovementServices_Friction_t Addresses::CCSPlayer_MovementServices_Friction()
    {
        return Friction.RCast<CCSPlayer_MovementServices_Friction_t>();
    }

    CCSPlayer_MovementServices_FullWalkMove_t Addresses::CCSPlayer_MovementServices_FullWalkMove()
    {
        return FullWalkMove.RCast<CCSPlayer_MovementServices_FullWalkMove_t>();
    }

    CCSPlayer_MovementServices_GroundAccelerate_t Addresses::CCSPlayer_MovementServices_GroundAccelerate()
    {
        return GroundAccelerate.RCast<CCSPlayer_MovementServices_GroundAccelerate_t>();
    }

    CCSPlayer_MovementServices_LadderMove_t Addresses::CCSPlayer_MovementServices_LadderMove()
    {
        return LadderMove.RCast<CCSPlayer_MovementServices_LadderMove_t>();
    }

    CCSPlayer_MovementServices_MoveInit_t Addresses::CCSPlayer_MovementServices_MoveInit()
    {
        return MoveInit.RCast<CCSPlayer_MovementServices_MoveInit_t>();
    }

    CCSPlayer_MovementServices_PlayerMove_t Addresses::CCSPlayer_MovementServices_PlayerMove()
    {
        return PlayerMove.RCast<CCSPlayer_MovementServices_PlayerMove_t>();
    }

    CCSPlayer_MovementServices_ProcessMovement_t Addresses::CCSPlayer_MovementServices_ProcessMovement()
    {
        return ProcessMovement.RCast<CCSPlayer_MovementServices_ProcessMovement_t>();
    }

    CCSPlayer_MovementServices_SetupMove_t Addresses::CCSPlayer_MovementServices_SetupMove()
    {
        return SetupMove.RCast<CCSPlayer_MovementServices_SetupMove_t>();
    }

    CCSPlayer_MovementServices_TryPlayerMove_t Addresses::CCSPlayer_MovementServices_TryPlayerMove()
    {
        return TryPlayerMove.RCast<CCSPlayer_MovementServices_TryPlayerMove_t>();
    }

    CCSPlayer_MovementServices_WalkMove_t Addresses::CCSPlayer_MovementServices_WalkMove()
    {
        return WalkMove.RCast<CCSPlayer_MovementServices_WalkMove_t>();
    }

    CCSPlayer_MovementServices_WaterMove_t Addresses::CCSPlayer_MovementServices_WaterMove()
    {
        return WaterMove.RCast<CCSPlayer_MovementServices_WaterMove_t>();
    }

    CCSPlayer_MovementServices_OnJumpLegacy_t Addresses::CCSPlayer_MovementServices_OnJumpLegacy()
    {
        return OnJumpLegacy.RCast<CCSPlayer_MovementServices_OnJumpLegacy_t>();
    }

    CCSPlayer_MovementServices_OnJumpModern_t Addresses::CCSPlayer_MovementServices_OnJumpModern()
    {
        return OnJumpModern.RCast<CCSPlayer_MovementServices_OnJumpModern_t>();
    }

    CCSPlayer_MovementServices_CheckJumpButtonLegacy_t Addresses::CCSPlayer_MovementServices_CheckJumpButtonLegacy()
    {
        return CheckJumpButtonLegacy.RCast<CCSPlayer_MovementServices_CheckJumpButtonLegacy_t>();
    }

    CCSPlayer_MovementServices_CheckJumpButtonModern_t Addresses::CCSPlayer_MovementServices_CheckJumpButtonModern()
    {
        return CheckJumpButtonModern.RCast<CCSPlayer_MovementServices_CheckJumpButtonModern_t>();
    }

    CAttributeList_SetOrAddAttributeValueByName_t Addresses::CAttributeList_SetOrAddAttributeValueByName()
    {
        return SetOrAddAttributeValueByName.RCast<CAttributeList_SetOrAddAttributeValueByName_t>();
    }

    CDecoyProjectile_EmitGrenade_t Addresses::CDecoyProjectile_EmitGrenade()
    {
        return EmitDecoy.RCast<CDecoyProjectile_EmitGrenade_t>();
    }

    CFlashbangProjectile_EmitGrenade_t Addresses::CFlashbangProjectile_EmitGrenade()
    {
        return EmitFlashbang.RCast<CFlashbangProjectile_EmitGrenade_t>();
    }

    CHEGrenadeProjectile_EmitGrenade_t Addresses::CHEGrenadeProjectile_EmitGrenade()
    {
        return EmitHEGrenade.RCast<CHEGrenadeProjectile_EmitGrenade_t>();
    }

    CMolotovProjectile_EmitGrenade_t Addresses::CMolotovProjectile_EmitGrenade()
    {
        return EmitMolotov.RCast<CMolotovProjectile_EmitGrenade_t>();
    }

    CSmokeGrenadeProjectile_EmitGrenade_t Addresses::CSmokeGrenadeProjectile_EmitGrenade()
    {
        return EmitSmoke.RCast<CSmokeGrenadeProjectile_EmitGrenade_t>();
    }
}
