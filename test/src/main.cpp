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
#include "main.h"

#include "source2toolkit/IToolkitApi.h"
#include "source2toolkit/IToolkitCommands.h"
#include "source2toolkit/IToolkitEvents.h"
#include "source2toolkit/IToolkitMemory.h"
#include "source2toolkit/IToolkitModule.h"
#include "source2toolkit/IToolkitTypes.h"

#include "source2toolkit/utils/commands.h"
#include "source2toolkit/utils/convars.h"
#include "source2toolkit/utils/events.h"
#include "source2toolkit/utils/gameconfig.h"
#include "source2toolkit/utils/scheduler.h"

#include "source2toolkit/schema/schema.h"
#include "source2toolkit/schema/serversideclient.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController.h"

// --- schema entity classes ---
#include "source2toolkit/schema/entity/classes/AnimGraph2SerializedPoseRecipeSlot_t.h"
#include "source2toolkit/schema/entity/classes/AutoRoomDoorwayPairs_t.h"
#include "source2toolkit/schema/entity/classes/CAI_ChangeHintGroup.h"
#include "source2toolkit/schema/entity/classes/CAI_Expresser.h"
#include "source2toolkit/schema/entity/classes/CAI_ExpresserWithFollowup.h"
#include "source2toolkit/schema/entity/classes/CAK47.h"
#include "source2toolkit/schema/entity/classes/CAmbientGeneric.h"
#include "source2toolkit/schema/entity/classes/CAnimGraphControllerBase.h"
#include "source2toolkit/schema/entity/classes/CAnimGraphControllerManager.h"
#include "source2toolkit/schema/entity/classes/CAttributeContainer.h"
#include "source2toolkit/schema/entity/classes/CAttributeList.h"
#include "source2toolkit/schema/entity/classes/CAttributeManager.h"
#include "source2toolkit/schema/entity/classes/CAttributeManager__cached_attribute_float_t.h"
#include "source2toolkit/schema/entity/classes/CBarnLight.h"
#include "source2toolkit/schema/entity/classes/CBaseAnimGraph.h"
#include "source2toolkit/schema/entity/classes/CBaseAnimGraphController.h"
#include "source2toolkit/schema/entity/classes/CBaseAnimGraphDestructibleParts_GraphController.h"
#include "source2toolkit/schema/entity/classes/CBaseButton.h"
#include "source2toolkit/schema/entity/classes/CBaseCSGrenade.h"
#include "source2toolkit/schema/entity/classes/CBaseCSGrenadeProjectile.h"
#include "source2toolkit/schema/entity/classes/CBaseClientUIEntity.h"
#include "source2toolkit/schema/entity/classes/CBaseCombatCharacter.h"
#include "source2toolkit/schema/entity/classes/CBaseDMStart.h"
#include "source2toolkit/schema/entity/classes/CBaseDoor.h"
#include "source2toolkit/schema/entity/classes/CBaseEntity.h"
#include "source2toolkit/schema/entity/classes/CBaseFilter.h"
#include "source2toolkit/schema/entity/classes/CBaseGrenade.h"
#include "source2toolkit/schema/entity/classes/CBaseIssue.h"
#include "source2toolkit/schema/entity/classes/CBaseModelEntity.h"
#include "source2toolkit/schema/entity/classes/CBaseModelEntity__OnDamageLevelChangedArgs_t.h"
#include "source2toolkit/schema/entity/classes/CBaseMoveBehavior.h"
#include "source2toolkit/schema/entity/classes/CBasePlatTrain.h"
#include "source2toolkit/schema/entity/classes/CBasePlayerController.h"
#include "source2toolkit/schema/entity/classes/CBasePlayerPawn.h"
#include "source2toolkit/schema/entity/classes/CBasePlayerVData.h"
#include "source2toolkit/schema/entity/classes/CBasePlayerWeapon.h"
#include "source2toolkit/schema/entity/classes/CBasePlayerWeaponVData.h"
#include "source2toolkit/schema/entity/classes/CBaseProp.h"
#include "source2toolkit/schema/entity/classes/CBasePropDoor.h"
#include "source2toolkit/schema/entity/classes/CBasePulseGraphInstance.h"
#include "source2toolkit/schema/entity/classes/CBaseToggle.h"
#include "source2toolkit/schema/entity/classes/CBaseTrigger.h"
#include "source2toolkit/schema/entity/classes/CBeam.h"
#include "source2toolkit/schema/entity/classes/CBlood.h"
#include "source2toolkit/schema/entity/classes/CBodyComponent.h"
#include "source2toolkit/schema/entity/classes/CBodyComponentBaseAnimGraph.h"
#include "source2toolkit/schema/entity/classes/CBodyComponentBaseModelEntity.h"
#include "source2toolkit/schema/entity/classes/CBodyComponentPoint.h"
#include "source2toolkit/schema/entity/classes/CBodyComponentSkeletonInstance.h"
#include "source2toolkit/schema/entity/classes/CBombTarget.h"
#include "source2toolkit/schema/entity/classes/CBot.h"
#include "source2toolkit/schema/entity/classes/CBreakable.h"
#include "source2toolkit/schema/entity/classes/CBreakableProp.h"
#include "source2toolkit/schema/entity/classes/CBuoyancyHelper.h"
#include "source2toolkit/schema/entity/classes/CBuyZone.h"
#include "source2toolkit/schema/entity/classes/CC4.h"
#include "source2toolkit/schema/entity/classes/CCS2ChickenGraphController.h"
#include "source2toolkit/schema/entity/classes/CCS2PawnGraphController.h"
#include "source2toolkit/schema/entity/classes/CCS2WeaponGraphController.h"
#include "source2toolkit/schema/entity/classes/CCSBot.h"
#include "source2toolkit/schema/entity/classes/CCSGO_EndOfMatchLineupEnd.h"
#include "source2toolkit/schema/entity/classes/CCSGO_EndOfMatchLineupEndpoint.h"
#include "source2toolkit/schema/entity/classes/CCSGO_EndOfMatchLineupStart.h"
#include "source2toolkit/schema/entity/classes/CCSGO_TeamIntroCharacterPosition.h"
#include "source2toolkit/schema/entity/classes/CCSGO_TeamIntroCounterTerroristPosition.h"
#include "source2toolkit/schema/entity/classes/CCSGO_TeamIntroTerroristPosition.h"
#include "source2toolkit/schema/entity/classes/CCSGO_TeamPreviewCharacterPosition.h"
#include "source2toolkit/schema/entity/classes/CCSGO_TeamSelectCharacterPosition.h"
#include "source2toolkit/schema/entity/classes/CCSGO_TeamSelectCounterTerroristPosition.h"
#include "source2toolkit/schema/entity/classes/CCSGO_TeamSelectTerroristPosition.h"
#include "source2toolkit/schema/entity/classes/CCSGO_WingmanIntroCharacterPosition.h"
#include "source2toolkit/schema/entity/classes/CCSGO_WingmanIntroCounterTerroristPosition.h"
#include "source2toolkit/schema/entity/classes/CCSGO_WingmanIntroTerroristPosition.h"
#include "source2toolkit/schema/entity/classes/CCSGameModeRules.h"
#include "source2toolkit/schema/entity/classes/CCSGameModeRules_ArmsRace.h"
#include "source2toolkit/schema/entity/classes/CCSGameModeRules_Deathmatch.h"
#include "source2toolkit/schema/entity/classes/CCSGameModeRules_Noop.h"
#include "source2toolkit/schema/entity/classes/CCSGameRules.h"
#include "source2toolkit/schema/entity/classes/CCSGameRulesProxy.h"
#include "source2toolkit/schema/entity/classes/CCSMinimapBoundary.h"
#include "source2toolkit/schema/entity/classes/CCSObserverPawn.h"
#include "source2toolkit/schema/entity/classes/CCSObserver_CameraServices.h"
#include "source2toolkit/schema/entity/classes/CCSObserver_MovementServices.h"
#include "source2toolkit/schema/entity/classes/CCSObserver_ObserverServices.h"
#include "source2toolkit/schema/entity/classes/CCSObserver_UseServices.h"
#include "source2toolkit/schema/entity/classes/CCSPetPlacement.h"
#include "source2toolkit/schema/entity/classes/CCSPlace.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerAnimationState.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerBase_CameraServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController_ActionTrackingServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController_DamageServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController_InGameMoneyServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerController_InventoryServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerLegacyJump.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerModernJump.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerPawn.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerPawnBase.h"
#include "source2toolkit/schema/entity/classes/CCSPlayerResource.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_ActionTrackingServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_AimPunchServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_BulletServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_BuyServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_CameraServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_DamageReactServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_HostageServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_ItemServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_MovementServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_PingServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_RadioServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_UseServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_WaterServices.h"
#include "source2toolkit/schema/entity/classes/CCSPlayer_WeaponServices.h"
#include "source2toolkit/schema/entity/classes/CCSPointScriptEntity.h"
#include "source2toolkit/schema/entity/classes/CCSSprite.h"
#include "source2toolkit/schema/entity/classes/CCSTeam.h"
#include "source2toolkit/schema/entity/classes/CCSWeaponBase.h"
#include "source2toolkit/schema/entity/classes/CCSWeaponBaseGun.h"
#include "source2toolkit/schema/entity/classes/CCSWeaponBaseShotgun.h"
#include "source2toolkit/schema/entity/classes/CCSWeaponBaseVData.h"
#include "source2toolkit/schema/entity/classes/CCashStack.h"
#include "source2toolkit/schema/entity/classes/CChangeLevel.h"
#include "source2toolkit/schema/entity/classes/CChicken.h"
#include "source2toolkit/schema/entity/classes/CChoreoComponent.h"
#include "source2toolkit/schema/entity/classes/CChoreoInfoTarget.h"
#include "source2toolkit/schema/entity/classes/CCitadelSoundOpvarSetOBB.h"
#include "source2toolkit/schema/entity/classes/CCollisionProperty.h"
#include "source2toolkit/schema/entity/classes/CColorCorrection.h"
#include "source2toolkit/schema/entity/classes/CColorCorrectionVolume.h"
#include "source2toolkit/schema/entity/classes/CCommentaryAuto.h"
#include "source2toolkit/schema/entity/classes/CCommentaryViewPosition.h"
#include "source2toolkit/schema/entity/classes/CConstantForceController.h"
#include "source2toolkit/schema/entity/classes/CConstraintAnchor.h"
#include "source2toolkit/schema/entity/classes/CCredits.h"
#include "source2toolkit/schema/entity/classes/CDEagle.h"
#include "source2toolkit/schema/entity/classes/CDamageRecord.h"
#include "source2toolkit/schema/entity/classes/CDebugHistory.h"
#include "source2toolkit/schema/entity/classes/CDecalGroupVData.h"
#include "source2toolkit/schema/entity/classes/CDecoyGrenade.h"
#include "source2toolkit/schema/entity/classes/CDecoyProjectile.h"
#include "source2toolkit/schema/entity/classes/CDestructiblePartsComponent.h"
#include "source2toolkit/schema/entity/classes/CDynamicLight.h"
#include "source2toolkit/schema/entity/classes/CDynamicNavConnectionsVolume.h"
#include "source2toolkit/schema/entity/classes/CDynamicProp.h"
#include "source2toolkit/schema/entity/classes/CDynamicPropAlias_cable_dynamic.h"
#include "source2toolkit/schema/entity/classes/CDynamicPropAlias_dynamic_prop.h"
#include "source2toolkit/schema/entity/classes/CDynamicPropAlias_prop_dynamic_override.h"
#include "source2toolkit/schema/entity/classes/CEconEntity.h"
#include "source2toolkit/schema/entity/classes/CEconItemAttribute.h"
#include "source2toolkit/schema/entity/classes/CEconItemView.h"
#include "source2toolkit/schema/entity/classes/CEconWearable.h"
#include "source2toolkit/schema/entity/classes/CEmptyGraphController.h"
#include "source2toolkit/schema/entity/classes/CEnableMotionFixup.h"
#include "source2toolkit/schema/entity/classes/CEntityAttributeTable.h"
#include "source2toolkit/schema/entity/classes/CEntityBlocker.h"
#include "source2toolkit/schema/entity/classes/CEntityDissolve.h"
#include "source2toolkit/schema/entity/classes/CEntityFlame.h"
#include "source2toolkit/schema/entity/classes/CEntitySubclassVDataBase.h"
#include "source2toolkit/schema/entity/classes/CEnvBeam.h"
#include "source2toolkit/schema/entity/classes/CEnvBeverage.h"
#include "source2toolkit/schema/entity/classes/CEnvCombinedLightProbeVolume.h"
#include "source2toolkit/schema/entity/classes/CEnvCombinedLightProbeVolumeAlias_func_combined_light_probe_volume.h"
#include "source2toolkit/schema/entity/classes/CEnvCubemap.h"
#include "source2toolkit/schema/entity/classes/CEnvCubemapBox.h"
#include "source2toolkit/schema/entity/classes/CEnvCubemapFog.h"
#include "source2toolkit/schema/entity/classes/CEnvDecal.h"
#include "source2toolkit/schema/entity/classes/CEnvDetailController.h"
#include "source2toolkit/schema/entity/classes/CEnvEntityIgniter.h"
#include "source2toolkit/schema/entity/classes/CEnvEntityMaker.h"
#include "source2toolkit/schema/entity/classes/CEnvExplosion.h"
#include "source2toolkit/schema/entity/classes/CEnvFade.h"
#include "source2toolkit/schema/entity/classes/CEnvGlobal.h"
#include "source2toolkit/schema/entity/classes/CEnvHudHint.h"
#include "source2toolkit/schema/entity/classes/CEnvInstructorHint.h"
#include "source2toolkit/schema/entity/classes/CEnvInstructorVRHint.h"
#include "source2toolkit/schema/entity/classes/CEnvLaser.h"
#include "source2toolkit/schema/entity/classes/CEnvLightProbeVolume.h"
#include "source2toolkit/schema/entity/classes/CEnvMuzzleFlash.h"
#include "source2toolkit/schema/entity/classes/CEnvParticleGlow.h"
#include "source2toolkit/schema/entity/classes/CEnvShake.h"
#include "source2toolkit/schema/entity/classes/CEnvSky.h"
#include "source2toolkit/schema/entity/classes/CEnvSoundscape.h"
#include "source2toolkit/schema/entity/classes/CEnvSoundscapeAlias_snd_soundscape.h"
#include "source2toolkit/schema/entity/classes/CEnvSoundscapeProxy.h"
#include "source2toolkit/schema/entity/classes/CEnvSoundscapeProxyAlias_snd_soundscape_proxy.h"
#include "source2toolkit/schema/entity/classes/CEnvSoundscapeTriggerable.h"
#include "source2toolkit/schema/entity/classes/CEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable.h"
#include "source2toolkit/schema/entity/classes/CEnvSpark.h"
#include "source2toolkit/schema/entity/classes/CEnvSplash.h"
#include "source2toolkit/schema/entity/classes/CEnvTilt.h"
#include "source2toolkit/schema/entity/classes/CEnvViewPunch.h"
#include "source2toolkit/schema/entity/classes/CEnvVolumetricFogController.h"
#include "source2toolkit/schema/entity/classes/CEnvVolumetricFogVolume.h"
#include "source2toolkit/schema/entity/classes/CEnvWind.h"
#include "source2toolkit/schema/entity/classes/CEnvWindController.h"
#include "source2toolkit/schema/entity/classes/CEnvWindShared.h"
#include "source2toolkit/schema/entity/classes/CEnvWindVolume.h"
#include "source2toolkit/schema/entity/classes/CExampleSchemaVData_Monomorphic.h"
#include "source2toolkit/schema/entity/classes/CExampleSchemaVData_PolymorphicBase.h"
#include "source2toolkit/schema/entity/classes/CExampleSchemaVData_PolymorphicDerivedA.h"
#include "source2toolkit/schema/entity/classes/CExampleSchemaVData_PolymorphicDerivedB.h"
#include "source2toolkit/schema/entity/classes/CFilterAttributeInt.h"
#include "source2toolkit/schema/entity/classes/CFilterClass.h"
#include "source2toolkit/schema/entity/classes/CFilterContext.h"
#include "source2toolkit/schema/entity/classes/CFilterEnemy.h"
#include "source2toolkit/schema/entity/classes/CFilterLOS.h"
#include "source2toolkit/schema/entity/classes/CFilterMassGreater.h"
#include "source2toolkit/schema/entity/classes/CFilterModel.h"
#include "source2toolkit/schema/entity/classes/CFilterMultiple.h"
#include "source2toolkit/schema/entity/classes/CFilterName.h"
#include "source2toolkit/schema/entity/classes/CFilterProximity.h"
#include "source2toolkit/schema/entity/classes/CFilterTeam.h"
#include "source2toolkit/schema/entity/classes/CFireCrackerBlast.h"
#include "source2toolkit/schema/entity/classes/CFiringModeFloat.h"
#include "source2toolkit/schema/entity/classes/CFiringModeInt.h"
#include "source2toolkit/schema/entity/classes/CFish.h"
#include "source2toolkit/schema/entity/classes/CFishPool.h"
#include "source2toolkit/schema/entity/classes/CFlashbang.h"
#include "source2toolkit/schema/entity/classes/CFlashbangProjectile.h"
#include "source2toolkit/schema/entity/classes/CFogController.h"
#include "source2toolkit/schema/entity/classes/CFogTrigger.h"
#include "source2toolkit/schema/entity/classes/CFogVolume.h"
#include "source2toolkit/schema/entity/classes/CFootstepControl.h"
#include "source2toolkit/schema/entity/classes/CFuncBrush.h"
#include "source2toolkit/schema/entity/classes/CFuncConveyor.h"
#include "source2toolkit/schema/entity/classes/CFuncElectrifiedVolume.h"
#include "source2toolkit/schema/entity/classes/CFuncIllusionary.h"
#include "source2toolkit/schema/entity/classes/CFuncInteractionLayerClip.h"
#include "source2toolkit/schema/entity/classes/CFuncLadder.h"
#include "source2toolkit/schema/entity/classes/CFuncLadderAlias_func_useableladder.h"
#include "source2toolkit/schema/entity/classes/CFuncMonitor.h"
#include "source2toolkit/schema/entity/classes/CFuncMoveLinear.h"
#include "source2toolkit/schema/entity/classes/CFuncMoveLinearAlias_momentary_door.h"
#include "source2toolkit/schema/entity/classes/CFuncMover.h"
#include "source2toolkit/schema/entity/classes/CFuncNavBlocker.h"
#include "source2toolkit/schema/entity/classes/CFuncNavObstruction.h"
#include "source2toolkit/schema/entity/classes/CFuncPlat.h"
#include "source2toolkit/schema/entity/classes/CFuncPlatRot.h"
#include "source2toolkit/schema/entity/classes/CFuncPropRespawnZone.h"
#include "source2toolkit/schema/entity/classes/CFuncRetakeBarrier.h"
#include "source2toolkit/schema/entity/classes/CFuncRotating.h"
#include "source2toolkit/schema/entity/classes/CFuncRotator.h"
#include "source2toolkit/schema/entity/classes/CFuncShatterglass.h"
#include "source2toolkit/schema/entity/classes/CFuncTankTrain.h"
#include "source2toolkit/schema/entity/classes/CFuncTimescale.h"
#include "source2toolkit/schema/entity/classes/CFuncTrackAuto.h"
#include "source2toolkit/schema/entity/classes/CFuncTrackChange.h"
#include "source2toolkit/schema/entity/classes/CFuncTrackTrain.h"
#include "source2toolkit/schema/entity/classes/CFuncTrain.h"
#include "source2toolkit/schema/entity/classes/CFuncTrainControls.h"
#include "source2toolkit/schema/entity/classes/CFuncVPhysicsClip.h"
#include "source2toolkit/schema/entity/classes/CFuncVehicleClip.h"
#include "source2toolkit/schema/entity/classes/CFuncWall.h"
#include "source2toolkit/schema/entity/classes/CFuncWallToggle.h"
#include "source2toolkit/schema/entity/classes/CFuncWater.h"
#include "source2toolkit/schema/entity/classes/CGameChoreoServices.h"
#include "source2toolkit/schema/entity/classes/CGameEnd.h"
#include "source2toolkit/schema/entity/classes/CGameGibManager.h"
#include "source2toolkit/schema/entity/classes/CGameMoney.h"
#include "source2toolkit/schema/entity/classes/CGamePlayerEquip.h"
#include "source2toolkit/schema/entity/classes/CGamePlayerZone.h"
#include "source2toolkit/schema/entity/classes/CGameRules.h"
#include "source2toolkit/schema/entity/classes/CGameRulesProxy.h"
#include "source2toolkit/schema/entity/classes/CGameSceneNode.h"
#include "source2toolkit/schema/entity/classes/CGameText.h"
#include "source2toolkit/schema/entity/classes/CGenericConstraint.h"
#include "source2toolkit/schema/entity/classes/CGlowProperty.h"
#include "source2toolkit/schema/entity/classes/CGradientFog.h"
#include "source2toolkit/schema/entity/classes/CGunTarget.h"
#include "source2toolkit/schema/entity/classes/CHEGrenade.h"
#include "source2toolkit/schema/entity/classes/CHEGrenadeProjectile.h"
#include "source2toolkit/schema/entity/classes/CHandleDummy.h"
#include "source2toolkit/schema/entity/classes/CHandleTest.h"
#include "source2toolkit/schema/entity/classes/CHitboxComponent.h"
#include "source2toolkit/schema/entity/classes/CHostage.h"
#include "source2toolkit/schema/entity/classes/CHostageAlias_info_hostage_spawn.h"
#include "source2toolkit/schema/entity/classes/CHostageCarriableProp.h"
#include "source2toolkit/schema/entity/classes/CHostageExpresserShim.h"
#include "source2toolkit/schema/entity/classes/CHostageRescueZone.h"
#include "source2toolkit/schema/entity/classes/CHostageRescueZoneShim.h"
#include "source2toolkit/schema/entity/classes/CInButtonState.h"
#include "source2toolkit/schema/entity/classes/CIncendiaryGrenade.h"
#include "source2toolkit/schema/entity/classes/CInferno.h"
#include "source2toolkit/schema/entity/classes/CInfoChoreoAnchor.h"
#include "source2toolkit/schema/entity/classes/CInfoChoreoAnchorPosition.h"
#include "source2toolkit/schema/entity/classes/CInfoData.h"
#include "source2toolkit/schema/entity/classes/CInfoDeathmatchSpawn.h"
#include "source2toolkit/schema/entity/classes/CInfoDynamicShadowHint.h"
#include "source2toolkit/schema/entity/classes/CInfoDynamicShadowHintBox.h"
#include "source2toolkit/schema/entity/classes/CInfoFan.h"
#include "source2toolkit/schema/entity/classes/CInfoGameEventProxy.h"
#include "source2toolkit/schema/entity/classes/CInfoInstructorHintBombTargetA.h"
#include "source2toolkit/schema/entity/classes/CInfoInstructorHintBombTargetB.h"
#include "source2toolkit/schema/entity/classes/CInfoInstructorHintHostageRescueZone.h"
#include "source2toolkit/schema/entity/classes/CInfoInstructorHintTarget.h"
#include "source2toolkit/schema/entity/classes/CInfoInteraction.h"
#include "source2toolkit/schema/entity/classes/CInfoLadderDismount.h"
#include "source2toolkit/schema/entity/classes/CInfoLandmark.h"
#include "source2toolkit/schema/entity/classes/CInfoOffscreenPanoramaTexture.h"
#include "source2toolkit/schema/entity/classes/CInfoParticleTarget.h"
#include "source2toolkit/schema/entity/classes/CInfoPlayerCounterterrorist.h"
#include "source2toolkit/schema/entity/classes/CInfoPlayerStart.h"
#include "source2toolkit/schema/entity/classes/CInfoPlayerTerrorist.h"
#include "source2toolkit/schema/entity/classes/CInfoSpawnGroupLandmark.h"
#include "source2toolkit/schema/entity/classes/CInfoSpawnGroupLoadUnload.h"
#include "source2toolkit/schema/entity/classes/CInfoTarget.h"
#include "source2toolkit/schema/entity/classes/CInfoTargetServerOnly.h"
#include "source2toolkit/schema/entity/classes/CInfoTeleportDestination.h"
#include "source2toolkit/schema/entity/classes/CInfoVisibilityBox.h"
#include "source2toolkit/schema/entity/classes/CInfoWorldLayer.h"
#include "source2toolkit/schema/entity/classes/CInstancedSceneEntity.h"
#include "source2toolkit/schema/entity/classes/CInstructorEventEntity.h"
#include "source2toolkit/schema/entity/classes/CIronSightController.h"
#include "source2toolkit/schema/entity/classes/CItem.h"
#include "source2toolkit/schema/entity/classes/CItemAssaultSuit.h"
#include "source2toolkit/schema/entity/classes/CItemDefuser.h"
#include "source2toolkit/schema/entity/classes/CItemDefuserAlias_item_defuser.h"
#include "source2toolkit/schema/entity/classes/CItemDogtags.h"
#include "source2toolkit/schema/entity/classes/CItemGeneric.h"
#include "source2toolkit/schema/entity/classes/CItemGenericTriggerHelper.h"
#include "source2toolkit/schema/entity/classes/CItemKevlar.h"
#include "source2toolkit/schema/entity/classes/CItemSoda.h"
#include "source2toolkit/schema/entity/classes/CItem_Healthshot.h"
#include "source2toolkit/schema/entity/classes/CKeepUpright.h"
#include "source2toolkit/schema/entity/classes/CKnife.h"
#include "source2toolkit/schema/entity/classes/CLightComponent.h"
#include "source2toolkit/schema/entity/classes/CLightDirectionalEntity.h"
#include "source2toolkit/schema/entity/classes/CLightEntity.h"
#include "source2toolkit/schema/entity/classes/CLightEnvironmentEntity.h"
#include "source2toolkit/schema/entity/classes/CLightOrthoEntity.h"
#include "source2toolkit/schema/entity/classes/CLightSpotEntity.h"
#include "source2toolkit/schema/entity/classes/CLogicAchievement.h"
#include "source2toolkit/schema/entity/classes/CLogicActiveAutosave.h"
#include "source2toolkit/schema/entity/classes/CLogicAuto.h"
#include "source2toolkit/schema/entity/classes/CLogicAutosave.h"
#include "source2toolkit/schema/entity/classes/CLogicBranch.h"
#include "source2toolkit/schema/entity/classes/CLogicBranchList.h"
#include "source2toolkit/schema/entity/classes/CLogicCase.h"
#include "source2toolkit/schema/entity/classes/CLogicCollisionPair.h"
#include "source2toolkit/schema/entity/classes/CLogicCompare.h"
#include "source2toolkit/schema/entity/classes/CLogicDistanceAutosave.h"
#include "source2toolkit/schema/entity/classes/CLogicDistanceCheck.h"
#include "source2toolkit/schema/entity/classes/CLogicEventListener.h"
#include "source2toolkit/schema/entity/classes/CLogicGameEvent.h"
#include "source2toolkit/schema/entity/classes/CLogicGameEventListener.h"
#include "source2toolkit/schema/entity/classes/CLogicLineToEntity.h"
#include "source2toolkit/schema/entity/classes/CLogicMeasureMovement.h"
#include "source2toolkit/schema/entity/classes/CLogicNPCCounter.h"
#include "source2toolkit/schema/entity/classes/CLogicNPCCounterAABB.h"
#include "source2toolkit/schema/entity/classes/CLogicNPCCounterOBB.h"
#include "source2toolkit/schema/entity/classes/CLogicNavigation.h"
#include "source2toolkit/schema/entity/classes/CLogicPlayerProxy.h"
#include "source2toolkit/schema/entity/classes/CLogicProximity.h"
#include "source2toolkit/schema/entity/classes/CLogicRelay.h"
#include "source2toolkit/schema/entity/classes/CLogicScript.h"
#include "source2toolkit/schema/entity/classes/CLogicalEntity.h"
#include "source2toolkit/schema/entity/classes/CMapInfo.h"
#include "source2toolkit/schema/entity/classes/CMapSharedEnvironment.h"
#include "source2toolkit/schema/entity/classes/CMapVetoPickController.h"
#include "source2toolkit/schema/entity/classes/CMarkupVolume.h"
#include "source2toolkit/schema/entity/classes/CMarkupVolumeTagged.h"
#include "source2toolkit/schema/entity/classes/CMarkupVolumeTagged_Nav.h"
#include "source2toolkit/schema/entity/classes/CMarkupVolumeTagged_NavGame.h"
#include "source2toolkit/schema/entity/classes/CMarkupVolumeWithRef.h"
#include "source2toolkit/schema/entity/classes/CMathColorBlend.h"
#include "source2toolkit/schema/entity/classes/CMathCounter.h"
#include "source2toolkit/schema/entity/classes/CMathRemap.h"
#include "source2toolkit/schema/entity/classes/CMessage.h"
#include "source2toolkit/schema/entity/classes/CMessageEntity.h"
#include "source2toolkit/schema/entity/classes/CModelPointEntity.h"
#include "source2toolkit/schema/entity/classes/CModelState.h"
#include "source2toolkit/schema/entity/classes/CMolotovGrenade.h"
#include "source2toolkit/schema/entity/classes/CMolotovProjectile.h"
#include "source2toolkit/schema/entity/classes/CMomentaryRotButton.h"
#include "source2toolkit/schema/entity/classes/CMoodVData.h"
#include "source2toolkit/schema/entity/classes/CMotorController.h"
#include "source2toolkit/schema/entity/classes/CMovementStatsProperty.h"
#include "source2toolkit/schema/entity/classes/CMoverPathNode.h"
#include "source2toolkit/schema/entity/classes/CMultiLightProxy.h"
#include "source2toolkit/schema/entity/classes/CMultiSource.h"
#include "source2toolkit/schema/entity/classes/CMultiplayRules.h"
#include "source2toolkit/schema/entity/classes/CMultiplayer_Expresser.h"
#include "source2toolkit/schema/entity/classes/CNavHullPresetVData.h"
#include "source2toolkit/schema/entity/classes/CNavHullVData.h"
#include "source2toolkit/schema/entity/classes/CNavSpaceInfo.h"
#include "source2toolkit/schema/entity/classes/CNavWalkable.h"
#include "source2toolkit/schema/entity/classes/CNetworkOriginCellCoordQuantizedVector.h"
#include "source2toolkit/schema/entity/classes/CNetworkTransmitComponent.h"
#include "source2toolkit/schema/entity/classes/CNetworkVelocityVector.h"
#include "source2toolkit/schema/entity/classes/CNetworkViewOffsetVector.h"
#include "source2toolkit/schema/entity/classes/CNmGraphInstance.h"
#include "source2toolkit/schema/entity/classes/CNmTarget.h"
#include "source2toolkit/schema/entity/classes/CNullEntity.h"
#include "source2toolkit/schema/entity/classes/COmniLight.h"
#include "source2toolkit/schema/entity/classes/COrnamentProp.h"
#include "source2toolkit/schema/entity/classes/CParticleSystem.h"
#include "source2toolkit/schema/entity/classes/CPathCorner.h"
#include "source2toolkit/schema/entity/classes/CPathCornerCrash.h"
#include "source2toolkit/schema/entity/classes/CPathKeyFrame.h"
#include "source2toolkit/schema/entity/classes/CPathMover.h"
#include "source2toolkit/schema/entity/classes/CPathMoverEntitySpawner.h"
#include "source2toolkit/schema/entity/classes/CPathNode.h"
#include "source2toolkit/schema/entity/classes/CPathParticleRope.h"
#include "source2toolkit/schema/entity/classes/CPathParticleRopeAlias_path_particle_rope_clientside.h"
#include "source2toolkit/schema/entity/classes/CPathQueryComponent.h"
#include "source2toolkit/schema/entity/classes/CPathSimple.h"
#include "source2toolkit/schema/entity/classes/CPathTrack.h"
#include "source2toolkit/schema/entity/classes/CPathWithDynamicNodes.h"
#include "source2toolkit/schema/entity/classes/CPhysBallSocket.h"
#include "source2toolkit/schema/entity/classes/CPhysBox.h"
#include "source2toolkit/schema/entity/classes/CPhysConstraint.h"
#include "source2toolkit/schema/entity/classes/CPhysExplosion.h"
#include "source2toolkit/schema/entity/classes/CPhysFixed.h"
#include "source2toolkit/schema/entity/classes/CPhysForce.h"
#include "source2toolkit/schema/entity/classes/CPhysHinge.h"
#include "source2toolkit/schema/entity/classes/CPhysHingeAlias_phys_hinge_local.h"
#include "source2toolkit/schema/entity/classes/CPhysImpact.h"
#include "source2toolkit/schema/entity/classes/CPhysLength.h"
#include "source2toolkit/schema/entity/classes/CPhysMagnet.h"
#include "source2toolkit/schema/entity/classes/CPhysMotor.h"
#include "source2toolkit/schema/entity/classes/CPhysPulley.h"
#include "source2toolkit/schema/entity/classes/CPhysSlideConstraint.h"
#include "source2toolkit/schema/entity/classes/CPhysThruster.h"
#include "source2toolkit/schema/entity/classes/CPhysTorque.h"
#include "source2toolkit/schema/entity/classes/CPhysWheelConstraint.h"
#include "source2toolkit/schema/entity/classes/CPhysicalButton.h"
#include "source2toolkit/schema/entity/classes/CPhysicsEntitySolver.h"
#include "source2toolkit/schema/entity/classes/CPhysicsProp.h"
#include "source2toolkit/schema/entity/classes/CPhysicsPropMultiplayer.h"
#include "source2toolkit/schema/entity/classes/CPhysicsPropOverride.h"
#include "source2toolkit/schema/entity/classes/CPhysicsPropRespawnable.h"
#include "source2toolkit/schema/entity/classes/CPhysicsShake.h"
#include "source2toolkit/schema/entity/classes/CPhysicsSpring.h"
#include "source2toolkit/schema/entity/classes/CPhysicsWire.h"
#include "source2toolkit/schema/entity/classes/CPlantedC4.h"
#include "source2toolkit/schema/entity/classes/CPlatTrigger.h"
#include "source2toolkit/schema/entity/classes/CPlayerControllerComponent.h"
#include "source2toolkit/schema/entity/classes/CPlayerPawnComponent.h"
#include "source2toolkit/schema/entity/classes/CPlayerPing.h"
#include "source2toolkit/schema/entity/classes/CPlayerSprayDecal.h"
#include "source2toolkit/schema/entity/classes/CPlayerVisibility.h"
#include "source2toolkit/schema/entity/classes/CPlayer_AutoaimServices.h"
#include "source2toolkit/schema/entity/classes/CPlayer_CameraServices.h"
#include "source2toolkit/schema/entity/classes/CPlayer_FlashlightServices.h"
#include "source2toolkit/schema/entity/classes/CPlayer_ItemServices.h"
#include "source2toolkit/schema/entity/classes/CPlayer_MovementServices.h"
#include "source2toolkit/schema/entity/classes/CPlayer_MovementServices_Humanoid.h"
#include "source2toolkit/schema/entity/classes/CPlayer_ObserverServices.h"
#include "source2toolkit/schema/entity/classes/CPlayer_UseServices.h"
#include "source2toolkit/schema/entity/classes/CPlayer_WaterServices.h"
#include "source2toolkit/schema/entity/classes/CPlayer_WeaponServices.h"
#include "source2toolkit/schema/entity/classes/CPointAngleSensor.h"
#include "source2toolkit/schema/entity/classes/CPointAngularVelocitySensor.h"
#include "source2toolkit/schema/entity/classes/CPointBroadcastClientCommand.h"
#include "source2toolkit/schema/entity/classes/CPointCamera.h"
#include "source2toolkit/schema/entity/classes/CPointCameraVFOV.h"
#include "source2toolkit/schema/entity/classes/CPointChildModifier.h"
#include "source2toolkit/schema/entity/classes/CPointClientCommand.h"
#include "source2toolkit/schema/entity/classes/CPointClientUIDialog.h"
#include "source2toolkit/schema/entity/classes/CPointClientUIWorldPanel.h"
#include "source2toolkit/schema/entity/classes/CPointClientUIWorldTextPanel.h"
#include "source2toolkit/schema/entity/classes/CPointCommentaryNode.h"
#include "source2toolkit/schema/entity/classes/CPointEntity.h"
#include "source2toolkit/schema/entity/classes/CPointEntityFinder.h"
#include "source2toolkit/schema/entity/classes/CPointGamestatsCounter.h"
#include "source2toolkit/schema/entity/classes/CPointGiveAmmo.h"
#include "source2toolkit/schema/entity/classes/CPointHurt.h"
#include "source2toolkit/schema/entity/classes/CPointOrient.h"
#include "source2toolkit/schema/entity/classes/CPointPrefab.h"
#include "source2toolkit/schema/entity/classes/CPointProximitySensor.h"
#include "source2toolkit/schema/entity/classes/CPointPulse.h"
#include "source2toolkit/schema/entity/classes/CPointPush.h"
#include "source2toolkit/schema/entity/classes/CPointServerCommand.h"
#include "source2toolkit/schema/entity/classes/CPointTeleport.h"
#include "source2toolkit/schema/entity/classes/CPointTemplate.h"
#include "source2toolkit/schema/entity/classes/CPointValueRemapper.h"
#include "source2toolkit/schema/entity/classes/CPointVelocitySensor.h"
#include "source2toolkit/schema/entity/classes/CPointWorldText.h"
#include "source2toolkit/schema/entity/classes/CPostProcessingVolume.h"
#include "source2toolkit/schema/entity/classes/CPrecipitation.h"
#include "source2toolkit/schema/entity/classes/CPrecipitationBlocker.h"
#include "source2toolkit/schema/entity/classes/CPrecipitationVData.h"
#include "source2toolkit/schema/entity/classes/CPropDataComponent.h"
#include "source2toolkit/schema/entity/classes/CPropDoorRotating.h"
#include "source2toolkit/schema/entity/classes/CPropDoorRotatingBreakable.h"
#include "source2toolkit/schema/entity/classes/CPulseGameBlackboard.h"
#include "source2toolkit/schema/entity/classes/CPulseGraphInstance_GameBlackboard.h"
#include "source2toolkit/schema/entity/classes/CPulseGraphInstance_ServerEntity.h"
#include "source2toolkit/schema/entity/classes/CPushable.h"
#include "source2toolkit/schema/entity/classes/CRagdollConstraint.h"
#include "source2toolkit/schema/entity/classes/CRagdollMagnet.h"
#include "source2toolkit/schema/entity/classes/CRagdollManager.h"
#include "source2toolkit/schema/entity/classes/CRagdollProp.h"
#include "source2toolkit/schema/entity/classes/CRagdollPropAlias_physics_prop_ragdoll.h"
#include "source2toolkit/schema/entity/classes/CRagdollPropAttached.h"
#include "source2toolkit/schema/entity/classes/CRangeFloat.h"
#include "source2toolkit/schema/entity/classes/CRectLight.h"
#include "source2toolkit/schema/entity/classes/CRenderComponent.h"
#include "source2toolkit/schema/entity/classes/CRetakeGameRules.h"
#include "source2toolkit/schema/entity/classes/CRevertSaved.h"
#include "source2toolkit/schema/entity/classes/CRopeKeyframe.h"
#include "source2toolkit/schema/entity/classes/CRopeKeyframeAlias_move_rope.h"
#include "source2toolkit/schema/entity/classes/CRotButton.h"
#include "source2toolkit/schema/entity/classes/CRotDoor.h"
#include "source2toolkit/schema/entity/classes/CRotatorTarget.h"
#include "source2toolkit/schema/entity/classes/CRuleBrushEntity.h"
#include "source2toolkit/schema/entity/classes/CRuleEntity.h"
#include "source2toolkit/schema/entity/classes/CRulePointEntity.h"
#include "source2toolkit/schema/entity/classes/CSMatchStats_t.h"
#include "source2toolkit/schema/entity/classes/CSPerRoundStats_t.h"
#include "source2toolkit/schema/entity/classes/CSceneEntity.h"
#include "source2toolkit/schema/entity/classes/CSceneEntityAlias_logic_choreographed_scene.h"
#include "source2toolkit/schema/entity/classes/CSceneListManager.h"
#include "source2toolkit/schema/entity/classes/CScenePayloadVData.h"
#include "source2toolkit/schema/entity/classes/CScriptItem.h"
#include "source2toolkit/schema/entity/classes/CScriptNavBlocker.h"
#include "source2toolkit/schema/entity/classes/CScriptTriggerHurt.h"
#include "source2toolkit/schema/entity/classes/CScriptTriggerMultiple.h"
#include "source2toolkit/schema/entity/classes/CScriptTriggerOnce.h"
#include "source2toolkit/schema/entity/classes/CScriptTriggerPush.h"
#include "source2toolkit/schema/entity/classes/CScriptedSequence.h"
#include "source2toolkit/schema/entity/classes/CServerOnlyEntity.h"
#include "source2toolkit/schema/entity/classes/CServerOnlyModelEntity.h"
#include "source2toolkit/schema/entity/classes/CServerOnlyPointEntity.h"
#include "source2toolkit/schema/entity/classes/CServerRagdollTrigger.h"
#include "source2toolkit/schema/entity/classes/CShatterGlassShardPhysics.h"
#include "source2toolkit/schema/entity/classes/CShower.h"
#include "source2toolkit/schema/entity/classes/CSimpleMarkupVolumeTagged.h"
#include "source2toolkit/schema/entity/classes/CSkeletonAnimationController.h"
#include "source2toolkit/schema/entity/classes/CSkeletonInstance.h"
#include "source2toolkit/schema/entity/classes/CSkillFloat.h"
#include "source2toolkit/schema/entity/classes/CSkillInt.h"
#include "source2toolkit/schema/entity/classes/CSkyCamera.h"
#include "source2toolkit/schema/entity/classes/CSkyboxReference.h"
#include "source2toolkit/schema/entity/classes/CSmokeGrenade.h"
#include "source2toolkit/schema/entity/classes/CSmokeGrenadeProjectile.h"
#include "source2toolkit/schema/entity/classes/CSoundAreaEntityBase.h"
#include "source2toolkit/schema/entity/classes/CSoundAreaEntityOrientedBox.h"
#include "source2toolkit/schema/entity/classes/CSoundAreaEntitySphere.h"
#include "source2toolkit/schema/entity/classes/CSoundEventAABBEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundEventConeEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundEventEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundEventEntityAlias_snd_event_point.h"
#include "source2toolkit/schema/entity/classes/CSoundEventOBBEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundEventParameter.h"
#include "source2toolkit/schema/entity/classes/CSoundEventPathCornerEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundEventSphereEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundOpvarSetAABBEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundOpvarSetAutoRoomEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundOpvarSetEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundOpvarSetOBBEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundOpvarSetOBBWindEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundOpvarSetPathCornerEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundOpvarSetPointBase.h"
#include "source2toolkit/schema/entity/classes/CSoundOpvarSetPointEntity.h"
#include "source2toolkit/schema/entity/classes/CSoundStackSave.h"
#include "source2toolkit/schema/entity/classes/CSplineConstraint.h"
#include "source2toolkit/schema/entity/classes/CSpotlightEnd.h"
#include "source2toolkit/schema/entity/classes/CSprite.h"
#include "source2toolkit/schema/entity/classes/CSpriteAlias_env_glow.h"
#include "source2toolkit/schema/entity/classes/CSpriteOriented.h"
#include "source2toolkit/schema/entity/classes/CTankTargetChange.h"
#include "source2toolkit/schema/entity/classes/CTankTrainAI.h"
#include "source2toolkit/schema/entity/classes/CTeam.h"
#include "source2toolkit/schema/entity/classes/CTeamplayRules.h"
#include "source2toolkit/schema/entity/classes/CTestEffect.h"
#include "source2toolkit/schema/entity/classes/CTestPulseIO.h"
#include "source2toolkit/schema/entity/classes/CTestPulseIOComponent.h"
#include "source2toolkit/schema/entity/classes/CTestPulseIOComponent_Derived.h"
#include "source2toolkit/schema/entity/classes/CTestPulseIO__EntityHandleIntArgs_t.h"
#include "source2toolkit/schema/entity/classes/CTestPulseIO__EntityNameStringArgs_t.h"
#include "source2toolkit/schema/entity/classes/CTestPulseIO__FloatStringArgs_t.h"
#include "source2toolkit/schema/entity/classes/CTestPulseIO__ThreeStringArgs_t.h"
#include "source2toolkit/schema/entity/classes/CTextureBasedAnimatable.h"
#include "source2toolkit/schema/entity/classes/CTimerEntity.h"
#include "source2toolkit/schema/entity/classes/CTonemapController2.h"
#include "source2toolkit/schema/entity/classes/CTonemapController2Alias_env_tonemap_controller2.h"
#include "source2toolkit/schema/entity/classes/CTonemapTrigger.h"
#include "source2toolkit/schema/entity/classes/CTouchExpansionComponent.h"
#include "source2toolkit/schema/entity/classes/CTriggerActiveWeaponDetect.h"
#include "source2toolkit/schema/entity/classes/CTriggerBombReset.h"
#include "source2toolkit/schema/entity/classes/CTriggerBrush.h"
#include "source2toolkit/schema/entity/classes/CTriggerBuoyancy.h"
#include "source2toolkit/schema/entity/classes/CTriggerCallback.h"
#include "source2toolkit/schema/entity/classes/CTriggerDetectBulletFire.h"
#include "source2toolkit/schema/entity/classes/CTriggerDetectExplosion.h"
#include "source2toolkit/schema/entity/classes/CTriggerFan.h"
#include "source2toolkit/schema/entity/classes/CTriggerGameEvent.h"
#include "source2toolkit/schema/entity/classes/CTriggerGravity.h"
#include "source2toolkit/schema/entity/classes/CTriggerHostageReset.h"
#include "source2toolkit/schema/entity/classes/CTriggerHurt.h"
#include "source2toolkit/schema/entity/classes/CTriggerImpact.h"
#include "source2toolkit/schema/entity/classes/CTriggerLerpObject.h"
#include "source2toolkit/schema/entity/classes/CTriggerLook.h"
#include "source2toolkit/schema/entity/classes/CTriggerMultiple.h"
#include "source2toolkit/schema/entity/classes/CTriggerOnce.h"
#include "source2toolkit/schema/entity/classes/CTriggerPhysics.h"
#include "source2toolkit/schema/entity/classes/CTriggerProximity.h"
#include "source2toolkit/schema/entity/classes/CTriggerPush.h"
#include "source2toolkit/schema/entity/classes/CTriggerRemove.h"
#include "source2toolkit/schema/entity/classes/CTriggerSave.h"
#include "source2toolkit/schema/entity/classes/CTriggerSndSosOpvar.h"
#include "source2toolkit/schema/entity/classes/CTriggerSoundscape.h"
#include "source2toolkit/schema/entity/classes/CTriggerTeleport.h"
#include "source2toolkit/schema/entity/classes/CTriggerToggleSave.h"
#include "source2toolkit/schema/entity/classes/CTriggerVolume.h"
#include "source2toolkit/schema/entity/classes/CVectorExponentialMovingAverage.h"
#include "source2toolkit/schema/entity/classes/CVoteController.h"
#include "source2toolkit/schema/entity/classes/CWaterBullet.h"
#include "source2toolkit/schema/entity/classes/CWeaponAWP.h"
#include "source2toolkit/schema/entity/classes/CWeaponAug.h"
#include "source2toolkit/schema/entity/classes/CWeaponBaseItem.h"
#include "source2toolkit/schema/entity/classes/CWeaponBizon.h"
#include "source2toolkit/schema/entity/classes/CWeaponCZ75a.h"
#include "source2toolkit/schema/entity/classes/CWeaponElite.h"
#include "source2toolkit/schema/entity/classes/CWeaponFamas.h"
#include "source2toolkit/schema/entity/classes/CWeaponFiveSeven.h"
#include "source2toolkit/schema/entity/classes/CWeaponG3SG1.h"
#include "source2toolkit/schema/entity/classes/CWeaponGalilAR.h"
#include "source2toolkit/schema/entity/classes/CWeaponGlock.h"
#include "source2toolkit/schema/entity/classes/CWeaponHKP2000.h"
#include "source2toolkit/schema/entity/classes/CWeaponM249.h"
#include "source2toolkit/schema/entity/classes/CWeaponM4A1.h"
#include "source2toolkit/schema/entity/classes/CWeaponM4A1Silencer.h"
#include "source2toolkit/schema/entity/classes/CWeaponMAC10.h"
#include "source2toolkit/schema/entity/classes/CWeaponMP5SD.h"
#include "source2toolkit/schema/entity/classes/CWeaponMP7.h"
#include "source2toolkit/schema/entity/classes/CWeaponMP9.h"
#include "source2toolkit/schema/entity/classes/CWeaponMag7.h"
#include "source2toolkit/schema/entity/classes/CWeaponNOVA.h"
#include "source2toolkit/schema/entity/classes/CWeaponNegev.h"
#include "source2toolkit/schema/entity/classes/CWeaponP250.h"
#include "source2toolkit/schema/entity/classes/CWeaponP90.h"
#include "source2toolkit/schema/entity/classes/CWeaponRevolver.h"
#include "source2toolkit/schema/entity/classes/CWeaponSCAR20.h"
#include "source2toolkit/schema/entity/classes/CWeaponSG556.h"
#include "source2toolkit/schema/entity/classes/CWeaponSSG08.h"
#include "source2toolkit/schema/entity/classes/CWeaponSawedoff.h"
#include "source2toolkit/schema/entity/classes/CWeaponTaser.h"
#include "source2toolkit/schema/entity/classes/CWeaponTec9.h"
#include "source2toolkit/schema/entity/classes/CWeaponUMP45.h"
#include "source2toolkit/schema/entity/classes/CWeaponUSPSilencer.h"
#include "source2toolkit/schema/entity/classes/CWeaponXM1014.h"
#include "source2toolkit/schema/entity/classes/CWorld.h"
#include "source2toolkit/schema/entity/classes/ConstraintSoundInfo.h"
#include "source2toolkit/schema/entity/classes/CountdownTimer.h"
#include "source2toolkit/schema/entity/classes/DecalGroupOption_t.h"
#include "source2toolkit/schema/entity/classes/DestructiblePartDamageRequest_t.h"
#include "source2toolkit/schema/entity/classes/DynamicVolumeDef_t.h"
#include "source2toolkit/schema/entity/classes/EntityRenderAttribute_t.h"
#include "source2toolkit/schema/entity/classes/EntitySpottedState_t.h"
#include "source2toolkit/schema/entity/classes/Extent.h"
#include "source2toolkit/schema/entity/classes/ExternalAnimGraphHandle_t.h"
#include "source2toolkit/schema/entity/classes/ExternalAnimGraph_t.h"
#include "source2toolkit/schema/entity/classes/FilterDamageType.h"
#include "source2toolkit/schema/entity/classes/FilterHealth.h"
#include "source2toolkit/schema/entity/classes/FuncMoverMovementSummary_t.h"
#include "source2toolkit/schema/entity/classes/IChoreoServices.h"
#include "source2toolkit/schema/entity/classes/IEconItemInterface.h"
#include "source2toolkit/schema/entity/classes/INavObstacle.h"
#include "source2toolkit/schema/entity/classes/IPhysAggregateInstance.h"
#include "source2toolkit/schema/entity/classes/IPhysicsBody.h"
#include "source2toolkit/schema/entity/classes/IPhysicsBodyList.h"
#include "source2toolkit/schema/entity/classes/IPhysicsJoint.h"
#include "source2toolkit/schema/entity/classes/IPhysicsMotionController.h"
#include "source2toolkit/schema/entity/classes/IPhysicsRagdollControl.h"
#include "source2toolkit/schema/entity/classes/ISkeletonAnimationController.h"
#include "source2toolkit/schema/entity/classes/InfoForResourceTypeCModel.h"
#include "source2toolkit/schema/entity/classes/InfoForResourceTypeCNmGraphDefinition.h"
#include "source2toolkit/schema/entity/classes/InfoForResourceTypeCPostProcessingResource.h"
#include "source2toolkit/schema/entity/classes/InfoForResourceTypeCTextureBase.h"
#include "source2toolkit/schema/entity/classes/InfoForResourceTypeCVDataItemDefs.h"
#include "source2toolkit/schema/entity/classes/InfoForResourceTypeCVDataResource.h"
#include "source2toolkit/schema/entity/classes/InfoForResourceTypeIMaterial2.h"
#include "source2toolkit/schema/entity/classes/InfoForResourceTypeIParticleSystemDefinition.h"
#include "source2toolkit/schema/entity/classes/IntervalTimer.h"
#include "source2toolkit/schema/entity/classes/ParticleIndex_t.h"
#include "source2toolkit/schema/entity/classes/PhysicsRagdollPose_t.h"
#include "source2toolkit/schema/entity/classes/RelationshipOverride_t.h"
#include "source2toolkit/schema/entity/classes/Relationship_t.h"
#include "source2toolkit/schema/entity/classes/ResourceId_t.h"
#include "source2toolkit/schema/entity/classes/ResponseContext_t.h"
#include "source2toolkit/schema/entity/classes/RotatorHistoryEntry_t.h"
#include "source2toolkit/schema/entity/classes/RotatorQueueEntry_t.h"
#include "source2toolkit/schema/entity/classes/SceneEventId_t.h"
#include "source2toolkit/schema/entity/classes/SceneOpportunityHandle_t.h"
#include "source2toolkit/schema/entity/classes/SceneRequestHandle_t.h"
#include "source2toolkit/schema/entity/classes/SellbackPurchaseEntry_t.h"
#include "source2toolkit/schema/entity/classes/ServerAuthoritativeWeaponSlot_t.h"
#include "source2toolkit/schema/entity/classes/SimpleConstraintSoundProfile.h"
#include "source2toolkit/schema/entity/classes/SoundOpvarTraceResult_t.h"
#include "source2toolkit/schema/entity/classes/SpawnPoint.h"
#include "source2toolkit/schema/entity/classes/VPhysicsCollisionAttribute_t.h"
#include "source2toolkit/schema/entity/classes/VelocitySampler.h"
#include "source2toolkit/schema/entity/classes/ViewAngleServerChange_t.h"
#include "source2toolkit/schema/entity/classes/WeaponPurchaseCount_t.h"
#include "source2toolkit/schema/entity/classes/WeaponPurchaseTracker_t.h"
#include "source2toolkit/schema/entity/classes/audioparams_t.h"
#include "source2toolkit/schema/entity/classes/constraint_axislimit_t.h"
#include "source2toolkit/schema/entity/classes/constraint_breakableparams_t.h"
#include "source2toolkit/schema/entity/classes/constraint_hingeparams_t.h"
#include "source2toolkit/schema/entity/classes/dynpitchvol_base_t.h"
#include "source2toolkit/schema/entity/classes/dynpitchvol_t.h"
#include "source2toolkit/schema/entity/classes/fogparams_t.h"
#include "source2toolkit/schema/entity/classes/fogplayerparams_t.h"
#include "source2toolkit/schema/entity/classes/hudtextparms_t.h"
#include "source2toolkit/schema/entity/classes/lerpdata_t.h"
#include "source2toolkit/schema/entity/classes/locksound_t.h"
#include "source2toolkit/schema/entity/classes/magnetted_objects_t.h"
#include "source2toolkit/schema/entity/classes/ragdoll_t.h"
#include "source2toolkit/schema/entity/classes/ragdollelement_t.h"
#include "source2toolkit/schema/entity/classes/ragdollhierarchyjoint_t.h"
#include "source2toolkit/schema/entity/classes/shard_model_desc_t.h"
#include "source2toolkit/schema/entity/classes/sky3dparams_t.h"
#include "source2toolkit/schema/entity/classes/sndopvarlatchdata_t.h"
#include "source2toolkit/schema/entity/classes/thinkfunc_t.h"

// --- schema entity enums ---
#include "source2toolkit/schema/entity/enums/AggregateInstanceStream_t.h"
#include "source2toolkit/schema/entity/enums/AimMatrixBlendMode.h"
#include "source2toolkit/schema/entity/enums/AmmoFlags_t.h"
#include "source2toolkit/schema/entity/enums/AmmoPosition_t.h"
#include "source2toolkit/schema/entity/enums/AnimGraphDebugDrawType_t.h"
#include "source2toolkit/schema/entity/enums/AnimLoopMode_t.h"
#include "source2toolkit/schema/entity/enums/AnimNodeNetworkMode.h"
#include "source2toolkit/schema/entity/enums/AnimParamButton_t.h"
#include "source2toolkit/schema/entity/enums/AnimParamNetworkSetting.h"
#include "source2toolkit/schema/entity/enums/AnimParamType_t.h"
#include "source2toolkit/schema/entity/enums/AnimParamVectorType_t.h"
#include "source2toolkit/schema/entity/enums/AnimScriptType.h"
#include "source2toolkit/schema/entity/enums/AnimValueSource.h"
#include "source2toolkit/schema/entity/enums/AnimVectorSource.h"
#include "source2toolkit/schema/entity/enums/AnimationAlgorithm_t.h"
#include "source2toolkit/schema/entity/enums/AnimationProcessingType_t.h"
#include "source2toolkit/schema/entity/enums/AnimationSnapshotType_t.h"
#include "source2toolkit/schema/entity/enums/AnimationType_t.h"
#include "source2toolkit/schema/entity/enums/BBoxVolumeType_t.h"
#include "source2toolkit/schema/entity/enums/BeamClipStyle_t.h"
#include "source2toolkit/schema/entity/enums/BeamType_t.h"
#include "source2toolkit/schema/entity/enums/BeginDeathLifeStateTransition_t.h"
#include "source2toolkit/schema/entity/enums/BinaryNodeChildOption.h"
#include "source2toolkit/schema/entity/enums/BinaryNodeTiming.h"
#include "source2toolkit/schema/entity/enums/Blend2DMode.h"
#include "source2toolkit/schema/entity/enums/BlendKeyType.h"
#include "source2toolkit/schema/entity/enums/BloodType.h"
#include "source2toolkit/schema/entity/enums/BloomBlendMode_t.h"
#include "source2toolkit/schema/entity/enums/BlurFilterType_t.h"
#include "source2toolkit/schema/entity/enums/BodySectionAuthority_t.h"
#include "source2toolkit/schema/entity/enums/BoneMaskBlendSpace.h"
#include "source2toolkit/schema/entity/enums/BoneTransformSpace_t.h"
#include "source2toolkit/schema/entity/enums/BreakableContentsType_t.h"
#include "source2toolkit/schema/entity/enums/BrushSolidities_e.h"
#include "source2toolkit/schema/entity/enums/C4LightEffect_t.h"
#include "source2toolkit/schema/entity/enums/CAnimationGraphVisualizerPrimitiveType.h"
#include "source2toolkit/schema/entity/enums/CCSPlayerAnimationState__AirAction_t.h"
#include "source2toolkit/schema/entity/enums/CCSPlayerAnimationState__Direction_t.h"
#include "source2toolkit/schema/entity/enums/CCSPlayerAnimationState__GroundMoveState_t.h"
#include "source2toolkit/schema/entity/enums/CCSPlayerAnimationState__MoveType_t.h"
#include "source2toolkit/schema/entity/enums/CDebugOverlayCombinedTypes_t.h"
#include "source2toolkit/schema/entity/enums/CDebugOverlayFilterTextType_t.h"
#include "source2toolkit/schema/entity/enums/CDebugOverlayFilterType_t.h"
#include "source2toolkit/schema/entity/enums/CFuncMover__FollowConstraint_t.h"
#include "source2toolkit/schema/entity/enums/CFuncMover__FollowEntityDirection_t.h"
#include "source2toolkit/schema/entity/enums/CFuncMover__Move_t.h"
#include "source2toolkit/schema/entity/enums/CFuncMover__OrientationUpdate_t.h"
#include "source2toolkit/schema/entity/enums/CFuncMover__TransitionToPathNodeAction_t.h"
#include "source2toolkit/schema/entity/enums/CFuncRotator__Rotate_t.h"
#include "source2toolkit/schema/entity/enums/CInfoChoreoLocatorShapeType_t.h"
#include "source2toolkit/schema/entity/enums/CLogicBranchList__LogicBranchListenerLastState_t.h"
#include "source2toolkit/schema/entity/enums/CNmCurrentSyncEventNode__InfoType_t.h"
#include "source2toolkit/schema/entity/enums/CNmEventRelevance_t.h"
#include "source2toolkit/schema/entity/enums/CNmEventTargetEntity_t.h"
#include "source2toolkit/schema/entity/enums/CNmFloatAngleMathNode__Operation_t.h"
#include "source2toolkit/schema/entity/enums/CNmFloatComparisonNode__Comparison_t.h"
#include "source2toolkit/schema/entity/enums/CNmFloatMathNode__Operator_t.h"
#include "source2toolkit/schema/entity/enums/CNmIDComparisonNode__Comparison_t.h"
#include "source2toolkit/schema/entity/enums/CNmParticleEvent__Type_t.h"
#include "source2toolkit/schema/entity/enums/CNmRootMotionData__SamplingMode_t.h"
#include "source2toolkit/schema/entity/enums/CNmRootMotionOverrideNode__OverrideFlags_t.h"
#include "source2toolkit/schema/entity/enums/CNmSoundEvent__Position_t.h"
#include "source2toolkit/schema/entity/enums/CNmStateNode__TimedEvent_t__Comparison_t.h"
#include "source2toolkit/schema/entity/enums/CNmSyncEventIndexConditionNode__TriggerMode_t.h"
#include "source2toolkit/schema/entity/enums/CNmTargetInfoNode__Info_t.h"
#include "source2toolkit/schema/entity/enums/CNmTargetWarpNode__TargetUpdateRule_t.h"
#include "source2toolkit/schema/entity/enums/CNmTimeConditionNode__ComparisonType_t.h"
#include "source2toolkit/schema/entity/enums/CNmTimeConditionNode__Operator_t.h"
#include "source2toolkit/schema/entity/enums/CNmTransitionNode__TransitionOptions_t.h"
#include "source2toolkit/schema/entity/enums/CNmVectorInfoNode__Info_t.h"
#include "source2toolkit/schema/entity/enums/CPhysicsProp__CrateType_t.h"
#include "source2toolkit/schema/entity/enums/CRR_Response__ResponseEnum_t.h"
#include "source2toolkit/schema/entity/enums/CSPlayerBlockingUseAction_t.h"
#include "source2toolkit/schema/entity/enums/CSPlayerState.h"
#include "source2toolkit/schema/entity/enums/CSWeaponCategory.h"
#include "source2toolkit/schema/entity/enums/CSWeaponMode.h"
#include "source2toolkit/schema/entity/enums/CSWeaponNameID.h"
#include "source2toolkit/schema/entity/enums/CSWeaponSilencerType.h"
#include "source2toolkit/schema/entity/enums/CSWeaponType.h"
#include "source2toolkit/schema/entity/enums/CVSoundFormat_t.h"
#include "source2toolkit/schema/entity/enums/CanPlaySequence_t.h"
#include "source2toolkit/schema/entity/enums/ChatIgnoreType_t.h"
#include "source2toolkit/schema/entity/enums/ChickenActivity.h"
#include "source2toolkit/schema/entity/enums/ChoiceBlendMethod.h"
#include "source2toolkit/schema/entity/enums/ChoiceChangeMethod.h"
#include "source2toolkit/schema/entity/enums/ChoiceMethod.h"
#include "source2toolkit/schema/entity/enums/ChoreoExternalAnimgraphControlState_t.h"
#include "source2toolkit/schema/entity/enums/ChoreoLookAtMode_t.h"
#include "source2toolkit/schema/entity/enums/ChoreoLookAtSpeed_t.h"
#include "source2toolkit/schema/entity/enums/Class_T.h"
#include "source2toolkit/schema/entity/enums/ClosestPointTestType_t.h"
#include "source2toolkit/schema/entity/enums/DamageTypes_t.h"
#include "source2toolkit/schema/entity/enums/DampingSpeedFunction.h"
#include "source2toolkit/schema/entity/enums/DebugOverlayBits_t.h"
#include "source2toolkit/schema/entity/enums/DecalFlags_t.h"
#include "source2toolkit/schema/entity/enums/DecalRtEncoding_t.h"
#include "source2toolkit/schema/entity/enums/DestructiblePartDestructionDeathBehavior_t.h"
#include "source2toolkit/schema/entity/enums/Detail2Combo_t.h"
#include "source2toolkit/schema/entity/enums/DetailCombo_t.h"
#include "source2toolkit/schema/entity/enums/DisableShadows_t.h"
#include "source2toolkit/schema/entity/enums/Disposition_t.h"
#include "source2toolkit/schema/entity/enums/DoorState_t.h"
#include "source2toolkit/schema/entity/enums/DynamicContinuousContactBehavior_t.h"
#include "source2toolkit/schema/entity/enums/EContributionScoreFlag_t.h"
#include "source2toolkit/schema/entity/enums/EDemoBoneSelectionMode.h"
#include "source2toolkit/schema/entity/enums/EDestructiblePartDamagePassThroughType.h"
#include "source2toolkit/schema/entity/enums/EDestructiblePartRadiusDamageApplyType.h"
#include "source2toolkit/schema/entity/enums/EDestructibleParts_DestroyParameterFlags.h"
#include "source2toolkit/schema/entity/enums/EIKEndEffectorRotationFixUpMode.h"
#include "source2toolkit/schema/entity/enums/EInButtonState.h"
#include "source2toolkit/schema/entity/enums/EKillTypes_t.h"
#include "source2toolkit/schema/entity/enums/EMidiNote.h"
#include "source2toolkit/schema/entity/enums/EMode_t.h"
#include "source2toolkit/schema/entity/enums/ENPCBehaviorOverride_t.h"
#include "source2toolkit/schema/entity/enums/EOverrideBlockLOS_t.h"
#include "source2toolkit/schema/entity/enums/EProceduralRagdollWeightIndexPropagationMethod.h"
#include "source2toolkit/schema/entity/enums/EPulseGraphExecutionHistoryFlag.h"
#include "source2toolkit/schema/entity/enums/ESceneObjectVisualization.h"
#include "source2toolkit/schema/entity/enums/ESceneRequestState_t.h"
#include "source2toolkit/schema/entity/enums/ESceneViewDebugOverlaysListenerDataType_t.h"
#include "source2toolkit/schema/entity/enums/ESilhouetteType_t.h"
#include "source2toolkit/schema/entity/enums/EWaveform.h"
#include "source2toolkit/schema/entity/enums/EntFinderMethod_t.h"
#include "source2toolkit/schema/entity/enums/EntityAttachmentType_t.h"
#include "source2toolkit/schema/entity/enums/EntityDisolveType_t.h"
#include "source2toolkit/schema/entity/enums/EntityDistanceMode_t.h"
#include "source2toolkit/schema/entity/enums/EntityPlatformTypes_t.h"
#include "source2toolkit/schema/entity/enums/EntitySubclassScope_t.h"
#include "source2toolkit/schema/entity/enums/EventTypeSelection_t.h"
#include "source2toolkit/schema/entity/enums/Explosions.h"
#include "source2toolkit/schema/entity/enums/ExternalAnimGraphInactiveBehavior_t.h"
#include "source2toolkit/schema/entity/enums/FacingMode.h"
#include "source2toolkit/schema/entity/enums/FieldNetworkOption.h"
#include "source2toolkit/schema/entity/enums/FixAngleSet_t.h"
#include "source2toolkit/schema/entity/enums/FlexOpCode_t.h"
#include "source2toolkit/schema/entity/enums/FootFallTagFoot_t.h"
#include "source2toolkit/schema/entity/enums/FootLockSubVisualization.h"
#include "source2toolkit/schema/entity/enums/FootPinningTimingSource.h"
#include "source2toolkit/schema/entity/enums/FootstepJumpPhase_t.h"
#include "source2toolkit/schema/entity/enums/FootstepLandedFootSoundType_t.h"
#include "source2toolkit/schema/entity/enums/ForcedCrouchState_t.h"
#include "source2toolkit/schema/entity/enums/FuncDoorSpawnPos_t.h"
#include "source2toolkit/schema/entity/enums/FuncMoverMovementSummaryFlags_t.h"
#include "source2toolkit/schema/entity/enums/FuseVariableAccess_t.h"
#include "source2toolkit/schema/entity/enums/FuseVariableType_t.h"
#include "source2toolkit/schema/entity/enums/GLOBALESTATE.h"
#include "source2toolkit/schema/entity/enums/GPUParticleCollisionMode_t.h"
#include "source2toolkit/schema/entity/enums/GameAnimEventIndex_t.h"
#include "source2toolkit/schema/entity/enums/GrenadeType_t.h"
#include "source2toolkit/schema/entity/enums/HandshakeTagState_t.h"
#include "source2toolkit/schema/entity/enums/HandshakeTagType_t.h"
#include "source2toolkit/schema/entity/enums/HierarchyType_t.h"
#include "source2toolkit/schema/entity/enums/HitboxLerpType_t.h"
#include "source2toolkit/schema/entity/enums/HorizJustification_e.h"
#include "source2toolkit/schema/entity/enums/HoverPoseFlags_t.h"
#include "source2toolkit/schema/entity/enums/Hull_t.h"
#include "source2toolkit/schema/entity/enums/IChoreoServices__ChoreoState_t.h"
#include "source2toolkit/schema/entity/enums/IChoreoServices__ScriptState_t.h"
#include "source2toolkit/schema/entity/enums/IKChannelMode.h"
#include "source2toolkit/schema/entity/enums/IKSolverType.h"
#include "source2toolkit/schema/entity/enums/IKTargetCoordinateSystem.h"
#include "source2toolkit/schema/entity/enums/IKTargetSource.h"
#include "source2toolkit/schema/entity/enums/INavObstacle__NavObstacleType_t.h"
#include "source2toolkit/schema/entity/enums/IkEndEffectorType.h"
#include "source2toolkit/schema/entity/enums/IkTargetType.h"
#include "source2toolkit/schema/entity/enums/InheritableBoolType_t.h"
#include "source2toolkit/schema/entity/enums/InputBitMask_t.h"
#include "source2toolkit/schema/entity/enums/InputLayoutVariation_t.h"
#include "source2toolkit/schema/entity/enums/InteractionPassive_t.h"
#include "source2toolkit/schema/entity/enums/InteractionPriority_t.h"
#include "source2toolkit/schema/entity/enums/ItemFlagTypes_t.h"
#include "source2toolkit/schema/entity/enums/JiggleBoneSimSpace.h"
#include "source2toolkit/schema/entity/enums/JointAxis_t.h"
#include "source2toolkit/schema/entity/enums/JointMotion_t.h"
#include "source2toolkit/schema/entity/enums/JumpCorrectionMethod.h"
#include "source2toolkit/schema/entity/enums/LatchDirtyPermission_t.h"
#include "source2toolkit/schema/entity/enums/LayoutPositionType_e.h"
#include "source2toolkit/schema/entity/enums/LessonPanelLayoutFileTypes_t.h"
#include "source2toolkit/schema/entity/enums/LinearRootMotionBlendMode_t.h"
#include "source2toolkit/schema/entity/enums/MaterialProxyType_t.h"
#include "source2toolkit/schema/entity/enums/Materials.h"
#include "source2toolkit/schema/entity/enums/MatterialAttributeTagType_t.h"
#include "source2toolkit/schema/entity/enums/MedalRank_t.h"
#include "source2toolkit/schema/entity/enums/MeshDrawPrimitiveFlags_t.h"
#include "source2toolkit/schema/entity/enums/MissingParentInheritBehavior_t.h"
#include "source2toolkit/schema/entity/enums/ModelBoneFlexComponent_t.h"
#include "source2toolkit/schema/entity/enums/ModelConfigAttachmentType_t.h"
#include "source2toolkit/schema/entity/enums/ModelHitboxType_t.h"
#include "source2toolkit/schema/entity/enums/ModelMeshBufferUsage_t.h"
#include "source2toolkit/schema/entity/enums/ModelSkeletonData_t__BoneFlags_t.h"
#include "source2toolkit/schema/entity/enums/ModifyDamageReturn_t.h"
#include "source2toolkit/schema/entity/enums/MoodType_t.h"
#include "source2toolkit/schema/entity/enums/MorphBundleType_t.h"
#include "source2toolkit/schema/entity/enums/MorphFlexControllerRemapType_t.h"
#include "source2toolkit/schema/entity/enums/MoveLinearAuthoredPos_t.h"
#include "source2toolkit/schema/entity/enums/MoveMountingAmount_t.h"
#include "source2toolkit/schema/entity/enums/MovementCapability_t.h"
#include "source2toolkit/schema/entity/enums/NPCFollowFormation_t.h"
#include "source2toolkit/schema/entity/enums/NPCPhysicsHullType_t.h"
#include "source2toolkit/schema/entity/enums/NavAttributeEnum.h"
#include "source2toolkit/schema/entity/enums/NavDirType.h"
#include "source2toolkit/schema/entity/enums/NavScopeFlags_t.h"
#include "source2toolkit/schema/entity/enums/NavScope_t.h"
#include "source2toolkit/schema/entity/enums/NmCachedValueMode_t.h"
#include "source2toolkit/schema/entity/enums/NmEasingFunction_t.h"
#include "source2toolkit/schema/entity/enums/NmEasingOperation_t.h"
#include "source2toolkit/schema/entity/enums/NmEventConditionRules_t.h"
#include "source2toolkit/schema/entity/enums/NmFollowBoneMode_t.h"
#include "source2toolkit/schema/entity/enums/NmFootPhaseCondition_t.h"
#include "source2toolkit/schema/entity/enums/NmFootPhase_t.h"
#include "source2toolkit/schema/entity/enums/NmFrameSnapEventMode_t.h"
#include "source2toolkit/schema/entity/enums/NmGraphDebugMode_t.h"
#include "source2toolkit/schema/entity/enums/NmGraphEventTypeCondition_t.h"
#include "source2toolkit/schema/entity/enums/NmGraphValueType_t.h"
#include "source2toolkit/schema/entity/enums/NmIKBlendMode_t.h"
#include "source2toolkit/schema/entity/enums/NmPoseBlendMode_t.h"
#include "source2toolkit/schema/entity/enums/NmRootMotionBlendMode_t.h"
#include "source2toolkit/schema/entity/enums/NmTargetWarpAlgorithm_t.h"
#include "source2toolkit/schema/entity/enums/NmTargetWarpRule_t.h"
#include "source2toolkit/schema/entity/enums/NmTransitionRuleCondition_t.h"
#include "source2toolkit/schema/entity/enums/NmTransitionRule_t.h"
#include "source2toolkit/schema/entity/enums/ObjectTypeFlags_t.h"
#include "source2toolkit/schema/entity/enums/ObserverInterpState_t.h"
#include "source2toolkit/schema/entity/enums/ObserverMode_t.h"
#include "source2toolkit/schema/entity/enums/OnFrame.h"
#include "source2toolkit/schema/entity/enums/OrientationWarpMode_t.h"
#include "source2toolkit/schema/entity/enums/OrientationWarpRootMotionSource_t.h"
#include "source2toolkit/schema/entity/enums/OrientationWarpTargetOffsetMode_t.h"
#include "source2toolkit/schema/entity/enums/PFNoiseModifier_t.h"
#include "source2toolkit/schema/entity/enums/PFNoiseTurbulence_t.h"
#include "source2toolkit/schema/entity/enums/PFNoiseType_t.h"
#include "source2toolkit/schema/entity/enums/PFuncVisualizationType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleAlphaReferenceType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleAttachment_t.h"
#include "source2toolkit/schema/entity/enums/ParticleAttrBoxFlags_t.h"
#include "source2toolkit/schema/entity/enums/ParticleCollisionGroup_t.h"
#include "source2toolkit/schema/entity/enums/ParticleCollisionMask_t.h"
#include "source2toolkit/schema/entity/enums/ParticleCollisionMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticleColorBlendMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticleColorBlendType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleControlPointAxis_t.h"
#include "source2toolkit/schema/entity/enums/ParticleDepthFeatheringMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticleDetailLevel_t.h"
#include "source2toolkit/schema/entity/enums/ParticleDirectionNoiseType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleEndcapMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticleEntityPos_t.h"
#include "source2toolkit/schema/entity/enums/ParticleFalloffFunction_t.h"
#include "source2toolkit/schema/entity/enums/ParticleFanType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleFloatBiasType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleFloatInputMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticleFloatMapType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleFloatRandomMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticleFloatRoundType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleFloatType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleFogType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleHitboxBiasType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleHitboxDataSelection_t.h"
#include "source2toolkit/schema/entity/enums/ParticleImpulseType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleLightBehaviorChoiceList_t.h"
#include "source2toolkit/schema/entity/enums/ParticleLightFogLightingMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticleLightTypeChoiceList_t.h"
#include "source2toolkit/schema/entity/enums/ParticleLightUnitChoiceList_t.h"
#include "source2toolkit/schema/entity/enums/ParticleLightingQuality_t.h"
#include "source2toolkit/schema/entity/enums/ParticleLightnintBranchBehavior_t.h"
#include "source2toolkit/schema/entity/enums/ParticleLiquidContents_t.h"
#include "source2toolkit/schema/entity/enums/ParticleMassMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticleModelType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleMultiSegmentCountSelection_t.h"
#include "source2toolkit/schema/entity/enums/ParticleMultiSegmentInputSelection_t.h"
#include "source2toolkit/schema/entity/enums/ParticleMultiSegmentSpecialCharacter_t.h"
#include "source2toolkit/schema/entity/enums/ParticleOmni2LightTypeChoiceList_t.h"
#include "source2toolkit/schema/entity/enums/ParticleOrientationChoiceList_t.h"
#include "source2toolkit/schema/entity/enums/ParticleOrientationSetMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticleOrientationType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleOutputBlendMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticleParentSetMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticlePinDistance_t.h"
#include "source2toolkit/schema/entity/enums/ParticlePostProcessPriorityGroup_t.h"
#include "source2toolkit/schema/entity/enums/ParticleReplicationMode_t.h"
#include "source2toolkit/schema/entity/enums/ParticleRotationLockType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleSelection_t.h"
#include "source2toolkit/schema/entity/enums/ParticleSequenceCropOverride_t.h"
#include "source2toolkit/schema/entity/enums/ParticleSetMethod_t.h"
#include "source2toolkit/schema/entity/enums/ParticleSortingChoiceList_t.h"
#include "source2toolkit/schema/entity/enums/ParticleTextureLayerBlendType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleToolsState_t.h"
#include "source2toolkit/schema/entity/enums/ParticleTopology_t.h"
#include "source2toolkit/schema/entity/enums/ParticleTraceMissBehavior_t.h"
#include "source2toolkit/schema/entity/enums/ParticleTraceSet_t.h"
#include "source2toolkit/schema/entity/enums/ParticleTransformType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleVRHandChoiceList_t.h"
#include "source2toolkit/schema/entity/enums/ParticleVecType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleVolumetricSmokeCreationType_t.h"
#include "source2toolkit/schema/entity/enums/ParticleVolumetricSmokeType_t.h"
#include "source2toolkit/schema/entity/enums/PerformanceMode_t.h"
#include "source2toolkit/schema/entity/enums/PermModelInfo_t__FlagEnum.h"
#include "source2toolkit/schema/entity/enums/PetGroundType_t.h"
#include "source2toolkit/schema/entity/enums/PhysGenericShapeType_t.h"
#include "source2toolkit/schema/entity/enums/PhysInterfaceId_t.h"
#include "source2toolkit/schema/entity/enums/PlayBackMode_t.h"
#include "source2toolkit/schema/entity/enums/PlayerConnectedState.h"
#include "source2toolkit/schema/entity/enums/PointOrientConstraint_t.h"
#include "source2toolkit/schema/entity/enums/PointOrientGoalDirectionType_t.h"
#include "source2toolkit/schema/entity/enums/PointTemplateClientOnlyEntityBehavior_t.h"
#include "source2toolkit/schema/entity/enums/PointTemplateOwnerSpawnGroupType_t.h"
#include "source2toolkit/schema/entity/enums/PointWorldTextJustifyHorizontal_t.h"
#include "source2toolkit/schema/entity/enums/PointWorldTextJustifyVertical_t.h"
#include "source2toolkit/schema/entity/enums/PointWorldTextReorientMode_t.h"
#include "source2toolkit/schema/entity/enums/PoseType_t.h"
#include "source2toolkit/schema/entity/enums/PreviewCharacterBannerAnimation.h"
#include "source2toolkit/schema/entity/enums/PreviewCharacterMode.h"
#include "source2toolkit/schema/entity/enums/PreviewEOMCelebration.h"
#include "source2toolkit/schema/entity/enums/PreviewWeaponState.h"
#include "source2toolkit/schema/entity/enums/PropDoorRotatingOpenDirection_e.h"
#include "source2toolkit/schema/entity/enums/PropDoorRotatingSpawnPos_t.h"
#include "source2toolkit/schema/entity/enums/PulseApiFeature_t.h"
#include "source2toolkit/schema/entity/enums/PulseBestOutflowRules_t.h"
#include "source2toolkit/schema/entity/enums/PulseCollisionGroup_t.h"
#include "source2toolkit/schema/entity/enums/PulseCursorCancelPriority_t.h"
#include "source2toolkit/schema/entity/enums/PulseCursorExecResult_t.h"
#include "source2toolkit/schema/entity/enums/PulseDomainValueType_t.h"
#include "source2toolkit/schema/entity/enums/PulseInstructionCode_t.h"
#include "source2toolkit/schema/entity/enums/PulseMethodCallMode_t.h"
#include "source2toolkit/schema/entity/enums/PulseNPCCondition_t.h"
#include "source2toolkit/schema/entity/enums/PulseTestEnumColor_t.h"
#include "source2toolkit/schema/entity/enums/PulseTestEnumShape_t.h"
#include "source2toolkit/schema/entity/enums/PulseTraceContents_t.h"
#include "source2toolkit/schema/entity/enums/PulseValueType_t.h"
#include "source2toolkit/schema/entity/enums/PulseVariableKeysSource_t.h"
#include "source2toolkit/schema/entity/enums/QuestProgress__Reason.h"
#include "source2toolkit/schema/entity/enums/RTProxyInstanceFlags_t.h"
#include "source2toolkit/schema/entity/enums/RagdollPoseControl.h"
#include "source2toolkit/schema/entity/enums/RelativeLocationType_t.h"
#include "source2toolkit/schema/entity/enums/RenderBufferFlags_t.h"
#include "source2toolkit/schema/entity/enums/RenderMeshSlotType_t.h"
#include "source2toolkit/schema/entity/enums/RenderModelSubModelFieldType_t.h"
#include "source2toolkit/schema/entity/enums/RenderPrimitiveType_t.h"
#include "source2toolkit/schema/entity/enums/RenderSlotType_t.h"
#include "source2toolkit/schema/entity/enums/ResetCycleOption.h"
#include "source2toolkit/schema/entity/enums/RotatorTargetSpace_t.h"
#include "source2toolkit/schema/entity/enums/RsComparison_t.h"
#include "source2toolkit/schema/entity/enums/RsCullMode_t.h"
#include "source2toolkit/schema/entity/enums/RsFillMode_t.h"
#include "source2toolkit/schema/entity/enums/RumbleEffect_t.h"
#include "source2toolkit/schema/entity/enums/SaveRestoreTableFlags_t.h"
#include "source2toolkit/schema/entity/enums/ScalarExpressionType_t.h"
#include "source2toolkit/schema/entity/enums/SceneOnPlayerDeath_t.h"
#include "source2toolkit/schema/entity/enums/ScriptedConflictResponse_t.h"
#include "source2toolkit/schema/entity/enums/ScriptedHeldWeaponBehavior_t.h"
#include "source2toolkit/schema/entity/enums/ScriptedMoveTo_t.h"
#include "source2toolkit/schema/entity/enums/ScriptedOnDeath_t.h"
#include "source2toolkit/schema/entity/enums/SelectorTagBehavior_t.h"
#include "source2toolkit/schema/entity/enums/SeqCmd_t.h"
#include "source2toolkit/schema/entity/enums/SeqPoseSetting_t.h"
#include "source2toolkit/schema/entity/enums/SequenceFinishNotifyState_t.h"
#include "source2toolkit/schema/entity/enums/SetStatisticExpressionType_t.h"
#include "source2toolkit/schema/entity/enums/ShadowType_t.h"
#include "source2toolkit/schema/entity/enums/ShakeCommand_t.h"
#include "source2toolkit/schema/entity/enums/ShardSolid_t.h"
#include "source2toolkit/schema/entity/enums/SharedMovementGait_t.h"
#include "source2toolkit/schema/entity/enums/ShatterDamageCause.h"
#include "source2toolkit/schema/entity/enums/ShatterGlassStressType.h"
#include "source2toolkit/schema/entity/enums/SnapshotIndexType_t.h"
#include "source2toolkit/schema/entity/enums/SndSeqInstrumentType_t.h"
#include "source2toolkit/schema/entity/enums/SndSeqMidiStatusType_t.h"
#include "source2toolkit/schema/entity/enums/SndSeqPlayerType_t.h"
#include "source2toolkit/schema/entity/enums/SndSeqQuantizeType_t.h"
#include "source2toolkit/schema/entity/enums/SndSeqRegionType_t.h"
#include "source2toolkit/schema/entity/enums/SndSeqSyncType_t.h"
#include "source2toolkit/schema/entity/enums/SndSeqTrackPlaybackType_t.h"
#include "source2toolkit/schema/entity/enums/SolveIKChainAnimNodeDebugSetting.h"
#include "source2toolkit/schema/entity/enums/SosActionLimitSortType_t.h"
#include "source2toolkit/schema/entity/enums/SosActionSetParamSortType_t.h"
#include "source2toolkit/schema/entity/enums/SosActionStopType_t.h"
#include "source2toolkit/schema/entity/enums/SosEditItemType_t.h"
#include "source2toolkit/schema/entity/enums/SosGroupFieldBehavior_t.h"
#include "source2toolkit/schema/entity/enums/SosGroupType_t.h"
#include "source2toolkit/schema/entity/enums/SoundEventStartType_t.h"
#include "source2toolkit/schema/entity/enums/SpriteCardPerParticleScale_t.h"
#include "source2toolkit/schema/entity/enums/SpriteCardShaderType_t.h"
#include "source2toolkit/schema/entity/enums/SpriteCardTextureChannel_t.h"
#include "source2toolkit/schema/entity/enums/SpriteCardTextureType_t.h"
#include "source2toolkit/schema/entity/enums/StanceOverrideMode.h"
#include "source2toolkit/schema/entity/enums/StanceType_t.h"
#include "source2toolkit/schema/entity/enums/StandardLightingAttenuationStyle_t.h"
#include "source2toolkit/schema/entity/enums/StateActionBehavior.h"
#include "source2toolkit/schema/entity/enums/StepPhase.h"
#include "source2toolkit/schema/entity/enums/SubclassVDataChangeType_t.h"
#include "source2toolkit/schema/entity/enums/SurroundingBoundsType_t.h"
#include "source2toolkit/schema/entity/enums/TOGGLE_STATE.h"
#include "source2toolkit/schema/entity/enums/TRAIN_CODE.h"
#include "source2toolkit/schema/entity/enums/TakeDamageFlags_t.h"
#include "source2toolkit/schema/entity/enums/TargetSelectorAngleMode_t.h"
#include "source2toolkit/schema/entity/enums/TargetWarpAngleMode_t.h"
#include "source2toolkit/schema/entity/enums/TargetWarpCorrectionMethod.h"
#include "source2toolkit/schema/entity/enums/TargetWarpTimingMethod.h"
#include "source2toolkit/schema/entity/enums/TestInputOutputCombinationsEnum_t.h"
#include "source2toolkit/schema/entity/enums/TextureRepetitionMode_t.h"
#include "source2toolkit/schema/entity/enums/TimelineCompression_t.h"
#include "source2toolkit/schema/entity/enums/Touch_t.h"
#include "source2toolkit/schema/entity/enums/TrackOrientationType_t.h"
#include "source2toolkit/schema/entity/enums/TrainOrientationType_t.h"
#include "source2toolkit/schema/entity/enums/TrainVelocityType_t.h"
#include "source2toolkit/schema/entity/enums/VMixChannelOperation_t.h"
#include "source2toolkit/schema/entity/enums/VMixFilterSlope_t.h"
#include "source2toolkit/schema/entity/enums/VMixFilterType_t.h"
#include "source2toolkit/schema/entity/enums/VMixGraphCommandID_t.h"
#include "source2toolkit/schema/entity/enums/VMixLFOShape_t.h"
#include "source2toolkit/schema/entity/enums/VMixPannerType_t.h"
#include "source2toolkit/schema/entity/enums/VMixSubgraphSwitchInterpolationType_t.h"
#include "source2toolkit/schema/entity/enums/VPhysXAggregateData_t__VPhysXFlagEnum_t.h"
#include "source2toolkit/schema/entity/enums/VPhysXBodyPart_t__VPhysXFlagEnum_t.h"
#include "source2toolkit/schema/entity/enums/VPhysXConstraintParams_t__EnumFlags0_t.h"
#include "source2toolkit/schema/entity/enums/VPhysXJoint_t__Flags_t.h"
#include "source2toolkit/schema/entity/enums/ValueRemapperHapticsType_t.h"
#include "source2toolkit/schema/entity/enums/ValueRemapperInputType_t.h"
#include "source2toolkit/schema/entity/enums/ValueRemapperMomentumType_t.h"
#include "source2toolkit/schema/entity/enums/ValueRemapperOutputType_t.h"
#include "source2toolkit/schema/entity/enums/ValueRemapperRatchetType_t.h"
#include "source2toolkit/schema/entity/enums/VectorExpressionType_t.h"
#include "source2toolkit/schema/entity/enums/VectorFloatExpressionType_t.h"
#include "source2toolkit/schema/entity/enums/VelocityMetricMode.h"
#include "source2toolkit/schema/entity/enums/VertJustification_e.h"
#include "source2toolkit/schema/entity/enums/VertexAlbedoFormat_t.h"
#include "source2toolkit/schema/entity/enums/ViewFadeMode_t.h"
#include "source2toolkit/schema/entity/enums/WaterLevel_t.h"
#include "source2toolkit/schema/entity/enums/WeaponAttackType_t.h"
#include "source2toolkit/schema/entity/enums/WeaponGameplayAnimState.h"
#include "source2toolkit/schema/entity/enums/WeaponSound_t.h"
#include "source2toolkit/schema/entity/enums/WeaponSwitchReason_t.h"
#include "source2toolkit/schema/entity/enums/WorldTextPanelHorizontalAlign_t.h"
#include "source2toolkit/schema/entity/enums/WorldTextPanelOrientation_t.h"
#include "source2toolkit/schema/entity/enums/WorldTextPanelVerticalAlign_t.h"
#include "source2toolkit/schema/entity/enums/attributeprovidertypes_t.h"
#include "source2toolkit/schema/entity/enums/doorCheck_e.h"
#include "source2toolkit/schema/entity/enums/eSplinePushType.h"
#include "source2toolkit/schema/entity/enums/filter_t.h"
#include "source2toolkit/schema/entity/enums/gear_slot_t.h"
#include "source2toolkit/schema/entity/enums/loadout_slot_t.h"
#include "source2toolkit/schema/entity/enums/navproperties_t.h"
#include "source2toolkit/schema/entity/enums/soundcommands_t.h"
#include "source2toolkit/schema/entity/enums/vote_create_failed_t.h"

#include "steam/steam_api.h"
#include "steam/steam_gameserver.h"
#include "steam/steam_api_common.h"

#include "isteamgamecoordinator.h"

#include "khook.hpp"
#include "eiface.h"
#include "igameeventsystem.h"
#include "iserver.h"
#include "schemasystem.h"
#include "interfaces/interfaces.h"
#include "networksystem/inetworkmessages.h"

#include <cstdio>

Plugin g_Plugin;
TOOLKIT_EXPOSE(source2toolkit_test, g_Plugin);

IToolkitModule* g_pLibSteamApi = nullptr;
IGameEventSystem* g_pGameEventSystem = nullptr;
CSteamGameServerAPIContext* g_pSteamAPI = nullptr;
ISteamGameCoordinator* g_pSteamGameCoordinator = nullptr;

// --- schema entity classes ---
AnimGraph2SerializedPoseRecipeSlot_t* g_pAnimGraph2SerializedPoseRecipeSlot_t = nullptr;
AutoRoomDoorwayPairs_t* g_pAutoRoomDoorwayPairs_t = nullptr;
CAI_ChangeHintGroup* g_pCAI_ChangeHintGroup = nullptr;
CAI_Expresser* g_pCAI_Expresser = nullptr;
CAI_ExpresserWithFollowup* g_pCAI_ExpresserWithFollowup = nullptr;
CAK47* g_pCAK47 = nullptr;
CAmbientGeneric* g_pCAmbientGeneric = nullptr;
CAnimGraphControllerBase* g_pCAnimGraphControllerBase = nullptr;
CAnimGraphControllerManager* g_pCAnimGraphControllerManager = nullptr;
CAttributeContainer* g_pCAttributeContainer = nullptr;
CAttributeList* g_pCAttributeList = nullptr;
CAttributeManager* g_pCAttributeManager = nullptr;
CAttributeManager__cached_attribute_float_t* g_pCAttributeManager__cached_attribute_float_t = nullptr;
CBarnLight* g_pCBarnLight = nullptr;
CBaseAnimGraph* g_pCBaseAnimGraph = nullptr;
CBaseAnimGraphController* g_pCBaseAnimGraphController = nullptr;
CBaseAnimGraphDestructibleParts_GraphController* g_pCBaseAnimGraphDestructibleParts_GraphController = nullptr;
CBaseButton* g_pCBaseButton = nullptr;
CBaseCSGrenade* g_pCBaseCSGrenade = nullptr;
CBaseCSGrenadeProjectile* g_pCBaseCSGrenadeProjectile = nullptr;
CBaseClientUIEntity* g_pCBaseClientUIEntity = nullptr;
CBaseCombatCharacter* g_pCBaseCombatCharacter = nullptr;
CBaseDMStart* g_pCBaseDMStart = nullptr;
CBaseDoor* g_pCBaseDoor = nullptr;
CBaseEntity* g_pCBaseEntity = nullptr;
CBaseFilter* g_pCBaseFilter = nullptr;
CBaseGrenade* g_pCBaseGrenade = nullptr;
CBaseIssue* g_pCBaseIssue = nullptr;
CBaseModelEntity* g_pCBaseModelEntity = nullptr;
CBaseModelEntity__OnDamageLevelChangedArgs_t* g_pCBaseModelEntity__OnDamageLevelChangedArgs_t = nullptr;
CBaseMoveBehavior* g_pCBaseMoveBehavior = nullptr;
CBasePlatTrain* g_pCBasePlatTrain = nullptr;
CBasePlayerController* g_pCBasePlayerController = nullptr;
CBasePlayerPawn* g_pCBasePlayerPawn = nullptr;
CBasePlayerVData* g_pCBasePlayerVData = nullptr;
CBasePlayerWeapon* g_pCBasePlayerWeapon = nullptr;
CBasePlayerWeaponVData* g_pCBasePlayerWeaponVData = nullptr;
CBaseProp* g_pCBaseProp = nullptr;
CBasePropDoor* g_pCBasePropDoor = nullptr;
CBasePulseGraphInstance* g_pCBasePulseGraphInstance = nullptr;
CBaseToggle* g_pCBaseToggle = nullptr;
CBaseTrigger* g_pCBaseTrigger = nullptr;
CBeam* g_pCBeam = nullptr;
CBlood* g_pCBlood = nullptr;
CBodyComponent* g_pCBodyComponent = nullptr;
CBodyComponentBaseAnimGraph* g_pCBodyComponentBaseAnimGraph = nullptr;
CBodyComponentBaseModelEntity* g_pCBodyComponentBaseModelEntity = nullptr;
CBodyComponentPoint* g_pCBodyComponentPoint = nullptr;
CBodyComponentSkeletonInstance* g_pCBodyComponentSkeletonInstance = nullptr;
CBombTarget* g_pCBombTarget = nullptr;
CBot* g_pCBot = nullptr;
CBreakable* g_pCBreakable = nullptr;
CBreakableProp* g_pCBreakableProp = nullptr;
CBuoyancyHelper* g_pCBuoyancyHelper = nullptr;
CBuyZone* g_pCBuyZone = nullptr;
CC4* g_pCC4 = nullptr;
CCS2ChickenGraphController* g_pCCS2ChickenGraphController = nullptr;
CCS2PawnGraphController* g_pCCS2PawnGraphController = nullptr;
CCS2WeaponGraphController* g_pCCS2WeaponGraphController = nullptr;
CCSBot* g_pCCSBot = nullptr;
CCSGO_EndOfMatchLineupEnd* g_pCCSGO_EndOfMatchLineupEnd = nullptr;
CCSGO_EndOfMatchLineupEndpoint* g_pCCSGO_EndOfMatchLineupEndpoint = nullptr;
CCSGO_EndOfMatchLineupStart* g_pCCSGO_EndOfMatchLineupStart = nullptr;
CCSGO_TeamIntroCharacterPosition* g_pCCSGO_TeamIntroCharacterPosition = nullptr;
CCSGO_TeamIntroCounterTerroristPosition* g_pCCSGO_TeamIntroCounterTerroristPosition = nullptr;
CCSGO_TeamIntroTerroristPosition* g_pCCSGO_TeamIntroTerroristPosition = nullptr;
CCSGO_TeamPreviewCharacterPosition* g_pCCSGO_TeamPreviewCharacterPosition = nullptr;
CCSGO_TeamSelectCharacterPosition* g_pCCSGO_TeamSelectCharacterPosition = nullptr;
CCSGO_TeamSelectCounterTerroristPosition* g_pCCSGO_TeamSelectCounterTerroristPosition = nullptr;
CCSGO_TeamSelectTerroristPosition* g_pCCSGO_TeamSelectTerroristPosition = nullptr;
CCSGO_WingmanIntroCharacterPosition* g_pCCSGO_WingmanIntroCharacterPosition = nullptr;
CCSGO_WingmanIntroCounterTerroristPosition* g_pCCSGO_WingmanIntroCounterTerroristPosition = nullptr;
CCSGO_WingmanIntroTerroristPosition* g_pCCSGO_WingmanIntroTerroristPosition = nullptr;
CCSGameModeRules* g_pCCSGameModeRules = nullptr;
CCSGameModeRules_ArmsRace* g_pCCSGameModeRules_ArmsRace = nullptr;
CCSGameModeRules_Deathmatch* g_pCCSGameModeRules_Deathmatch = nullptr;
CCSGameModeRules_Noop* g_pCCSGameModeRules_Noop = nullptr;
CCSGameRules* g_pCCSGameRules = nullptr;
CCSGameRulesProxy* g_pCCSGameRulesProxy = nullptr;
CCSMinimapBoundary* g_pCCSMinimapBoundary = nullptr;
CCSObserverPawn* g_pCCSObserverPawn = nullptr;
CCSObserver_CameraServices* g_pCCSObserver_CameraServices = nullptr;
CCSObserver_MovementServices* g_pCCSObserver_MovementServices = nullptr;
CCSObserver_ObserverServices* g_pCCSObserver_ObserverServices = nullptr;
CCSObserver_UseServices* g_pCCSObserver_UseServices = nullptr;
CCSPetPlacement* g_pCCSPetPlacement = nullptr;
CCSPlace* g_pCCSPlace = nullptr;
CCSPlayerAnimationState* g_pCCSPlayerAnimationState = nullptr;
CCSPlayerBase_CameraServices* g_pCCSPlayerBase_CameraServices = nullptr;
CCSPlayerController_ActionTrackingServices* g_pCCSPlayerController_ActionTrackingServices = nullptr;
CCSPlayerController_DamageServices* g_pCCSPlayerController_DamageServices = nullptr;
CCSPlayerController_InGameMoneyServices* g_pCCSPlayerController_InGameMoneyServices = nullptr;
CCSPlayerController_InventoryServices* g_pCCSPlayerController_InventoryServices = nullptr;
CCSPlayerLegacyJump* g_pCCSPlayerLegacyJump = nullptr;
CCSPlayerModernJump* g_pCCSPlayerModernJump = nullptr;
CCSPlayerPawn* g_pCCSPlayerPawn = nullptr;
CCSPlayerPawnBase* g_pCCSPlayerPawnBase = nullptr;
CCSPlayerResource* g_pCCSPlayerResource = nullptr;
CCSPlayer_ActionTrackingServices* g_pCCSPlayer_ActionTrackingServices = nullptr;
CCSPlayer_AimPunchServices* g_pCCSPlayer_AimPunchServices = nullptr;
CCSPlayer_BulletServices* g_pCCSPlayer_BulletServices = nullptr;
CCSPlayer_BuyServices* g_pCCSPlayer_BuyServices = nullptr;
CCSPlayer_CameraServices* g_pCCSPlayer_CameraServices = nullptr;
CCSPlayer_DamageReactServices* g_pCCSPlayer_DamageReactServices = nullptr;
CCSPlayer_HostageServices* g_pCCSPlayer_HostageServices = nullptr;
CCSPlayer_ItemServices* g_pCCSPlayer_ItemServices = nullptr;
CCSPlayer_MovementServices* g_pCCSPlayer_MovementServices = nullptr;
CCSPlayer_PingServices* g_pCCSPlayer_PingServices = nullptr;
CCSPlayer_RadioServices* g_pCCSPlayer_RadioServices = nullptr;
CCSPlayer_UseServices* g_pCCSPlayer_UseServices = nullptr;
CCSPlayer_WaterServices* g_pCCSPlayer_WaterServices = nullptr;
CCSPlayer_WeaponServices* g_pCCSPlayer_WeaponServices = nullptr;
CCSPointScriptEntity* g_pCCSPointScriptEntity = nullptr;
CCSSprite* g_pCCSSprite = nullptr;
CCSTeam* g_pCCSTeam = nullptr;
CCSWeaponBase* g_pCCSWeaponBase = nullptr;
CCSWeaponBaseGun* g_pCCSWeaponBaseGun = nullptr;
CCSWeaponBaseShotgun* g_pCCSWeaponBaseShotgun = nullptr;
CCSWeaponBaseVData* g_pCCSWeaponBaseVData = nullptr;
CCashStack* g_pCCashStack = nullptr;
CChangeLevel* g_pCChangeLevel = nullptr;
CChicken* g_pCChicken = nullptr;
CChoreoComponent* g_pCChoreoComponent = nullptr;
CChoreoInfoTarget* g_pCChoreoInfoTarget = nullptr;
CCitadelSoundOpvarSetOBB* g_pCCitadelSoundOpvarSetOBB = nullptr;
CCollisionProperty* g_pCCollisionProperty = nullptr;
CColorCorrection* g_pCColorCorrection = nullptr;
CColorCorrectionVolume* g_pCColorCorrectionVolume = nullptr;
CCommentaryAuto* g_pCCommentaryAuto = nullptr;
CCommentaryViewPosition* g_pCCommentaryViewPosition = nullptr;
CConstantForceController* g_pCConstantForceController = nullptr;
CConstraintAnchor* g_pCConstraintAnchor = nullptr;
CCredits* g_pCCredits = nullptr;
CDEagle* g_pCDEagle = nullptr;
CDamageRecord* g_pCDamageRecord = nullptr;
CDebugHistory* g_pCDebugHistory = nullptr;
CDecalGroupVData* g_pCDecalGroupVData = nullptr;
CDecoyGrenade* g_pCDecoyGrenade = nullptr;
CDecoyProjectile* g_pCDecoyProjectile = nullptr;
CDestructiblePartsComponent* g_pCDestructiblePartsComponent = nullptr;
CDynamicLight* g_pCDynamicLight = nullptr;
CDynamicNavConnectionsVolume* g_pCDynamicNavConnectionsVolume = nullptr;
CDynamicProp* g_pCDynamicProp = nullptr;
CDynamicPropAlias_cable_dynamic* g_pCDynamicPropAlias_cable_dynamic = nullptr;
CDynamicPropAlias_dynamic_prop* g_pCDynamicPropAlias_dynamic_prop = nullptr;
CDynamicPropAlias_prop_dynamic_override* g_pCDynamicPropAlias_prop_dynamic_override = nullptr;
CEconEntity* g_pCEconEntity = nullptr;
CEconItemAttribute* g_pCEconItemAttribute = nullptr;
CEconItemView* g_pCEconItemView = nullptr;
CEconWearable* g_pCEconWearable = nullptr;
CEmptyGraphController* g_pCEmptyGraphController = nullptr;
CEnableMotionFixup* g_pCEnableMotionFixup = nullptr;
CEntityAttributeTable* g_pCEntityAttributeTable = nullptr;
CEntityBlocker* g_pCEntityBlocker = nullptr;
CEntityDissolve* g_pCEntityDissolve = nullptr;
CEntityFlame* g_pCEntityFlame = nullptr;
CEntitySubclassVDataBase* g_pCEntitySubclassVDataBase = nullptr;
CEnvBeam* g_pCEnvBeam = nullptr;
CEnvBeverage* g_pCEnvBeverage = nullptr;
CEnvCombinedLightProbeVolume* g_pCEnvCombinedLightProbeVolume = nullptr;
CEnvCombinedLightProbeVolumeAlias_func_combined_light_probe_volume*
    g_pCEnvCombinedLightProbeVolumeAlias_func_combined_light_probe_volume = nullptr;
CEnvCubemap* g_pCEnvCubemap = nullptr;
CEnvCubemapBox* g_pCEnvCubemapBox = nullptr;
CEnvCubemapFog* g_pCEnvCubemapFog = nullptr;
CEnvDecal* g_pCEnvDecal = nullptr;
CEnvDetailController* g_pCEnvDetailController = nullptr;
CEnvEntityIgniter* g_pCEnvEntityIgniter = nullptr;
CEnvEntityMaker* g_pCEnvEntityMaker = nullptr;
CEnvExplosion* g_pCEnvExplosion = nullptr;
CEnvFade* g_pCEnvFade = nullptr;
CEnvGlobal* g_pCEnvGlobal = nullptr;
CEnvHudHint* g_pCEnvHudHint = nullptr;
CEnvInstructorHint* g_pCEnvInstructorHint = nullptr;
CEnvInstructorVRHint* g_pCEnvInstructorVRHint = nullptr;
CEnvLaser* g_pCEnvLaser = nullptr;
CEnvLightProbeVolume* g_pCEnvLightProbeVolume = nullptr;
CEnvMuzzleFlash* g_pCEnvMuzzleFlash = nullptr;
CEnvParticleGlow* g_pCEnvParticleGlow = nullptr;
CEnvShake* g_pCEnvShake = nullptr;
CEnvSky* g_pCEnvSky = nullptr;
CEnvSoundscape* g_pCEnvSoundscape = nullptr;
CEnvSoundscapeAlias_snd_soundscape* g_pCEnvSoundscapeAlias_snd_soundscape = nullptr;
CEnvSoundscapeProxy* g_pCEnvSoundscapeProxy = nullptr;
CEnvSoundscapeProxyAlias_snd_soundscape_proxy* g_pCEnvSoundscapeProxyAlias_snd_soundscape_proxy = nullptr;
CEnvSoundscapeTriggerable* g_pCEnvSoundscapeTriggerable = nullptr;
CEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable* g_pCEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable
    = nullptr;
CEnvSpark* g_pCEnvSpark = nullptr;
CEnvSplash* g_pCEnvSplash = nullptr;
CEnvTilt* g_pCEnvTilt = nullptr;
CEnvViewPunch* g_pCEnvViewPunch = nullptr;
CEnvVolumetricFogController* g_pCEnvVolumetricFogController = nullptr;
CEnvVolumetricFogVolume* g_pCEnvVolumetricFogVolume = nullptr;
CEnvWind* g_pCEnvWind = nullptr;
CEnvWindController* g_pCEnvWindController = nullptr;
CEnvWindShared* g_pCEnvWindShared = nullptr;
CEnvWindVolume* g_pCEnvWindVolume = nullptr;
CExampleSchemaVData_Monomorphic* g_pCExampleSchemaVData_Monomorphic = nullptr;
CExampleSchemaVData_PolymorphicBase* g_pCExampleSchemaVData_PolymorphicBase = nullptr;
CExampleSchemaVData_PolymorphicDerivedA* g_pCExampleSchemaVData_PolymorphicDerivedA = nullptr;
CExampleSchemaVData_PolymorphicDerivedB* g_pCExampleSchemaVData_PolymorphicDerivedB = nullptr;
CFilterAttributeInt* g_pCFilterAttributeInt = nullptr;
CFilterClass* g_pCFilterClass = nullptr;
CFilterContext* g_pCFilterContext = nullptr;
CFilterEnemy* g_pCFilterEnemy = nullptr;
CFilterLOS* g_pCFilterLOS = nullptr;
CFilterMassGreater* g_pCFilterMassGreater = nullptr;
CFilterModel* g_pCFilterModel = nullptr;
CFilterMultiple* g_pCFilterMultiple = nullptr;
CFilterName* g_pCFilterName = nullptr;
CFilterProximity* g_pCFilterProximity = nullptr;
CFilterTeam* g_pCFilterTeam = nullptr;
CFireCrackerBlast* g_pCFireCrackerBlast = nullptr;
CFiringModeFloat* g_pCFiringModeFloat = nullptr;
CFiringModeInt* g_pCFiringModeInt = nullptr;
CFish* g_pCFish = nullptr;
CFishPool* g_pCFishPool = nullptr;
CFlashbang* g_pCFlashbang = nullptr;
CFlashbangProjectile* g_pCFlashbangProjectile = nullptr;
CFogController* g_pCFogController = nullptr;
CFogTrigger* g_pCFogTrigger = nullptr;
CFogVolume* g_pCFogVolume = nullptr;
CFootstepControl* g_pCFootstepControl = nullptr;
CFuncBrush* g_pCFuncBrush = nullptr;
CFuncConveyor* g_pCFuncConveyor = nullptr;
CFuncElectrifiedVolume* g_pCFuncElectrifiedVolume = nullptr;
CFuncIllusionary* g_pCFuncIllusionary = nullptr;
CFuncInteractionLayerClip* g_pCFuncInteractionLayerClip = nullptr;
CFuncLadder* g_pCFuncLadder = nullptr;
CFuncLadderAlias_func_useableladder* g_pCFuncLadderAlias_func_useableladder = nullptr;
CFuncMonitor* g_pCFuncMonitor = nullptr;
CFuncMoveLinear* g_pCFuncMoveLinear = nullptr;
CFuncMoveLinearAlias_momentary_door* g_pCFuncMoveLinearAlias_momentary_door = nullptr;
CFuncMover* g_pCFuncMover = nullptr;
CFuncNavBlocker* g_pCFuncNavBlocker = nullptr;
CFuncNavObstruction* g_pCFuncNavObstruction = nullptr;
CFuncPlat* g_pCFuncPlat = nullptr;
CFuncPlatRot* g_pCFuncPlatRot = nullptr;
CFuncPropRespawnZone* g_pCFuncPropRespawnZone = nullptr;
CFuncRetakeBarrier* g_pCFuncRetakeBarrier = nullptr;
CFuncRotating* g_pCFuncRotating = nullptr;
CFuncRotator* g_pCFuncRotator = nullptr;
CFuncShatterglass* g_pCFuncShatterglass = nullptr;
CFuncTankTrain* g_pCFuncTankTrain = nullptr;
CFuncTimescale* g_pCFuncTimescale = nullptr;
CFuncTrackAuto* g_pCFuncTrackAuto = nullptr;
CFuncTrackChange* g_pCFuncTrackChange = nullptr;
CFuncTrackTrain* g_pCFuncTrackTrain = nullptr;
CFuncTrain* g_pCFuncTrain = nullptr;
CFuncTrainControls* g_pCFuncTrainControls = nullptr;
CFuncVPhysicsClip* g_pCFuncVPhysicsClip = nullptr;
CFuncVehicleClip* g_pCFuncVehicleClip = nullptr;
CFuncWall* g_pCFuncWall = nullptr;
CFuncWallToggle* g_pCFuncWallToggle = nullptr;
CFuncWater* g_pCFuncWater = nullptr;
CGameChoreoServices* g_pCGameChoreoServices = nullptr;
CGameEnd* g_pCGameEnd = nullptr;
CGameGibManager* g_pCGameGibManager = nullptr;
CGameMoney* g_pCGameMoney = nullptr;
CGamePlayerEquip* g_pCGamePlayerEquip = nullptr;
CGamePlayerZone* g_pCGamePlayerZone = nullptr;
CGameRules* g_pCGameRules = nullptr;
CGameRulesProxy* g_pCGameRulesProxy = nullptr;
CGameSceneNode* g_pCGameSceneNode = nullptr;
CGameText* g_pCGameText = nullptr;
CGenericConstraint* g_pCGenericConstraint = nullptr;
CGlowProperty* g_pCGlowProperty = nullptr;
CGradientFog* g_pCGradientFog = nullptr;
CGunTarget* g_pCGunTarget = nullptr;
CHEGrenade* g_pCHEGrenade = nullptr;
CHEGrenadeProjectile* g_pCHEGrenadeProjectile = nullptr;
CHandleDummy* g_pCHandleDummy = nullptr;
CHandleTest* g_pCHandleTest = nullptr;
CHitboxComponent* g_pCHitboxComponent = nullptr;
CHostage* g_pCHostage = nullptr;
CHostageAlias_info_hostage_spawn* g_pCHostageAlias_info_hostage_spawn = nullptr;
CHostageCarriableProp* g_pCHostageCarriableProp = nullptr;
CHostageExpresserShim* g_pCHostageExpresserShim = nullptr;
CHostageRescueZone* g_pCHostageRescueZone = nullptr;
CHostageRescueZoneShim* g_pCHostageRescueZoneShim = nullptr;
CInButtonState* g_pCInButtonState = nullptr;
CIncendiaryGrenade* g_pCIncendiaryGrenade = nullptr;
CInferno* g_pCInferno = nullptr;
CInfoChoreoAnchor* g_pCInfoChoreoAnchor = nullptr;
CInfoChoreoAnchorPosition* g_pCInfoChoreoAnchorPosition = nullptr;
CInfoData* g_pCInfoData = nullptr;
CInfoDeathmatchSpawn* g_pCInfoDeathmatchSpawn = nullptr;
CInfoDynamicShadowHint* g_pCInfoDynamicShadowHint = nullptr;
CInfoDynamicShadowHintBox* g_pCInfoDynamicShadowHintBox = nullptr;
CInfoFan* g_pCInfoFan = nullptr;
CInfoGameEventProxy* g_pCInfoGameEventProxy = nullptr;
CInfoInstructorHintBombTargetA* g_pCInfoInstructorHintBombTargetA = nullptr;
CInfoInstructorHintBombTargetB* g_pCInfoInstructorHintBombTargetB = nullptr;
CInfoInstructorHintHostageRescueZone* g_pCInfoInstructorHintHostageRescueZone = nullptr;
CInfoInstructorHintTarget* g_pCInfoInstructorHintTarget = nullptr;
CInfoInteraction* g_pCInfoInteraction = nullptr;
CInfoLadderDismount* g_pCInfoLadderDismount = nullptr;
CInfoLandmark* g_pCInfoLandmark = nullptr;
CInfoOffscreenPanoramaTexture* g_pCInfoOffscreenPanoramaTexture = nullptr;
CInfoParticleTarget* g_pCInfoParticleTarget = nullptr;
CInfoPlayerCounterterrorist* g_pCInfoPlayerCounterterrorist = nullptr;
CInfoPlayerStart* g_pCInfoPlayerStart = nullptr;
CInfoPlayerTerrorist* g_pCInfoPlayerTerrorist = nullptr;
CInfoSpawnGroupLandmark* g_pCInfoSpawnGroupLandmark = nullptr;
CInfoSpawnGroupLoadUnload* g_pCInfoSpawnGroupLoadUnload = nullptr;
CInfoTarget* g_pCInfoTarget = nullptr;
CInfoTargetServerOnly* g_pCInfoTargetServerOnly = nullptr;
CInfoTeleportDestination* g_pCInfoTeleportDestination = nullptr;
CInfoVisibilityBox* g_pCInfoVisibilityBox = nullptr;
CInfoWorldLayer* g_pCInfoWorldLayer = nullptr;
CInstancedSceneEntity* g_pCInstancedSceneEntity = nullptr;
CInstructorEventEntity* g_pCInstructorEventEntity = nullptr;
CIronSightController* g_pCIronSightController = nullptr;
CItem* g_pCItem = nullptr;
CItemAssaultSuit* g_pCItemAssaultSuit = nullptr;
CItemDefuser* g_pCItemDefuser = nullptr;
CItemDefuserAlias_item_defuser* g_pCItemDefuserAlias_item_defuser = nullptr;
CItemDogtags* g_pCItemDogtags = nullptr;
CItemGeneric* g_pCItemGeneric = nullptr;
CItemGenericTriggerHelper* g_pCItemGenericTriggerHelper = nullptr;
CItemKevlar* g_pCItemKevlar = nullptr;
CItemSoda* g_pCItemSoda = nullptr;
CItem_Healthshot* g_pCItem_Healthshot = nullptr;
CKeepUpright* g_pCKeepUpright = nullptr;
CKnife* g_pCKnife = nullptr;
CLightComponent* g_pCLightComponent = nullptr;
CLightDirectionalEntity* g_pCLightDirectionalEntity = nullptr;
CLightEntity* g_pCLightEntity = nullptr;
CLightEnvironmentEntity* g_pCLightEnvironmentEntity = nullptr;
CLightOrthoEntity* g_pCLightOrthoEntity = nullptr;
CLightSpotEntity* g_pCLightSpotEntity = nullptr;
CLogicAchievement* g_pCLogicAchievement = nullptr;
CLogicActiveAutosave* g_pCLogicActiveAutosave = nullptr;
CLogicAuto* g_pCLogicAuto = nullptr;
CLogicAutosave* g_pCLogicAutosave = nullptr;
CLogicBranch* g_pCLogicBranch = nullptr;
CLogicBranchList* g_pCLogicBranchList = nullptr;
CLogicCase* g_pCLogicCase = nullptr;
CLogicCollisionPair* g_pCLogicCollisionPair = nullptr;
CLogicCompare* g_pCLogicCompare = nullptr;
CLogicDistanceAutosave* g_pCLogicDistanceAutosave = nullptr;
CLogicDistanceCheck* g_pCLogicDistanceCheck = nullptr;
CLogicEventListener* g_pCLogicEventListener = nullptr;
CLogicGameEvent* g_pCLogicGameEvent = nullptr;
CLogicGameEventListener* g_pCLogicGameEventListener = nullptr;
CLogicLineToEntity* g_pCLogicLineToEntity = nullptr;
CLogicMeasureMovement* g_pCLogicMeasureMovement = nullptr;
CLogicNPCCounter* g_pCLogicNPCCounter = nullptr;
CLogicNPCCounterAABB* g_pCLogicNPCCounterAABB = nullptr;
CLogicNPCCounterOBB* g_pCLogicNPCCounterOBB = nullptr;
CLogicNavigation* g_pCLogicNavigation = nullptr;
CLogicPlayerProxy* g_pCLogicPlayerProxy = nullptr;
CLogicProximity* g_pCLogicProximity = nullptr;
CLogicRelay* g_pCLogicRelay = nullptr;
CLogicScript* g_pCLogicScript = nullptr;
CLogicalEntity* g_pCLogicalEntity = nullptr;
CMapInfo* g_pCMapInfo = nullptr;
CMapSharedEnvironment* g_pCMapSharedEnvironment = nullptr;
CMapVetoPickController* g_pCMapVetoPickController = nullptr;
CMarkupVolume* g_pCMarkupVolume = nullptr;
CMarkupVolumeTagged* g_pCMarkupVolumeTagged = nullptr;
CMarkupVolumeTagged_Nav* g_pCMarkupVolumeTagged_Nav = nullptr;
CMarkupVolumeTagged_NavGame* g_pCMarkupVolumeTagged_NavGame = nullptr;
CMarkupVolumeWithRef* g_pCMarkupVolumeWithRef = nullptr;
CMathColorBlend* g_pCMathColorBlend = nullptr;
CMathCounter* g_pCMathCounter = nullptr;
CMathRemap* g_pCMathRemap = nullptr;
CMessage* g_pCMessage = nullptr;
CMessageEntity* g_pCMessageEntity = nullptr;
CModelPointEntity* g_pCModelPointEntity = nullptr;
CModelState* g_pCModelState = nullptr;
CMolotovGrenade* g_pCMolotovGrenade = nullptr;
CMolotovProjectile* g_pCMolotovProjectile = nullptr;
CMomentaryRotButton* g_pCMomentaryRotButton = nullptr;
CMoodVData* g_pCMoodVData = nullptr;
CMotorController* g_pCMotorController = nullptr;
CMovementStatsProperty* g_pCMovementStatsProperty = nullptr;
CMoverPathNode* g_pCMoverPathNode = nullptr;
CMultiLightProxy* g_pCMultiLightProxy = nullptr;
CMultiSource* g_pCMultiSource = nullptr;
CMultiplayRules* g_pCMultiplayRules = nullptr;
CMultiplayer_Expresser* g_pCMultiplayer_Expresser = nullptr;
CNavHullPresetVData* g_pCNavHullPresetVData = nullptr;
CNavHullVData* g_pCNavHullVData = nullptr;
CNavSpaceInfo* g_pCNavSpaceInfo = nullptr;
CNavWalkable* g_pCNavWalkable = nullptr;
CNetworkOriginCellCoordQuantizedVector* g_pCNetworkOriginCellCoordQuantizedVector = nullptr;
CNetworkTransmitComponent* g_pCNetworkTransmitComponent = nullptr;
CNetworkVelocityVector* g_pCNetworkVelocityVector = nullptr;
CNetworkViewOffsetVector* g_pCNetworkViewOffsetVector = nullptr;
CNmGraphInstance* g_pCNmGraphInstance = nullptr;
CNmTarget* g_pCNmTarget = nullptr;
CNullEntity* g_pCNullEntity = nullptr;
COmniLight* g_pCOmniLight = nullptr;
COrnamentProp* g_pCOrnamentProp = nullptr;
CParticleSystem* g_pCParticleSystem = nullptr;
CPathCorner* g_pCPathCorner = nullptr;
CPathCornerCrash* g_pCPathCornerCrash = nullptr;
CPathKeyFrame* g_pCPathKeyFrame = nullptr;
CPathMover* g_pCPathMover = nullptr;
CPathMoverEntitySpawner* g_pCPathMoverEntitySpawner = nullptr;
CPathNode* g_pCPathNode = nullptr;
CPathParticleRope* g_pCPathParticleRope = nullptr;
CPathParticleRopeAlias_path_particle_rope_clientside* g_pCPathParticleRopeAlias_path_particle_rope_clientside = nullptr;
CPathQueryComponent* g_pCPathQueryComponent = nullptr;
CPathSimple* g_pCPathSimple = nullptr;
CPathTrack* g_pCPathTrack = nullptr;
CPathWithDynamicNodes* g_pCPathWithDynamicNodes = nullptr;
CPhysBallSocket* g_pCPhysBallSocket = nullptr;
CPhysBox* g_pCPhysBox = nullptr;
CPhysConstraint* g_pCPhysConstraint = nullptr;
CPhysExplosion* g_pCPhysExplosion = nullptr;
CPhysFixed* g_pCPhysFixed = nullptr;
CPhysForce* g_pCPhysForce = nullptr;
CPhysHinge* g_pCPhysHinge = nullptr;
CPhysHingeAlias_phys_hinge_local* g_pCPhysHingeAlias_phys_hinge_local = nullptr;
CPhysImpact* g_pCPhysImpact = nullptr;
CPhysLength* g_pCPhysLength = nullptr;
CPhysMagnet* g_pCPhysMagnet = nullptr;
CPhysMotor* g_pCPhysMotor = nullptr;
CPhysPulley* g_pCPhysPulley = nullptr;
CPhysSlideConstraint* g_pCPhysSlideConstraint = nullptr;
CPhysThruster* g_pCPhysThruster = nullptr;
CPhysTorque* g_pCPhysTorque = nullptr;
CPhysWheelConstraint* g_pCPhysWheelConstraint = nullptr;
CPhysicalButton* g_pCPhysicalButton = nullptr;
CPhysicsEntitySolver* g_pCPhysicsEntitySolver = nullptr;
CPhysicsProp* g_pCPhysicsProp = nullptr;
CPhysicsPropMultiplayer* g_pCPhysicsPropMultiplayer = nullptr;
CPhysicsPropOverride* g_pCPhysicsPropOverride = nullptr;
CPhysicsPropRespawnable* g_pCPhysicsPropRespawnable = nullptr;
CPhysicsShake* g_pCPhysicsShake = nullptr;
CPhysicsSpring* g_pCPhysicsSpring = nullptr;
CPhysicsWire* g_pCPhysicsWire = nullptr;
CPlantedC4* g_pCPlantedC4 = nullptr;
CPlatTrigger* g_pCPlatTrigger = nullptr;
CPlayerControllerComponent* g_pCPlayerControllerComponent = nullptr;
CPlayerPawnComponent* g_pCPlayerPawnComponent = nullptr;
CPlayerPing* g_pCPlayerPing = nullptr;
CPlayerSprayDecal* g_pCPlayerSprayDecal = nullptr;
CPlayerVisibility* g_pCPlayerVisibility = nullptr;
CPlayer_AutoaimServices* g_pCPlayer_AutoaimServices = nullptr;
CPlayer_CameraServices* g_pCPlayer_CameraServices = nullptr;
CPlayer_FlashlightServices* g_pCPlayer_FlashlightServices = nullptr;
CPlayer_ItemServices* g_pCPlayer_ItemServices = nullptr;
CPlayer_MovementServices* g_pCPlayer_MovementServices = nullptr;
CPlayer_MovementServices_Humanoid* g_pCPlayer_MovementServices_Humanoid = nullptr;
CPlayer_ObserverServices* g_pCPlayer_ObserverServices = nullptr;
CPlayer_UseServices* g_pCPlayer_UseServices = nullptr;
CPlayer_WaterServices* g_pCPlayer_WaterServices = nullptr;
CPlayer_WeaponServices* g_pCPlayer_WeaponServices = nullptr;
CPointAngleSensor* g_pCPointAngleSensor = nullptr;
CPointAngularVelocitySensor* g_pCPointAngularVelocitySensor = nullptr;
CPointBroadcastClientCommand* g_pCPointBroadcastClientCommand = nullptr;
CPointCamera* g_pCPointCamera = nullptr;
CPointCameraVFOV* g_pCPointCameraVFOV = nullptr;
CPointChildModifier* g_pCPointChildModifier = nullptr;
CPointClientCommand* g_pCPointClientCommand = nullptr;
CPointClientUIDialog* g_pCPointClientUIDialog = nullptr;
CPointClientUIWorldPanel* g_pCPointClientUIWorldPanel = nullptr;
CPointClientUIWorldTextPanel* g_pCPointClientUIWorldTextPanel = nullptr;
CPointCommentaryNode* g_pCPointCommentaryNode = nullptr;
CPointEntity* g_pCPointEntity = nullptr;
CPointEntityFinder* g_pCPointEntityFinder = nullptr;
CPointGamestatsCounter* g_pCPointGamestatsCounter = nullptr;
CPointGiveAmmo* g_pCPointGiveAmmo = nullptr;
CPointHurt* g_pCPointHurt = nullptr;
CPointOrient* g_pCPointOrient = nullptr;
CPointPrefab* g_pCPointPrefab = nullptr;
CPointProximitySensor* g_pCPointProximitySensor = nullptr;
CPointPulse* g_pCPointPulse = nullptr;
CPointPush* g_pCPointPush = nullptr;
CPointServerCommand* g_pCPointServerCommand = nullptr;
CPointTeleport* g_pCPointTeleport = nullptr;
CPointTemplate* g_pCPointTemplate = nullptr;
CPointValueRemapper* g_pCPointValueRemapper = nullptr;
CPointVelocitySensor* g_pCPointVelocitySensor = nullptr;
CPointWorldText* g_pCPointWorldText = nullptr;
CPostProcessingVolume* g_pCPostProcessingVolume = nullptr;
CPrecipitation* g_pCPrecipitation = nullptr;
CPrecipitationBlocker* g_pCPrecipitationBlocker = nullptr;
CPrecipitationVData* g_pCPrecipitationVData = nullptr;
CPropDataComponent* g_pCPropDataComponent = nullptr;
CPropDoorRotating* g_pCPropDoorRotating = nullptr;
CPropDoorRotatingBreakable* g_pCPropDoorRotatingBreakable = nullptr;
CPulseGameBlackboard* g_pCPulseGameBlackboard = nullptr;
CPulseGraphInstance_GameBlackboard* g_pCPulseGraphInstance_GameBlackboard = nullptr;
CPulseGraphInstance_ServerEntity* g_pCPulseGraphInstance_ServerEntity = nullptr;
CPushable* g_pCPushable = nullptr;
CRagdollConstraint* g_pCRagdollConstraint = nullptr;
CRagdollMagnet* g_pCRagdollMagnet = nullptr;
CRagdollManager* g_pCRagdollManager = nullptr;
CRagdollProp* g_pCRagdollProp = nullptr;
CRagdollPropAlias_physics_prop_ragdoll* g_pCRagdollPropAlias_physics_prop_ragdoll = nullptr;
CRagdollPropAttached* g_pCRagdollPropAttached = nullptr;
CRangeFloat* g_pCRangeFloat = nullptr;
CRectLight* g_pCRectLight = nullptr;
CRenderComponent* g_pCRenderComponent = nullptr;
CRetakeGameRules* g_pCRetakeGameRules = nullptr;
CRevertSaved* g_pCRevertSaved = nullptr;
CRopeKeyframe* g_pCRopeKeyframe = nullptr;
CRopeKeyframeAlias_move_rope* g_pCRopeKeyframeAlias_move_rope = nullptr;
CRotButton* g_pCRotButton = nullptr;
CRotDoor* g_pCRotDoor = nullptr;
CRotatorTarget* g_pCRotatorTarget = nullptr;
CRuleBrushEntity* g_pCRuleBrushEntity = nullptr;
CRuleEntity* g_pCRuleEntity = nullptr;
CRulePointEntity* g_pCRulePointEntity = nullptr;
CSMatchStats_t* g_pCSMatchStats_t = nullptr;
CSPerRoundStats_t* g_pCSPerRoundStats_t = nullptr;
CSceneEntity* g_pCSceneEntity = nullptr;
CSceneEntityAlias_logic_choreographed_scene* g_pCSceneEntityAlias_logic_choreographed_scene = nullptr;
CSceneListManager* g_pCSceneListManager = nullptr;
CScenePayloadVData* g_pCScenePayloadVData = nullptr;
CScriptComponent* g_pCScriptComponent = nullptr;
CScriptItem* g_pCScriptItem = nullptr;
CScriptNavBlocker* g_pCScriptNavBlocker = nullptr;
CScriptTriggerHurt* g_pCScriptTriggerHurt = nullptr;
CScriptTriggerMultiple* g_pCScriptTriggerMultiple = nullptr;
CScriptTriggerOnce* g_pCScriptTriggerOnce = nullptr;
CScriptTriggerPush* g_pCScriptTriggerPush = nullptr;
CScriptedSequence* g_pCScriptedSequence = nullptr;
CServerOnlyEntity* g_pCServerOnlyEntity = nullptr;
CServerOnlyModelEntity* g_pCServerOnlyModelEntity = nullptr;
CServerOnlyPointEntity* g_pCServerOnlyPointEntity = nullptr;
CServerRagdollTrigger* g_pCServerRagdollTrigger = nullptr;
CShatterGlassShardPhysics* g_pCShatterGlassShardPhysics = nullptr;
CShower* g_pCShower = nullptr;
CSimpleMarkupVolumeTagged* g_pCSimpleMarkupVolumeTagged = nullptr;
CSkeletonAnimationController* g_pCSkeletonAnimationController = nullptr;
CSkeletonInstance* g_pCSkeletonInstance = nullptr;
CSkillFloat* g_pCSkillFloat = nullptr;
CSkillInt* g_pCSkillInt = nullptr;
CSkyCamera* g_pCSkyCamera = nullptr;
CSkyboxReference* g_pCSkyboxReference = nullptr;
CSmokeGrenade* g_pCSmokeGrenade = nullptr;
CSmokeGrenadeProjectile* g_pCSmokeGrenadeProjectile = nullptr;
CSoundAreaEntityBase* g_pCSoundAreaEntityBase = nullptr;
CSoundAreaEntityOrientedBox* g_pCSoundAreaEntityOrientedBox = nullptr;
CSoundAreaEntitySphere* g_pCSoundAreaEntitySphere = nullptr;
CSoundEventAABBEntity* g_pCSoundEventAABBEntity = nullptr;
CSoundEventConeEntity* g_pCSoundEventConeEntity = nullptr;
CSoundEventEntity* g_pCSoundEventEntity = nullptr;
CSoundEventEntityAlias_snd_event_point* g_pCSoundEventEntityAlias_snd_event_point = nullptr;
CSoundEventOBBEntity* g_pCSoundEventOBBEntity = nullptr;
CSoundEventParameter* g_pCSoundEventParameter = nullptr;
CSoundEventPathCornerEntity* g_pCSoundEventPathCornerEntity = nullptr;
CSoundEventSphereEntity* g_pCSoundEventSphereEntity = nullptr;
CSoundOpvarSetAABBEntity* g_pCSoundOpvarSetAABBEntity = nullptr;
CSoundOpvarSetAutoRoomEntity* g_pCSoundOpvarSetAutoRoomEntity = nullptr;
CSoundOpvarSetEntity* g_pCSoundOpvarSetEntity = nullptr;
CSoundOpvarSetOBBEntity* g_pCSoundOpvarSetOBBEntity = nullptr;
CSoundOpvarSetOBBWindEntity* g_pCSoundOpvarSetOBBWindEntity = nullptr;
CSoundOpvarSetPathCornerEntity* g_pCSoundOpvarSetPathCornerEntity = nullptr;
CSoundOpvarSetPointBase* g_pCSoundOpvarSetPointBase = nullptr;
CSoundOpvarSetPointEntity* g_pCSoundOpvarSetPointEntity = nullptr;
CSoundStackSave* g_pCSoundStackSave = nullptr;
CSplineConstraint* g_pCSplineConstraint = nullptr;
CSpotlightEnd* g_pCSpotlightEnd = nullptr;
CSprite* g_pCSprite = nullptr;
CSpriteAlias_env_glow* g_pCSpriteAlias_env_glow = nullptr;
CSpriteOriented* g_pCSpriteOriented = nullptr;
CTankTargetChange* g_pCTankTargetChange = nullptr;
CTankTrainAI* g_pCTankTrainAI = nullptr;
CTeam* g_pCTeam = nullptr;
CTeamplayRules* g_pCTeamplayRules = nullptr;
CTestEffect* g_pCTestEffect = nullptr;
CTestPulseIO* g_pCTestPulseIO = nullptr;
CTestPulseIOComponent* g_pCTestPulseIOComponent = nullptr;
CTestPulseIOComponent_Derived* g_pCTestPulseIOComponent_Derived = nullptr;
CTestPulseIO__EntityHandleIntArgs_t* g_pCTestPulseIO__EntityHandleIntArgs_t = nullptr;
CTestPulseIO__EntityNameStringArgs_t* g_pCTestPulseIO__EntityNameStringArgs_t = nullptr;
CTestPulseIO__FloatStringArgs_t* g_pCTestPulseIO__FloatStringArgs_t = nullptr;
CTestPulseIO__ThreeStringArgs_t* g_pCTestPulseIO__ThreeStringArgs_t = nullptr;
CTextureBasedAnimatable* g_pCTextureBasedAnimatable = nullptr;
CTimerEntity* g_pCTimerEntity = nullptr;
CTonemapController2* g_pCTonemapController2 = nullptr;
CTonemapController2Alias_env_tonemap_controller2* g_pCTonemapController2Alias_env_tonemap_controller2 = nullptr;
CTonemapTrigger* g_pCTonemapTrigger = nullptr;
CTouchExpansionComponent* g_pCTouchExpansionComponent = nullptr;
CTriggerActiveWeaponDetect* g_pCTriggerActiveWeaponDetect = nullptr;
CTriggerBombReset* g_pCTriggerBombReset = nullptr;
CTriggerBrush* g_pCTriggerBrush = nullptr;
CTriggerBuoyancy* g_pCTriggerBuoyancy = nullptr;
CTriggerCallback* g_pCTriggerCallback = nullptr;
CTriggerDetectBulletFire* g_pCTriggerDetectBulletFire = nullptr;
CTriggerDetectExplosion* g_pCTriggerDetectExplosion = nullptr;
CTriggerFan* g_pCTriggerFan = nullptr;
CTriggerGameEvent* g_pCTriggerGameEvent = nullptr;
CTriggerGravity* g_pCTriggerGravity = nullptr;
CTriggerHostageReset* g_pCTriggerHostageReset = nullptr;
CTriggerHurt* g_pCTriggerHurt = nullptr;
CTriggerImpact* g_pCTriggerImpact = nullptr;
CTriggerLerpObject* g_pCTriggerLerpObject = nullptr;
CTriggerLook* g_pCTriggerLook = nullptr;
CTriggerMultiple* g_pCTriggerMultiple = nullptr;
CTriggerOnce* g_pCTriggerOnce = nullptr;
CTriggerPhysics* g_pCTriggerPhysics = nullptr;
CTriggerProximity* g_pCTriggerProximity = nullptr;
CTriggerPush* g_pCTriggerPush = nullptr;
CTriggerRemove* g_pCTriggerRemove = nullptr;
CTriggerSave* g_pCTriggerSave = nullptr;
CTriggerSndSosOpvar* g_pCTriggerSndSosOpvar = nullptr;
CTriggerSoundscape* g_pCTriggerSoundscape = nullptr;
CTriggerTeleport* g_pCTriggerTeleport = nullptr;
CTriggerToggleSave* g_pCTriggerToggleSave = nullptr;
CTriggerVolume* g_pCTriggerVolume = nullptr;
CVariantDefaultAllocator* g_pCVariantDefaultAllocator = nullptr;
CVectorExponentialMovingAverage* g_pCVectorExponentialMovingAverage = nullptr;
CVoteController* g_pCVoteController = nullptr;
CWaterBullet* g_pCWaterBullet = nullptr;
CWeaponAWP* g_pCWeaponAWP = nullptr;
CWeaponAug* g_pCWeaponAug = nullptr;
CWeaponBaseItem* g_pCWeaponBaseItem = nullptr;
CWeaponBizon* g_pCWeaponBizon = nullptr;
CWeaponCZ75a* g_pCWeaponCZ75a = nullptr;
CWeaponElite* g_pCWeaponElite = nullptr;
CWeaponFamas* g_pCWeaponFamas = nullptr;
CWeaponFiveSeven* g_pCWeaponFiveSeven = nullptr;
CWeaponG3SG1* g_pCWeaponG3SG1 = nullptr;
CWeaponGalilAR* g_pCWeaponGalilAR = nullptr;
CWeaponGlock* g_pCWeaponGlock = nullptr;
CWeaponHKP2000* g_pCWeaponHKP2000 = nullptr;
CWeaponM249* g_pCWeaponM249 = nullptr;
CWeaponM4A1* g_pCWeaponM4A1 = nullptr;
CWeaponM4A1Silencer* g_pCWeaponM4A1Silencer = nullptr;
CWeaponMAC10* g_pCWeaponMAC10 = nullptr;
CWeaponMP5SD* g_pCWeaponMP5SD = nullptr;
CWeaponMP7* g_pCWeaponMP7 = nullptr;
CWeaponMP9* g_pCWeaponMP9 = nullptr;
CWeaponMag7* g_pCWeaponMag7 = nullptr;
CWeaponNOVA* g_pCWeaponNOVA = nullptr;
CWeaponNegev* g_pCWeaponNegev = nullptr;
CWeaponP250* g_pCWeaponP250 = nullptr;
CWeaponP90* g_pCWeaponP90 = nullptr;
CWeaponRevolver* g_pCWeaponRevolver = nullptr;
CWeaponSCAR20* g_pCWeaponSCAR20 = nullptr;
CWeaponSG556* g_pCWeaponSG556 = nullptr;
CWeaponSSG08* g_pCWeaponSSG08 = nullptr;
CWeaponSawedoff* g_pCWeaponSawedoff = nullptr;
CWeaponTaser* g_pCWeaponTaser = nullptr;
CWeaponTec9* g_pCWeaponTec9 = nullptr;
CWeaponUMP45* g_pCWeaponUMP45 = nullptr;
CWeaponUSPSilencer* g_pCWeaponUSPSilencer = nullptr;
CWeaponXM1014* g_pCWeaponXM1014 = nullptr;
CWorld* g_pCWorld = nullptr;
ChangeAccessorFieldPathIndex_t* g_pChangeAccessorFieldPathIndex_t = nullptr;
ConstraintSoundInfo* g_pConstraintSoundInfo = nullptr;
CountdownTimer* g_pCountdownTimer = nullptr;
DecalGroupOption_t* g_pDecalGroupOption_t = nullptr;
DestructiblePartDamageRequest_t* g_pDestructiblePartDamageRequest_t = nullptr;
DynamicVolumeDef_t* g_pDynamicVolumeDef_t = nullptr;
EntityRenderAttribute_t* g_pEntityRenderAttribute_t = nullptr;
EntitySpottedState_t* g_pEntitySpottedState_t = nullptr;
Extent* g_pExtent = nullptr;
ExternalAnimGraphHandle_t* g_pExternalAnimGraphHandle_t = nullptr;
ExternalAnimGraph_t* g_pExternalAnimGraph_t = nullptr;
FilterDamageType* g_pFilterDamageType = nullptr;
FilterHealth* g_pFilterHealth = nullptr;
FuncMoverMovementSummary_t* g_pFuncMoverMovementSummary_t = nullptr;
IChoreoServices* g_pIChoreoServices = nullptr;
IEconItemInterface* g_pIEconItemInterface = nullptr;
INavObstacle* g_pINavObstacle = nullptr;
IPhysAggregateInstance* g_pIPhysAggregateInstance = nullptr;
IPhysicsBody* g_pIPhysicsBody = nullptr;
IPhysicsBodyList* g_pIPhysicsBodyList = nullptr;
IPhysicsJoint* g_pIPhysicsJoint = nullptr;
IPhysicsMotionController* g_pIPhysicsMotionController = nullptr;
IPhysicsRagdollControl* g_pIPhysicsRagdollControl = nullptr;
ISkeletonAnimationController* g_pISkeletonAnimationController = nullptr;
InfoForResourceTypeCModel* g_pInfoForResourceTypeCModel = nullptr;
InfoForResourceTypeCNmGraphDefinition* g_pInfoForResourceTypeCNmGraphDefinition = nullptr;
InfoForResourceTypeCPostProcessingResource* g_pInfoForResourceTypeCPostProcessingResource = nullptr;
InfoForResourceTypeCTextureBase* g_pInfoForResourceTypeCTextureBase = nullptr;
InfoForResourceTypeCVDataItemDefs* g_pInfoForResourceTypeCVDataItemDefs = nullptr;
InfoForResourceTypeCVDataResource* g_pInfoForResourceTypeCVDataResource = nullptr;
InfoForResourceTypeIMaterial2* g_pInfoForResourceTypeIMaterial2 = nullptr;
InfoForResourceTypeIParticleSystemDefinition* g_pInfoForResourceTypeIParticleSystemDefinition = nullptr;
IntervalTimer* g_pIntervalTimer = nullptr;
ParticleIndex_t* g_pParticleIndex_t = nullptr;
PhysicsRagdollPose_t* g_pPhysicsRagdollPose_t = nullptr;
RelationshipOverride_t* g_pRelationshipOverride_t = nullptr;
Relationship_t* g_pRelationship_t = nullptr;
ResourceId_t* g_pResourceId_t = nullptr;
ResponseContext_t* g_pResponseContext_t = nullptr;
RotatorHistoryEntry_t* g_pRotatorHistoryEntry_t = nullptr;
RotatorQueueEntry_t* g_pRotatorQueueEntry_t = nullptr;
SceneEventId_t* g_pSceneEventId_t = nullptr;
SceneOpportunityHandle_t* g_pSceneOpportunityHandle_t = nullptr;
SceneRequestHandle_t* g_pSceneRequestHandle_t = nullptr;
SellbackPurchaseEntry_t* g_pSellbackPurchaseEntry_t = nullptr;
ServerAuthoritativeWeaponSlot_t* g_pServerAuthoritativeWeaponSlot_t = nullptr;
SimpleConstraintSoundProfile* g_pSimpleConstraintSoundProfile = nullptr;
SoundOpvarTraceResult_t* g_pSoundOpvarTraceResult_t = nullptr;
SpawnPoint* g_pSpawnPoint = nullptr;
VPhysicsCollisionAttribute_t* g_pVPhysicsCollisionAttribute_t = nullptr;
VelocitySampler* g_pVelocitySampler = nullptr;
ViewAngleServerChange_t* g_pViewAngleServerChange_t = nullptr;
WeaponPurchaseCount_t* g_pWeaponPurchaseCount_t = nullptr;
WeaponPurchaseTracker_t* g_pWeaponPurchaseTracker_t = nullptr;
audioparams_t* g_paudioparams_t = nullptr;
constraint_axislimit_t* g_pconstraint_axislimit_t = nullptr;
constraint_breakableparams_t* g_pconstraint_breakableparams_t = nullptr;
constraint_hingeparams_t* g_pconstraint_hingeparams_t = nullptr;
dynpitchvol_base_t* g_pdynpitchvol_base_t = nullptr;
dynpitchvol_t* g_pdynpitchvol_t = nullptr;
fogparams_t* g_pfogparams_t = nullptr;
fogplayerparams_t* g_pfogplayerparams_t = nullptr;
hudtextparms_t* g_phudtextparms_t = nullptr;
lerpdata_t* g_plerpdata_t = nullptr;
locksound_t* g_plocksound_t = nullptr;
magnetted_objects_t* g_pmagnetted_objects_t = nullptr;
ragdoll_t* g_pragdoll_t = nullptr;
ragdollelement_t* g_pragdollelement_t = nullptr;
ragdollhierarchyjoint_t* g_pragdollhierarchyjoint_t = nullptr;
shard_model_desc_t* g_pshard_model_desc_t = nullptr;
sky3dparams_t* g_psky3dparams_t = nullptr;
sndopvarlatchdata_t* g_psndopvarlatchdata_t = nullptr;
thinkfunc_t* g_pthinkfunc_t = nullptr;

// --- schema entity enums ---
AggregateInstanceStream_t g_AggregateInstanceStream_t{};
AimMatrixBlendMode g_AimMatrixBlendMode{};
AmmoFlags_t g_AmmoFlags_t{};
AmmoPosition_t g_AmmoPosition_t{};
AnimGraphDebugDrawType_t g_AnimGraphDebugDrawType_t{};
AnimLoopMode_t g_AnimLoopMode_t{};
AnimNodeNetworkMode g_AnimNodeNetworkMode{};
AnimParamButton_t g_AnimParamButton_t{};
AnimParamNetworkSetting g_AnimParamNetworkSetting{};
AnimParamType_t g_AnimParamType_t{};
AnimParamVectorType_t g_AnimParamVectorType_t{};
AnimScriptType g_AnimScriptType{};
AnimValueSource g_AnimValueSource{};
AnimVectorSource g_AnimVectorSource{};
AnimationAlgorithm_t g_AnimationAlgorithm_t{};
AnimationProcessingType_t g_AnimationProcessingType_t{};
AnimationSnapshotType_t g_AnimationSnapshotType_t{};
AnimationType_t g_AnimationType_t{};
BBoxVolumeType_t g_BBoxVolumeType_t{};
BeamClipStyle_t g_BeamClipStyle_t{};
BeamType_t g_BeamType_t{};
BeginDeathLifeStateTransition_t g_BeginDeathLifeStateTransition_t{};
BinaryNodeChildOption g_BinaryNodeChildOption{};
BinaryNodeTiming g_BinaryNodeTiming{};
Blend2DMode g_Blend2DMode{};
BlendKeyType g_BlendKeyType{};
BloodType g_BloodType{};
BloomBlendMode_t g_BloomBlendMode_t{};
BlurFilterType_t g_BlurFilterType_t{};
BodySectionAuthority_t g_BodySectionAuthority_t{};
BoneMaskBlendSpace g_BoneMaskBlendSpace{};
BoneTransformSpace_t g_BoneTransformSpace_t{};
BreakableContentsType_t g_BreakableContentsType_t{};
BrushSolidities_e g_BrushSolidities_e{};
C4LightEffect_t g_C4LightEffect_t{};
CAnimationGraphVisualizerPrimitiveType g_CAnimationGraphVisualizerPrimitiveType{};
CCSPlayerAnimationState__AirAction_t g_CCSPlayerAnimationState__AirAction_t{};
CCSPlayerAnimationState__Direction_t g_CCSPlayerAnimationState__Direction_t{};
CCSPlayerAnimationState__GroundMoveState_t g_CCSPlayerAnimationState__GroundMoveState_t{};
CCSPlayerAnimationState__MoveType_t g_CCSPlayerAnimationState__MoveType_t{};
CDebugOverlayCombinedTypes_t g_CDebugOverlayCombinedTypes_t{};
CDebugOverlayFilterTextType_t g_CDebugOverlayFilterTextType_t{};
CDebugOverlayFilterType_t g_CDebugOverlayFilterType_t{};
CFuncMover__FollowConstraint_t g_CFuncMover__FollowConstraint_t{};
CFuncMover__FollowEntityDirection_t g_CFuncMover__FollowEntityDirection_t{};
CFuncMover__Move_t g_CFuncMover__Move_t{};
CFuncMover__OrientationUpdate_t g_CFuncMover__OrientationUpdate_t{};
CFuncMover__TransitionToPathNodeAction_t g_CFuncMover__TransitionToPathNodeAction_t{};
CFuncRotator__Rotate_t g_CFuncRotator__Rotate_t{};
CInfoChoreoLocatorShapeType_t g_CInfoChoreoLocatorShapeType_t{};
CLogicBranchList__LogicBranchListenerLastState_t g_CLogicBranchList__LogicBranchListenerLastState_t{};
CNmCurrentSyncEventNode__InfoType_t g_CNmCurrentSyncEventNode__InfoType_t{};
CNmEventRelevance_t g_CNmEventRelevance_t{};
CNmEventTargetEntity_t g_CNmEventTargetEntity_t{};
CNmFloatAngleMathNode__Operation_t g_CNmFloatAngleMathNode__Operation_t{};
CNmFloatComparisonNode__Comparison_t g_CNmFloatComparisonNode__Comparison_t{};
CNmFloatMathNode__Operator_t g_CNmFloatMathNode__Operator_t{};
CNmIDComparisonNode__Comparison_t g_CNmIDComparisonNode__Comparison_t{};
CNmParticleEvent__Type_t g_CNmParticleEvent__Type_t{};
CNmRootMotionData__SamplingMode_t g_CNmRootMotionData__SamplingMode_t{};
CNmRootMotionOverrideNode__OverrideFlags_t g_CNmRootMotionOverrideNode__OverrideFlags_t{};
CNmSoundEvent__Position_t g_CNmSoundEvent__Position_t{};
CNmStateNode__TimedEvent_t__Comparison_t g_CNmStateNode__TimedEvent_t__Comparison_t{};
CNmSyncEventIndexConditionNode__TriggerMode_t g_CNmSyncEventIndexConditionNode__TriggerMode_t{};
CNmTargetInfoNode__Info_t g_CNmTargetInfoNode__Info_t{};
CNmTargetWarpNode__TargetUpdateRule_t g_CNmTargetWarpNode__TargetUpdateRule_t{};
CNmTimeConditionNode__ComparisonType_t g_CNmTimeConditionNode__ComparisonType_t{};
CNmTimeConditionNode__Operator_t g_CNmTimeConditionNode__Operator_t{};
CNmTransitionNode__TransitionOptions_t g_CNmTransitionNode__TransitionOptions_t{};
CNmVectorInfoNode__Info_t g_CNmVectorInfoNode__Info_t{};
CPhysicsProp__CrateType_t g_CPhysicsProp__CrateType_t{};
CRR_Response__ResponseEnum_t g_CRR_Response__ResponseEnum_t{};
CSPlayerBlockingUseAction_t g_CSPlayerBlockingUseAction_t{};
CSPlayerState g_CSPlayerState{};
CSWeaponCategory g_CSWeaponCategory{};
CSWeaponMode g_CSWeaponMode{};
CSWeaponNameID g_CSWeaponNameID{};
CSWeaponSilencerType g_CSWeaponSilencerType{};
CSWeaponType g_CSWeaponType{};
CVSoundFormat_t g_CVSoundFormat_t{};
CanPlaySequence_t g_CanPlaySequence_t{};
ChatIgnoreType_t g_ChatIgnoreType_t{};
ChickenActivity g_ChickenActivity{};
ChoiceBlendMethod g_ChoiceBlendMethod{};
ChoiceChangeMethod g_ChoiceChangeMethod{};
ChoiceMethod g_ChoiceMethod{};
ChoreoExternalAnimgraphControlState_t g_ChoreoExternalAnimgraphControlState_t{};
ChoreoLookAtMode_t g_ChoreoLookAtMode_t{};
ChoreoLookAtSpeed_t g_ChoreoLookAtSpeed_t{};
Class_T g_Class_T{};
ClosestPointTestType_t g_ClosestPointTestType_t{};
DamageTypes_t g_DamageTypes_t{};
DampingSpeedFunction g_DampingSpeedFunction{};
DebugOverlayBits_t g_DebugOverlayBits_t{};
DecalFlags_t g_DecalFlags_t{};
DecalRtEncoding_t g_DecalRtEncoding_t{};
DestructiblePartDestructionDeathBehavior_t g_DestructiblePartDestructionDeathBehavior_t{};
Detail2Combo_t g_Detail2Combo_t{};
DetailCombo_t g_DetailCombo_t{};
DisableShadows_t g_DisableShadows_t{};
Disposition_t g_Disposition_t{};
DoorState_t g_DoorState_t{};
DynamicContinuousContactBehavior_t g_DynamicContinuousContactBehavior_t{};
EContributionScoreFlag_t g_EContributionScoreFlag_t{};
EDemoBoneSelectionMode g_EDemoBoneSelectionMode{};
EDestructiblePartDamagePassThroughType g_EDestructiblePartDamagePassThroughType{};
EDestructiblePartRadiusDamageApplyType g_EDestructiblePartRadiusDamageApplyType{};
EDestructibleParts_DestroyParameterFlags g_EDestructibleParts_DestroyParameterFlags{};
EIKEndEffectorRotationFixUpMode g_EIKEndEffectorRotationFixUpMode{};
EInButtonState g_EInButtonState{};
EKillTypes_t g_EKillTypes_t{};
EMidiNote g_EMidiNote{};
EMode_t g_EMode_t{};
ENPCBehaviorOverride_t g_ENPCBehaviorOverride_t{};
EOverrideBlockLOS_t g_EOverrideBlockLOS_t{};
EProceduralRagdollWeightIndexPropagationMethod g_EProceduralRagdollWeightIndexPropagationMethod{};
EPulseGraphExecutionHistoryFlag g_EPulseGraphExecutionHistoryFlag{};
ESceneObjectVisualization g_ESceneObjectVisualization{};
ESceneRequestState_t g_ESceneRequestState_t{};
ESceneViewDebugOverlaysListenerDataType_t g_ESceneViewDebugOverlaysListenerDataType_t{};
ESilhouetteType_t g_ESilhouetteType_t{};
EWaveform g_EWaveform{};
EntFinderMethod_t g_EntFinderMethod_t{};
EntityAttachmentType_t g_EntityAttachmentType_t{};
EntityDisolveType_t g_EntityDisolveType_t{};
EntityDistanceMode_t g_EntityDistanceMode_t{};
EntityDormancyType_t g_EntityDormancyType_t{};
EntityEffects_t g_EntityEffects_t{};
EntityIOTargetType_t g_EntityIOTargetType_t{};
EntityPlatformTypes_t g_EntityPlatformTypes_t{};
EntitySubclassScope_t g_EntitySubclassScope_t{};
EventTypeSelection_t g_EventTypeSelection_t{};
Explosions g_Explosions{};
ExternalAnimGraphInactiveBehavior_t g_ExternalAnimGraphInactiveBehavior_t{};
FacingMode g_FacingMode{};
FieldNetworkOption g_FieldNetworkOption{};
FixAngleSet_t g_FixAngleSet_t{};
Flags_t g_Flags_t{};
FlexOpCode_t g_FlexOpCode_t{};
FootFallTagFoot_t g_FootFallTagFoot_t{};
FootLockSubVisualization g_FootLockSubVisualization{};
FootPinningTimingSource g_FootPinningTimingSource{};
FootstepJumpPhase_t g_FootstepJumpPhase_t{};
FootstepLandedFootSoundType_t g_FootstepLandedFootSoundType_t{};
ForcedCrouchState_t g_ForcedCrouchState_t{};
FuncDoorSpawnPos_t g_FuncDoorSpawnPos_t{};
FuncMoverMovementSummaryFlags_t g_FuncMoverMovementSummaryFlags_t{};
FuseVariableAccess_t g_FuseVariableAccess_t{};
FuseVariableType_t g_FuseVariableType_t{};
GLOBALESTATE g_GLOBALESTATE{};
GPUParticleCollisionMode_t g_GPUParticleCollisionMode_t{};
GameAnimEventIndex_t g_GameAnimEventIndex_t{};
GrenadeType_t g_GrenadeType_t{};
HandshakeTagState_t g_HandshakeTagState_t{};
HandshakeTagType_t g_HandshakeTagType_t{};
HierarchyType_t g_HierarchyType_t{};
HitboxLerpType_t g_HitboxLerpType_t{};
HorizJustification_e g_HorizJustification_e{};
HoverPoseFlags_t g_HoverPoseFlags_t{};
Hull_t g_Hull_t{};
IChoreoServices__ChoreoState_t g_IChoreoServices__ChoreoState_t{};
IChoreoServices__ScriptState_t g_IChoreoServices__ScriptState_t{};
IKChannelMode g_IKChannelMode{};
IKSolverType g_IKSolverType{};
IKTargetCoordinateSystem g_IKTargetCoordinateSystem{};
IKTargetSource g_IKTargetSource{};
INavObstacle__NavObstacleType_t g_INavObstacle__NavObstacleType_t{};
IkEndEffectorType g_IkEndEffectorType{};
IkTargetType g_IkTargetType{};
InheritableBoolType_t g_InheritableBoolType_t{};
InputBitMask_t g_InputBitMask_t{};
InputLayoutVariation_t g_InputLayoutVariation_t{};
InteractionPassive_t g_InteractionPassive_t{};
InteractionPriority_t g_InteractionPriority_t{};
ItemFlagTypes_t g_ItemFlagTypes_t{};
JiggleBoneSimSpace g_JiggleBoneSimSpace{};
JointAxis_t g_JointAxis_t{};
JointMotion_t g_JointMotion_t{};
JumpCorrectionMethod g_JumpCorrectionMethod{};
LatchDirtyPermission_t g_LatchDirtyPermission_t{};
LayoutPositionType_e g_LayoutPositionType_e{};
LessonPanelLayoutFileTypes_t g_LessonPanelLayoutFileTypes_t{};
LifeState_t g_LifeState_t{};
LinearRootMotionBlendMode_t g_LinearRootMotionBlendMode_t{};
MaterialProxyType_t g_MaterialProxyType_t{};
Materials g_Materials{};
MatterialAttributeTagType_t g_MatterialAttributeTagType_t{};
MedalRank_t g_MedalRank_t{};
MeshDrawPrimitiveFlags_t g_MeshDrawPrimitiveFlags_t{};
MissingParentInheritBehavior_t g_MissingParentInheritBehavior_t{};
ModelBoneFlexComponent_t g_ModelBoneFlexComponent_t{};
ModelConfigAttachmentType_t g_ModelConfigAttachmentType_t{};
ModelHitboxType_t g_ModelHitboxType_t{};
ModelMeshBufferUsage_t g_ModelMeshBufferUsage_t{};
ModelSkeletonData_t__BoneFlags_t g_ModelSkeletonData_t__BoneFlags_t{};
ModifyDamageReturn_t g_ModifyDamageReturn_t{};
MoodType_t g_MoodType_t{};
MorphBundleType_t g_MorphBundleType_t{};
MorphFlexControllerRemapType_t g_MorphFlexControllerRemapType_t{};
MoveLinearAuthoredPos_t g_MoveLinearAuthoredPos_t{};
MoveMountingAmount_t g_MoveMountingAmount_t{};
MovementCapability_t g_MovementCapability_t{};
NPCFollowFormation_t g_NPCFollowFormation_t{};
NPCPhysicsHullType_t g_NPCPhysicsHullType_t{};
NavAttributeEnum g_NavAttributeEnum{};
NavDirType g_NavDirType{};
NavScopeFlags_t g_NavScopeFlags_t{};
NavScope_t g_NavScope_t{};
NmCachedValueMode_t g_NmCachedValueMode_t{};
NmEasingFunction_t g_NmEasingFunction_t{};
NmEasingOperation_t g_NmEasingOperation_t{};
NmEventConditionRules_t g_NmEventConditionRules_t{};
NmFollowBoneMode_t g_NmFollowBoneMode_t{};
NmFootPhaseCondition_t g_NmFootPhaseCondition_t{};
NmFootPhase_t g_NmFootPhase_t{};
NmFrameSnapEventMode_t g_NmFrameSnapEventMode_t{};
NmGraphDebugMode_t g_NmGraphDebugMode_t{};
NmGraphEventTypeCondition_t g_NmGraphEventTypeCondition_t{};
NmGraphValueType_t g_NmGraphValueType_t{};
NmIKBlendMode_t g_NmIKBlendMode_t{};
NmPoseBlendMode_t g_NmPoseBlendMode_t{};
NmRootMotionBlendMode_t g_NmRootMotionBlendMode_t{};
NmTargetWarpAlgorithm_t g_NmTargetWarpAlgorithm_t{};
NmTargetWarpRule_t g_NmTargetWarpRule_t{};
NmTransitionRuleCondition_t g_NmTransitionRuleCondition_t{};
NmTransitionRule_t g_NmTransitionRule_t{};
ObjectTypeFlags_t g_ObjectTypeFlags_t{};
ObserverInterpState_t g_ObserverInterpState_t{};
ObserverMode_t g_ObserverMode_t{};
OnFrame g_OnFrame{};
OrientationWarpMode_t g_OrientationWarpMode_t{};
OrientationWarpRootMotionSource_t g_OrientationWarpRootMotionSource_t{};
OrientationWarpTargetOffsetMode_t g_OrientationWarpTargetOffsetMode_t{};
PFNoiseModifier_t g_PFNoiseModifier_t{};
PFNoiseTurbulence_t g_PFNoiseTurbulence_t{};
PFNoiseType_t g_PFNoiseType_t{};
PFuncVisualizationType_t g_PFuncVisualizationType_t{};
ParticleAlphaReferenceType_t g_ParticleAlphaReferenceType_t{};
ParticleAttachment_t g_ParticleAttachment_t{};
ParticleAttrBoxFlags_t g_ParticleAttrBoxFlags_t{};
ParticleCollisionGroup_t g_ParticleCollisionGroup_t{};
ParticleCollisionMask_t g_ParticleCollisionMask_t{};
ParticleCollisionMode_t g_ParticleCollisionMode_t{};
ParticleColorBlendMode_t g_ParticleColorBlendMode_t{};
ParticleColorBlendType_t g_ParticleColorBlendType_t{};
ParticleControlPointAxis_t g_ParticleControlPointAxis_t{};
ParticleDepthFeatheringMode_t g_ParticleDepthFeatheringMode_t{};
ParticleDetailLevel_t g_ParticleDetailLevel_t{};
ParticleDirectionNoiseType_t g_ParticleDirectionNoiseType_t{};
ParticleEndcapMode_t g_ParticleEndcapMode_t{};
ParticleEntityPos_t g_ParticleEntityPos_t{};
ParticleFalloffFunction_t g_ParticleFalloffFunction_t{};
ParticleFanType_t g_ParticleFanType_t{};
ParticleFloatBiasType_t g_ParticleFloatBiasType_t{};
ParticleFloatInputMode_t g_ParticleFloatInputMode_t{};
ParticleFloatMapType_t g_ParticleFloatMapType_t{};
ParticleFloatRandomMode_t g_ParticleFloatRandomMode_t{};
ParticleFloatRoundType_t g_ParticleFloatRoundType_t{};
ParticleFloatType_t g_ParticleFloatType_t{};
ParticleFogType_t g_ParticleFogType_t{};
ParticleHitboxBiasType_t g_ParticleHitboxBiasType_t{};
ParticleHitboxDataSelection_t g_ParticleHitboxDataSelection_t{};
ParticleImpulseType_t g_ParticleImpulseType_t{};
ParticleLightBehaviorChoiceList_t g_ParticleLightBehaviorChoiceList_t{};
ParticleLightFogLightingMode_t g_ParticleLightFogLightingMode_t{};
ParticleLightTypeChoiceList_t g_ParticleLightTypeChoiceList_t{};
ParticleLightUnitChoiceList_t g_ParticleLightUnitChoiceList_t{};
ParticleLightingQuality_t g_ParticleLightingQuality_t{};
ParticleLightnintBranchBehavior_t g_ParticleLightnintBranchBehavior_t{};
ParticleLiquidContents_t g_ParticleLiquidContents_t{};
ParticleMassMode_t g_ParticleMassMode_t{};
ParticleModelType_t g_ParticleModelType_t{};
ParticleMultiSegmentCountSelection_t g_ParticleMultiSegmentCountSelection_t{};
ParticleMultiSegmentInputSelection_t g_ParticleMultiSegmentInputSelection_t{};
ParticleMultiSegmentSpecialCharacter_t g_ParticleMultiSegmentSpecialCharacter_t{};
ParticleOmni2LightTypeChoiceList_t g_ParticleOmni2LightTypeChoiceList_t{};
ParticleOrientationChoiceList_t g_ParticleOrientationChoiceList_t{};
ParticleOrientationSetMode_t g_ParticleOrientationSetMode_t{};
ParticleOrientationType_t g_ParticleOrientationType_t{};
ParticleOutputBlendMode_t g_ParticleOutputBlendMode_t{};
ParticleParentSetMode_t g_ParticleParentSetMode_t{};
ParticlePinDistance_t g_ParticlePinDistance_t{};
ParticlePostProcessPriorityGroup_t g_ParticlePostProcessPriorityGroup_t{};
ParticleReplicationMode_t g_ParticleReplicationMode_t{};
ParticleRotationLockType_t g_ParticleRotationLockType_t{};
ParticleSelection_t g_ParticleSelection_t{};
ParticleSequenceCropOverride_t g_ParticleSequenceCropOverride_t{};
ParticleSetMethod_t g_ParticleSetMethod_t{};
ParticleSortingChoiceList_t g_ParticleSortingChoiceList_t{};
ParticleTextureLayerBlendType_t g_ParticleTextureLayerBlendType_t{};
ParticleToolsState_t g_ParticleToolsState_t{};
ParticleTopology_t g_ParticleTopology_t{};
ParticleTraceMissBehavior_t g_ParticleTraceMissBehavior_t{};
ParticleTraceSet_t g_ParticleTraceSet_t{};
ParticleTransformType_t g_ParticleTransformType_t{};
ParticleVRHandChoiceList_t g_ParticleVRHandChoiceList_t{};
ParticleVecType_t g_ParticleVecType_t{};
ParticleVolumetricSmokeCreationType_t g_ParticleVolumetricSmokeCreationType_t{};
ParticleVolumetricSmokeType_t g_ParticleVolumetricSmokeType_t{};
PerformanceMode_t g_PerformanceMode_t{};
PermModelInfo_t__FlagEnum g_PermModelInfo_t__FlagEnum{};
PetGroundType_t g_PetGroundType_t{};
PhysGenericShapeType_t g_PhysGenericShapeType_t{};
PhysInterfaceId_t g_PhysInterfaceId_t{};
PlayBackMode_t g_PlayBackMode_t{};
PlayerConnectedState g_PlayerConnectedState{};
PointOrientConstraint_t g_PointOrientConstraint_t{};
PointOrientGoalDirectionType_t g_PointOrientGoalDirectionType_t{};
PointTemplateClientOnlyEntityBehavior_t g_PointTemplateClientOnlyEntityBehavior_t{};
PointTemplateOwnerSpawnGroupType_t g_PointTemplateOwnerSpawnGroupType_t{};
PointWorldTextJustifyHorizontal_t g_PointWorldTextJustifyHorizontal_t{};
PointWorldTextJustifyVertical_t g_PointWorldTextJustifyVertical_t{};
PointWorldTextReorientMode_t g_PointWorldTextReorientMode_t{};
PoseType_t g_PoseType_t{};
PreviewCharacterBannerAnimation g_PreviewCharacterBannerAnimation{};
PreviewCharacterMode g_PreviewCharacterMode{};
PreviewEOMCelebration g_PreviewEOMCelebration{};
PreviewWeaponState g_PreviewWeaponState{};
PropDoorRotatingOpenDirection_e g_PropDoorRotatingOpenDirection_e{};
PropDoorRotatingSpawnPos_t g_PropDoorRotatingSpawnPos_t{};
PulseApiFeature_t g_PulseApiFeature_t{};
PulseBestOutflowRules_t g_PulseBestOutflowRules_t{};
PulseCollisionGroup_t g_PulseCollisionGroup_t{};
PulseCursorCancelPriority_t g_PulseCursorCancelPriority_t{};
PulseCursorExecResult_t g_PulseCursorExecResult_t{};
PulseDomainValueType_t g_PulseDomainValueType_t{};
PulseInstructionCode_t g_PulseInstructionCode_t{};
PulseMethodCallMode_t g_PulseMethodCallMode_t{};
PulseNPCCondition_t g_PulseNPCCondition_t{};
PulseTestEnumColor_t g_PulseTestEnumColor_t{};
PulseTestEnumShape_t g_PulseTestEnumShape_t{};
PulseTraceContents_t g_PulseTraceContents_t{};
PulseValueType_t g_PulseValueType_t{};
PulseVariableKeysSource_t g_PulseVariableKeysSource_t{};
QuestProgress__Reason g_QuestProgress__Reason{};
RTProxyInstanceFlags_t g_RTProxyInstanceFlags_t{};
RagdollPoseControl g_RagdollPoseControl{};
RelativeLocationType_t g_RelativeLocationType_t{};
RenderBufferFlags_t g_RenderBufferFlags_t{};
RenderMeshSlotType_t g_RenderMeshSlotType_t{};
RenderModelSubModelFieldType_t g_RenderModelSubModelFieldType_t{};
RenderMultisampleType_t g_RenderMultisampleType_t{};
RenderPrimitiveType_t g_RenderPrimitiveType_t{};
RenderSlotType_t g_RenderSlotType_t{};
ResetCycleOption g_ResetCycleOption{};
RotatorTargetSpace_t g_RotatorTargetSpace_t{};
RsComparison_t g_RsComparison_t{};
RsCullMode_t g_RsCullMode_t{};
RsFillMode_t g_RsFillMode_t{};
RumbleEffect_t g_RumbleEffect_t{};
SaveRestoreTableFlags_t g_SaveRestoreTableFlags_t{};
ScalarExpressionType_t g_ScalarExpressionType_t{};
SceneOnPlayerDeath_t g_SceneOnPlayerDeath_t{};
ScriptedConflictResponse_t g_ScriptedConflictResponse_t{};
ScriptedHeldWeaponBehavior_t g_ScriptedHeldWeaponBehavior_t{};
ScriptedMoveTo_t g_ScriptedMoveTo_t{};
ScriptedOnDeath_t g_ScriptedOnDeath_t{};
SelectorTagBehavior_t g_SelectorTagBehavior_t{};
SeqCmd_t g_SeqCmd_t{};
SeqPoseSetting_t g_SeqPoseSetting_t{};
SequenceFinishNotifyState_t g_SequenceFinishNotifyState_t{};
SetStatisticExpressionType_t g_SetStatisticExpressionType_t{};
ShadowType_t g_ShadowType_t{};
ShakeCommand_t g_ShakeCommand_t{};
ShardSolid_t g_ShardSolid_t{};
SharedMovementGait_t g_SharedMovementGait_t{};
ShatterDamageCause g_ShatterDamageCause{};
ShatterGlassStressType g_ShatterGlassStressType{};
SnapshotIndexType_t g_SnapshotIndexType_t{};
SndSeqInstrumentType_t g_SndSeqInstrumentType_t{};
SndSeqMidiStatusType_t g_SndSeqMidiStatusType_t{};
SndSeqPlayerType_t g_SndSeqPlayerType_t{};
SndSeqQuantizeType_t g_SndSeqQuantizeType_t{};
SndSeqRegionType_t g_SndSeqRegionType_t{};
SndSeqSyncType_t g_SndSeqSyncType_t{};
SndSeqTrackPlaybackType_t g_SndSeqTrackPlaybackType_t{};
SolveIKChainAnimNodeDebugSetting g_SolveIKChainAnimNodeDebugSetting{};
SosActionLimitSortType_t g_SosActionLimitSortType_t{};
SosActionSetParamSortType_t g_SosActionSetParamSortType_t{};
SosActionStopType_t g_SosActionStopType_t{};
SosEditItemType_t g_SosEditItemType_t{};
SosGroupFieldBehavior_t g_SosGroupFieldBehavior_t{};
SosGroupType_t g_SosGroupType_t{};
SoundEventStartType_t g_SoundEventStartType_t{};
SpriteCardPerParticleScale_t g_SpriteCardPerParticleScale_t{};
SpriteCardShaderType_t g_SpriteCardShaderType_t{};
SpriteCardTextureChannel_t g_SpriteCardTextureChannel_t{};
SpriteCardTextureType_t g_SpriteCardTextureType_t{};
StanceOverrideMode g_StanceOverrideMode{};
StanceType_t g_StanceType_t{};
StandardLightingAttenuationStyle_t g_StandardLightingAttenuationStyle_t{};
StateActionBehavior g_StateActionBehavior{};
StepPhase g_StepPhase{};
SubclassVDataChangeType_t g_SubclassVDataChangeType_t{};
SurroundingBoundsType_t g_SurroundingBoundsType_t{};
TOGGLE_STATE g_TOGGLE_STATE{};
TRAIN_CODE g_TRAIN_CODE{};
TakeDamageFlags_t g_TakeDamageFlags_t{};
TargetSelectorAngleMode_t g_TargetSelectorAngleMode_t{};
TargetWarpAngleMode_t g_TargetWarpAngleMode_t{};
TargetWarpCorrectionMethod g_TargetWarpCorrectionMethod{};
TargetWarpTimingMethod g_TargetWarpTimingMethod{};
TestInputOutputCombinationsEnum_t g_TestInputOutputCombinationsEnum_t{};
TextureRepetitionMode_t g_TextureRepetitionMode_t{};
ThreeState_t g_ThreeState_t{};
TimelineCompression_t g_TimelineCompression_t{};
Touch_t g_Touch_t{};
TrackOrientationType_t g_TrackOrientationType_t{};
TrainOrientationType_t g_TrainOrientationType_t{};
TrainVelocityType_t g_TrainVelocityType_t{};
VMixChannelOperation_t g_VMixChannelOperation_t{};
VMixFilterSlope_t g_VMixFilterSlope_t{};
VMixFilterType_t g_VMixFilterType_t{};
VMixGraphCommandID_t g_VMixGraphCommandID_t{};
VMixLFOShape_t g_VMixLFOShape_t{};
VMixPannerType_t g_VMixPannerType_t{};
VMixSubgraphSwitchInterpolationType_t g_VMixSubgraphSwitchInterpolationType_t{};
VPhysXAggregateData_t__VPhysXFlagEnum_t g_VPhysXAggregateData_t__VPhysXFlagEnum_t{};
VPhysXBodyPart_t__VPhysXFlagEnum_t g_VPhysXBodyPart_t__VPhysXFlagEnum_t{};
VPhysXConstraintParams_t__EnumFlags0_t g_VPhysXConstraintParams_t__EnumFlags0_t{};
VPhysXJoint_t__Flags_t g_VPhysXJoint_t__Flags_t{};
ValueRemapperHapticsType_t g_ValueRemapperHapticsType_t{};
ValueRemapperInputType_t g_ValueRemapperInputType_t{};
ValueRemapperMomentumType_t g_ValueRemapperMomentumType_t{};
ValueRemapperOutputType_t g_ValueRemapperOutputType_t{};
ValueRemapperRatchetType_t g_ValueRemapperRatchetType_t{};
VectorExpressionType_t g_VectorExpressionType_t{};
VectorFloatExpressionType_t g_VectorFloatExpressionType_t{};
VelocityMetricMode g_VelocityMetricMode{};
VertJustification_e g_VertJustification_e{};
VertexAlbedoFormat_t g_VertexAlbedoFormat_t{};
ViewFadeMode_t g_ViewFadeMode_t{};
WaterLevel_t g_WaterLevel_t{};
WeaponAttackType_t g_WeaponAttackType_t{};
WeaponGameplayAnimState g_WeaponGameplayAnimState{};
WeaponSound_t g_WeaponSound_t{};
WeaponSwitchReason_t g_WeaponSwitchReason_t{};
WorldTextPanelHorizontalAlign_t g_WorldTextPanelHorizontalAlign_t{};
WorldTextPanelOrientation_t g_WorldTextPanelOrientation_t{};
WorldTextPanelVerticalAlign_t g_WorldTextPanelVerticalAlign_t{};
attributeprovidertypes_t g_attributeprovidertypes_t{};
doorCheck_e g_doorCheck_e{};
eSplinePushType g_eSplinePushType{};
fieldtype_t g_fieldtype_t{};
filter_t g_filter_t{};
gear_slot_t g_gear_slot_t{};
loadout_slot_t g_loadout_slot_t{};
navproperties_t g_navproperties_t{};
soundcommands_t g_soundcommands_t{};
soundlevel_t g_soundlevel_t{};
vote_create_failed_t g_vote_create_failed_t{};

Plugin::Plugin() :
    m_pGameServerSteamAPIActivated(new KHook::Virtual(&ISource2Server::GameServerSteamAPIActivated, this, &Plugin::CSource2Server_GameServerSteamAPIActivated, nullptr)),
    m_pSendMessage(new KHook::Virtual(&ISteamGameCoordinator::SendMessage, this, &Plugin::ISteamGameCoordinator_SendMessage, nullptr)),
    m_pIsMessageAvailable(new KHook::Virtual(&ISteamGameCoordinator::IsMessageAvailable, this, &Plugin::ISteamGameCoordinator_IsMessageAvailable, nullptr)),
    m_pRetrieveMessage(new KHook::Virtual(&ISteamGameCoordinator::RetrieveMessage, this, &Plugin::ISteamGameCoordinator_RetrieveMessage, nullptr)),
    m_pRunCallbacks(new KHook::Function(this, &Plugin::ISteamGameServer_RunCallbacks, nullptr)),
    m_pRegisterCallback(new KHook::Function(this, &Plugin::ISteamGameServer_RegisterCallback, nullptr)),
    m_pUnregisterCallback(new KHook::Function(this, &Plugin::ISteamGameServer_UnregisterCallback, nullptr))
{
    g_ppGameCoordinatorCallbackCapture = &g_pGameCoordinatorMessageAvailableCallback;
}

bool Plugin::Load(PluginId id, IToolkitAPI* api, char* error, size_t maxlen, bool late)
{
    TOOLKIT_SAVEVARS();

    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pEngineServer, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pCVar, ICvar, CVAR_INTERFACE_VERSION);
    GET_VALVE_IFACE_CURRENT(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
    GET_VALVE_IFACE_CURRENT(GetFileSystemFactory, g_pFullFileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);
    GET_VALVE_IFACE_ANY(GetServerFactory, g_pSource2Server, ISource2Server, INTERFACEVERSION_SERVERGAMEDLL);
    GET_VALVE_IFACE_ANY(GetServerFactory, g_pSource2GameClients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
    GET_VALVE_IFACE_ANY(GetEngineFactory, g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);
    GET_VALVE_IFACE_ANY(GetEngineFactory, g_pSchemaSystem, CSchemaSystem, SCHEMASYSTEM_INTERFACE_VERSION);
    GET_VALVE_IFACE_ANY(GetEngineFactory, g_pGameEventSystem, IGameEventSystem, GAMEEVENTSYSTEM_INTERFACE_VERSION);
    GET_VALVE_IFACE_ANY(GetEngineFactory, g_pNetworkMessages, INetworkMessages, NETWORKMESSAGES_INTERFACE_VERSION);
    GET_VALVE_IFACE_ANY(GetServerFactory, g_pSource2GameEntities, ISource2GameEntities, SOURCE2GAMEENTITIES_INTERFACE_VERSION);

    api->AddListener(this, this);

    // Function hooks
    {
        m_pGameServerSteamAPIActivated->Add(g_pSource2Server);

        g_pLibSteamApi = IToolkitModule::New("steam_api");
        if (g_pLibSteamApi)
        {
            m_pRunCallbacks->Configure(g_pLibSteamApi->GetFunctionByName("SteamGameServer_RunCallbacks").RCast<void(*)()>());
            m_pRegisterCallback->Configure(g_pLibSteamApi->GetFunctionByName("SteamAPI_RegisterCallback").RCast<void(*)(CCallbackBase*, int)>());
            m_pUnregisterCallback->Configure(g_pLibSteamApi->GetFunctionByName("SteamAPI_UnregisterCallback").RCast<void(*)(CCallbackBase*)>());
        }

        if (late)
        {
            g_pSteamGameCoordinator = SteamGameCoordinator();
            if (g_pSteamGameCoordinator)
            {
                m_pSendMessage->Add(g_pSteamGameCoordinator);
                m_pIsMessageAvailable->Add(g_pSteamGameCoordinator);
                m_pRetrieveMessage->Add(g_pSteamGameCoordinator);
            }
        }
    }

    TOOLKIT_LOG(this, "Load( id=%d, api=%p, late=%d ) done\n", id, api, late);

    return true;
}

bool Plugin::Unload(char* error, size_t maxlen)
{
    m_pGameServerSteamAPIActivated->Remove(g_pSource2Server);
    m_pSendMessage->Remove(g_pSteamGameCoordinator);
    m_pIsMessageAvailable->Remove(g_pSteamGameCoordinator);
    m_pRetrieveMessage->Remove(g_pSteamGameCoordinator);

    delete m_pRunCallbacks;
    delete m_pRegisterCallback;
    delete m_pUnregisterCallback;

    delete g_pLibSteamApi;

    TOOLKIT_LOG(this, "Unload() done\n");

    return true;
}

void Plugin::OnPluginLoad(PluginId id)
{
    TOOLKIT_LOG(this, "OnPluginLoad( id=%d )\n", id);
}

void Plugin::OnPluginUnload(PluginId id)
{
    TOOLKIT_LOG(this, "OnPluginUnload( id=%d )\n", id);
}

void Plugin::OnAllToolkitPluginsLoaded()
{
    TOOLKIT_LOG(this, "OnAllToolkitPluginsLoaded()\n");
}

void Plugin::OnAllMetamodPluginsLoaded()
{
    TOOLKIT_LOG(this, "OnAllMetamodPluginsLoaded()\n");
}

void Plugin::OnLevelInit(const char* mapName, const char* mapEntities, const char* oldLevel, const char* landmarkName, bool loadGame, bool background)
{
    TOOLKIT_LOG(this, "OnLevelInit( map=%s, old=%s, landmark=%s, loadGame=%d, background=%d )\n", mapName ? mapName : "nullptr", oldLevel ? oldLevel : "nullptr", landmarkName ? landmarkName : "nullptr", loadGame, background);
}

void Plugin::OnLevelShutdown()
{
    TOOLKIT_LOG(this, "OnLevelShutdown()\n");
}

std::optional<std::pair<uint32_t, std::string>> Plugin::CreateGCSendProto(uint32_t type, google::protobuf::Message& msg, CMsgProtoBufHeader* pHeader)
{
    CMsgProtoBufHeader defaultHdr;
    CMsgProtoBufHeader& hdr = pHeader ? *pHeader : defaultHdr;

    size_t hdrSize = hdr.ByteSizeLong();
    size_t bodySize = msg.ByteSizeLong();
    std::string s(sizeof(uint32_t) * 2 + hdrSize + bodySize, '\0');

    *reinterpret_cast<uint32_t*>(s.data()) = type | 0x80000000u;
    *reinterpret_cast<uint32_t*>(s.data() + sizeof(uint32_t)) = static_cast<uint32_t>(hdrSize);

    if (!hdr.SerializeToArray(s.data() + sizeof(uint32_t) * 2, static_cast<int>(hdrSize)))
        return std::nullopt;
    if (!msg.SerializeToArray(s.data() + sizeof(uint32_t) * 2 + hdrSize, static_cast<int>(bodySize)))
        return std::nullopt;

    return std::make_pair(type | 0x80000000u, std::move(s));
}

void Plugin::QueueGCMessage(uint32_t type, google::protobuf::Message& msg, CMsgProtoBufHeader* pHeader)
{
    if (auto send = CreateGCSendProto(type, msg, pHeader))
    {
        g_vecGameCoordinatorPending.push_back(std::move(send.value()));
        TriggerGCCallback();
    }
}

void Plugin::TriggerGCCallback()
{
    if (!g_pGameCoordinatorMessageAvailableCallback || g_vecGameCoordinatorPending.empty())
        return;

    GCMessageAvailable_t msg;
    msg.m_nMessageSize = static_cast<uint32>(g_vecGameCoordinatorPending.front().second.size());
    g_pGameCoordinatorMessageAvailableCallback->Run(&msg);
}

KHook::Return<void> Plugin::CSource2Server_GameServerSteamAPIActivated(ISource2Server* pThis)
{
    TOOLKIT_LOG(this, "CSource2Server_GameServerSteamAPIActivated( pThis=%p )\n", pThis);

    g_pSteamAPI = new CSteamGameServerAPIContext();
    g_pSteamAPI->Init();

    g_pSteamGameCoordinator = SteamGameCoordinator();
    TOOLKIT_LOG(
        this,
        "CSource2Server_GameServerSteamAPIActivated: g_pSteamAPI=%p, g_pLibSteamApi=%p, g_pSteamGameCoordinator=%p\n",
        g_pSteamAPI, g_pLibSteamApi ? g_pLibSteamApi->GetModuleHandle() : nullptr, g_pSteamGameCoordinator);

    if (g_pSteamGameCoordinator)
    {
        m_pSendMessage->Add(g_pSteamGameCoordinator);
        m_pIsMessageAvailable->Add(g_pSteamGameCoordinator);
        m_pRetrieveMessage->Add(g_pSteamGameCoordinator);
    }

    return {KHook::Action::Ignore};
}

KHook::Return<void> Plugin::ISteamGameServer_RunCallbacks()
{
    // TOOLKIT_LOG(this, "ISteamGameServer_RunCallbacks()\n");

    if (!g_vecGameCoordinatorPending.empty())
        TriggerGCCallback();

    return {KHook::Action::Ignore};
}

KHook::Return<void> Plugin::ISteamGameServer_RegisterCallback(CCallbackBase* pCallback, int iCallback)
{
    TOOLKIT_LOG(this, "ISteamGameServer_RegisterCallback( pCallback=%p, iCallback=%d )\n", pCallback, iCallback);

    if (iCallback == GCMessageAvailable_t::k_iCallback && g_ppGameCoordinatorCallbackCapture)
        *g_ppGameCoordinatorCallbackCapture = pCallback;

    return {KHook::Action::Ignore};
}

KHook::Return<void> Plugin::ISteamGameServer_UnregisterCallback(CCallbackBase* pCallback)
{
    TOOLKIT_LOG(this, "ISteamGameServer_UnregisterCallback( pCallback=%p )\n", pCallback);

    if (pCallback == *g_ppGameCoordinatorCallbackCapture)
        *g_ppGameCoordinatorCallbackCapture = nullptr;

    return {KHook::Action::Supersede};
}

KHook::Return<EGCResults> Plugin::ISteamGameCoordinator_SendMessage(ISteamGameCoordinator* pThis, uint32 unMsgType, const void* pubData, uint32 cubData)
{
    uint32 realType = unMsgType & ~0x80000000u;
    bool isProto = (unMsgType & 0x80000000u) != 0;
    TOOLKIT_LOG(this, "ISteamGameCoordinator_SendMessage( type=%u (0x%X), proto=%d, size=%u )\n", realType, realType, isProto, cubData);

    //    CMsgProtoBufHeader header;
    // if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCEnterMatchmaking, CMsgServerToGCEnterMatchmaking>(unMsgType, pubData, cubData, header))
    // {
    // 	Msg("CMsgServerToGCEnterMatchmaking (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
    //
    // 	if (object_cache.sent_lobby)
    // 	{
    // 		for (int i = 0; i < 5; i++)
    // 			Msg("Received k_EMsgServerToGCEnterMatchmaking but lobby already sent prior");
    // 		return k_EGCResultOK;
    // 	}
    // 	object_cache.sent_lobby = true;
    //
    // 	if (!ParseMatchInformation())
    // 	{
    // 		// Already logged
    // 		return k_EGCResultOK;
    // 	}
    //
    // 	// Create an object cache on the server with our data
    // 	{
    // 		CMsgSOSingleObject msg;
    // 		msg.set_type_id(ObjectCache::Lobby);
    // 		msg.set_object_data(object_cache.lobby.SerializeAsString());
    // 		msg.set_version(GetRandom(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max()));
    // 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
    // 		{
    // 			owner->set_type(1);
    // 			owner->set_id(GetServerSteamID());
    // 		}
    // 		if (auto send = CreateGCSendProto(k_ESOMsg_Create, msg))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	{
    // 		CMsgSOSingleObject msg;
    // 		msg.set_type_id(ObjectCache::ServerStaticLobby);
    // 		msg.set_object_data(object_cache.static_lobby.SerializeAsString());
    // 		msg.set_version(GetRandom(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max()));
    // 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
    // 		{
    // 			owner->set_type(1);
    // 			owner->set_id(GetServerSteamID());
    // 		}
    // 		if (auto send = CreateGCSendProto(k_ESOMsg_Create, msg))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	{
    // 		CMsgSOSingleObject msg;
    // 		msg.set_type_id(ObjectCache::ServerDynamicLobby);
    // 		msg.set_object_data(object_cache.dynamic_lobby.SerializeAsString());
    // 		msg.set_version(GetRandom(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max()));
    // 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
    // 		{
    // 			owner->set_type(1);
    // 			owner->set_id(GetServerSteamID());
    // 		}
    // 		if (auto send = CreateGCSendProto(k_ESOMsg_Create, msg))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	return k_EGCResultOK;
    // }
    // else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCUpdateLobbyServerState, CMsgServerToGCUpdateLobbyServerState>(unMsgType, pubData, cubData, header))
    // {
    // 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCUpdateLobbyServerState (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
    //
    // 	bool didUpdate = false;
    // 	if (msg->lobby_id() == object_cache.lobby.lobby_id())
    // 	{
    // 		if (msg->has_server_state())
    // 		{
    // 			object_cache.lobby.set_server_state(msg->server_state());
    // 			didUpdate = true;
    // 		}
    // 		if (msg->has_safe_to_abandon())
    // 		{
    // 			object_cache.lobby.set_safe_to_abandon(msg->safe_to_abandon());
    // 			didUpdate = true;
    // 		}
    // 	}
    //
    // 	// Update the cache
    // 	if (didUpdate)
    // 	{
    // 		CMsgSOSingleObject msg;
    // 		msg.set_type_id(ObjectCache::Lobby);
    // 		msg.set_object_data(object_cache.lobby.SerializeAsString());
    // 		msg.set_version(GetRandom(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max()));
    // 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
    // 		{
    // 			owner->set_type(1);
    // 			owner->set_id(GetServerSteamID());
    // 		}
    // 		if (auto send = CreateGCSendProto(k_ESOMsg_Update, msg))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	return k_EGCResultOK;
    // }
    // else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCMatchSignoutPermission, CMsgServerToGCMatchSignoutPermission>(unMsgType, pubData, cubData, header))
    // {
    // 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCMatchSignoutPermission (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
    //
    // 	uint64_t jobid = header.job_id_source();
    //
    // 	// We just always say yes and request all data
    // 	{
    // 		CMsgProtoBufHeader header;
    // 		header.set_job_id_target(jobid);
    //
    // 		CMsgServerToGCMatchSignoutPermissionResponse msg;
    // 		msg.set_can_sign_out(true);
    // 		msg.add_requested_data(k_EServerSignoutData_Disconnections);
    // 		msg.add_requested_data(k_EServerSignoutData_AccountStatChanges);
    // 		msg.add_requested_data(k_EServerSignoutData_DetailedStats);
    // 		msg.add_requested_data(k_EServerSignoutData_ServerPerfStats);
    // 		msg.add_requested_data(k_EServerSignoutData_PerfData);
    // 		msg.add_requested_data(k_EServerSignoutData_PlayerChat);
    // 		msg.add_requested_data(k_EServerSignoutData_BookRewards);
    // 		msg.add_requested_data(k_EServerSignoutData_PenalizedPlayers);
    // 		if (auto send = CreateGCSendProto(k_EMsgServerToGCMatchSignoutPermissionResponse, msg, header))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	return k_EGCResultOK;
    // }
    // else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCMatchSignout, CMsgServerToGCMatchSignout>(unMsgType, pubData, cubData, header))
    // {
    // 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCMatchSignout (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
    //
    // 	try
    // 	{
    // 		if (std::optional<nlohmann::json> json = MatchSignoutToFullJson(msg.value()))
    // 		{
    // 			std::ofstream f(GetMatchDirectory() / "result.json");
    // 			f << std::setw(4) << json.value();
    // 		}
    // 	}
    // 	catch (const std::exception &ex)
    // 	{
    // 		Msg("Failed to serialize convert 'CMsgServerToGCMatchSignout' to JSON and dump to file: {}, no match stats will be saved", ex.what());
    // 	}
    // 	catch (...)
    // 	{
    // 		Msg("Failed to serialize convert 'CMsgServerToGCMatchSignout' to JSON and dump to file, no match stats will be saved");
    // 	}
    //
    // 	uint64_t jobid = header.job_id_source();
    //
    // 	// Destroy the caches
    // 	{
    // 		CMsgSOSingleObject msg;
    // 		msg.set_type_id(ObjectCache::Lobby);
    // 		msg.set_object_data(object_cache.lobby.SerializeAsString());
    // 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
    // 		{
    // 			owner->set_type(1);
    // 			owner->set_id(GetServerSteamID());
    // 		}
    // 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	{
    // 		CMsgSOSingleObject msg;
    // 		msg.set_type_id(ObjectCache::ServerStaticLobby);
    // 		msg.set_object_data(object_cache.static_lobby.SerializeAsString());
    // 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
    // 		{
    // 			owner->set_type(1);
    // 			owner->set_id(GetServerSteamID());
    // 		}
    // 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	{
    // 		CMsgSOSingleObject msg;
    // 		msg.set_type_id(ObjectCache::ServerDynamicLobby);
    // 		msg.set_object_data(object_cache.dynamic_lobby.SerializeAsString());
    // 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
    // 		{
    // 			owner->set_type(1);
    // 			owner->set_id(GetServerSteamID());
    // 		}
    // 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	{
    // 		CMsgProtoBufHeader header;
    // 		header.set_job_id_target(jobid);
    //
    // 		CMsgServerToGCMatchSignoutResponse msg;
    // 		msg.set_result(CMsgServerToGCMatchSignoutResponse_ESignoutResult_k_ESignout_Success);
    // 		if (auto send = CreateGCSendProto(k_EMsgServerToGCMatchSignoutResponse, msg, header))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    // 	return k_EGCResultOK;
    // }
    // else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCAbandonMatch, CMsgServerToGCAbandonMatch>(unMsgType, pubData, cubData, header))
    // {
    // 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCAbandonMatch (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
    //
    // 	uint64_t jobid = header.job_id_source();
    //
    // 	// Destroy the caches
    // 	{
    // 		CMsgSOSingleObject msg;
    // 		msg.set_type_id(ObjectCache::Lobby);
    // 		msg.set_object_data(object_cache.lobby.SerializeAsString());
    // 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
    // 		{
    // 			owner->set_type(1);
    // 			owner->set_id(GetServerSteamID());
    // 		}
    // 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	{
    // 		CMsgSOSingleObject msg;
    // 		msg.set_type_id(ObjectCache::ServerStaticLobby);
    // 		msg.set_object_data(object_cache.static_lobby.SerializeAsString());
    // 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
    // 		{
    // 			owner->set_type(1);
    // 			owner->set_id(GetServerSteamID());
    // 		}
    // 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	{
    // 		CMsgSOSingleObject msg;
    // 		msg.set_type_id(ObjectCache::ServerDynamicLobby);
    // 		msg.set_object_data(object_cache.dynamic_lobby.SerializeAsString());
    // 		if (CMsgSOIDOwner *owner = msg.mutable_owner_soid())
    // 		{
    // 			owner->set_type(1);
    // 			owner->set_id(GetServerSteamID());
    // 		}
    // 		if (auto send = CreateGCSendProto(k_ESOMsg_Destroy, msg))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	{
    // 		CMsgProtoBufHeader header;
    // 		header.set_job_id_target(jobid);
    //
    // 		CMsgServerToGCAbandonMatchResponse msg;
    // 		if (auto send = CreateGCSendProto(k_EMsgServerToGCAbandonMatchResponse, msg, header))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	return k_EGCResultOK;
    // }
    // else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCTestConnection, CMsgServerToGCTestConnection>(unMsgType, pubData, cubData, header))
    // {
    // 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCTestConnection (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
    //
    // 	uint64_t jobid = header.job_id_source();
    //
    // 	{
    // 		CMsgProtoBufHeader header;
    // 		header.set_job_id_target(jobid);
    //
    // 		CMsgServerToGCTestConnectionResponse msg;
    // 		msg.set_state(object_cache.lobby.server_state());
    // 		msg.set_state(object_cache.lobby.lobby_id());
    // 		if (auto send = CreateGCSendProto(k_EMsgServerToGCTestConnectionResponse, msg, header))
    // 			gc_custom_pending.push_back(send.value());
    // 	}
    //
    // 	return k_EGCResultOK;
    // }
    // else if (auto msg = CheckProtoAndRemoveHeader<k_EMsgServerToGCUpdateMatchInfo, CMsgServerToGCUpdateMatchInfo>(unMsgType, pubData, cubData, header))
    // {
    // 	MsgIf(wantsProtobufDebugLog, "CMsgServerToGCUpdateMatchInfo (Header)\n{}\n(Body)\n{}", header.Utf8DebugString(), msg->Utf8DebugString());
    // 	return k_EGCResultOK;
    // }

    return {KHook::Action::Ignore, k_EGCResultOK};
}

KHook::Return<bool> Plugin::ISteamGameCoordinator_IsMessageAvailable(ISteamGameCoordinator* pThis, uint32* pcubMsgSize)
{
    TOOLKIT_LOG(this, "ISteamGameCoordinator_IsMessageAvailable( pThis=%p, pcubMsgSize=%p )\n", pThis, pcubMsgSize);

    if (!g_vecGameCoordinatorPending.empty())
    {
        if (pcubMsgSize)
            *pcubMsgSize = g_vecGameCoordinatorPending[0].second.size();
        return {KHook::Action::Override, true};
    }

    return {KHook::Action::Ignore, true};
}

KHook::Return<EGCResults> Plugin::ISteamGameCoordinator_RetrieveMessage(ISteamGameCoordinator* pThis, uint32* punMsgType, void* pubDest, uint32 cubDest, uint32* pcubMsgSize)
{
    TOOLKIT_LOG(this, "ISteamGameCoordinator_RetrieveMessage( pThis=%p, punMsgType=%p, pubDest=%p, cubDest=%d, pcubMsgSize=%p )\n", pThis, punMsgType, pubDest, cubDest, pcubMsgSize);

    if (!g_vecGameCoordinatorPending.empty())
    {
        if (punMsgType)
            *punMsgType = g_vecGameCoordinatorPending[0].first;
        if (pcubMsgSize)
            *pcubMsgSize = g_vecGameCoordinatorPending[0].second.size();
        if (cubDest < g_vecGameCoordinatorPending[0].second.size())
            return {KHook::Action::Override, k_EGCResultBufferTooSmall};

        std::memcpy(pubDest, g_vecGameCoordinatorPending[0].second.data(),
                    g_vecGameCoordinatorPending[0].second.size());
        g_vecGameCoordinatorPending.erase(g_vecGameCoordinatorPending.begin());

        return {KHook::Action::Override, k_EGCResultOK};
    }

    return {KHook::Action::Ignore, k_EGCResultOK};
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
