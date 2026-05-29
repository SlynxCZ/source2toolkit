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

#ifndef _INCLUDE_CENVBEAMIMPL_H
#define _INCLUDE_CENVBEAMIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvBeam.h"
#include "schema/entity/classes/CEnvBeam.h"
#include "CBeamImpl.h"

class CEnvBeamImpl : public CBeamImpl, public IEnvBeam
{

public:
    explicit CEnvBeamImpl(CEnvBeam* p) : CBeamImpl(p) {}

private:
    CEnvBeam* Real() { return static_cast<CEnvBeam*>(m_pReal); }
    CEnvBeam* Real() const { return static_cast<CEnvBeam*>(m_pReal); }

public:
    CEnvBeam* GetOriginal() const override { return Real(); }
    int32_t& Active() override { return Real()->m_active(); }
    void ActiveUpdated() override { Real()->m_active.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIMaterial2>& SpriteTexture() override { return Real()->m_spriteTexture(); }
    void SpriteTextureUpdated() override { Real()->m_spriteTexture.NetworkStateChanged(); }
    CUtlSymbolLarge& StartEntity() override { return Real()->m_iszStartEntity(); }
    void StartEntityUpdated() override { Real()->m_iszStartEntity.NetworkStateChanged(); }
    CUtlSymbolLarge& EndEntity() override { return Real()->m_iszEndEntity(); }
    void EndEntityUpdated() override { Real()->m_iszEndEntity.NetworkStateChanged(); }
    float& Life() override { return Real()->m_life(); }
    void LifeUpdated() override { Real()->m_life.NetworkStateChanged(); }
    float& BoltWidth() override { return Real()->m_boltWidth(); }
    void BoltWidthUpdated() override { Real()->m_boltWidth.NetworkStateChanged(); }
    float& NoiseAmplitude() override { return Real()->m_noiseAmplitude(); }
    void NoiseAmplitudeUpdated() override { Real()->m_noiseAmplitude.NetworkStateChanged(); }
    int32_t& Speed() override { return Real()->m_speed(); }
    void SpeedUpdated() override { Real()->m_speed.NetworkStateChanged(); }
    float& Restrike() override { return Real()->m_restrike(); }
    void RestrikeUpdated() override { Real()->m_restrike.NetworkStateChanged(); }
    CUtlSymbolLarge& SpriteName() override { return Real()->m_iszSpriteName(); }
    void SpriteNameUpdated() override { Real()->m_iszSpriteName.NetworkStateChanged(); }
    int32_t& FrameStart() override { return Real()->m_frameStart(); }
    void FrameStartUpdated() override { Real()->m_frameStart.NetworkStateChanged(); }
    Vector& EndPointWorld() override { return Real()->m_vEndPointWorld(); }
    void EndPointWorldUpdated() override { Real()->m_vEndPointWorld.NetworkStateChanged(); }
    Vector& EndPointRelative() override { return Real()->m_vEndPointRelative(); }
    void EndPointRelativeUpdated() override { Real()->m_vEndPointRelative.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_radius(); }
    void RadiusUpdated() override { Real()->m_radius.NetworkStateChanged(); }
    Touch_t& TouchType() override { return Real()->m_TouchType(); }
    void TouchTypeUpdated() override { Real()->m_TouchType.NetworkStateChanged(); }
    CUtlSymbolLarge& FilterName() override { return Real()->m_iFilterName(); }
    void FilterNameUpdated() override { Real()->m_iFilterName.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Filter() override { return Real()->m_hFilter(); }
    void FilterUpdated() override { Real()->m_hFilter.NetworkStateChanged(); }
    CUtlSymbolLarge& Decal() override { return Real()->m_iszDecal(); }
    void DecalUpdated() override { Real()->m_iszDecal.NetworkStateChanged(); }
    CEntityIOOutput& OnTouchedByEntity() override { return Real()->m_OnTouchedByEntity(); }
    void OnTouchedByEntityUpdated() override { Real()->m_OnTouchedByEntity.NetworkStateChanged(); }
};

inline IEnvBeam* CEnvBeam::ToInterface() { return new CEnvBeamImpl(this); }
inline IEnvBeam* IEnvBeam::FromOriginal(CEnvBeam* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENVBEAMIMPL_H
