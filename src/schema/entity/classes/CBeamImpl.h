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

#ifndef _INCLUDE_CBEAMIMPL_H
#define _INCLUDE_CBEAMIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBeam.h"
#include "schema/entity/classes/CBeam.h"
#include "CBaseModelEntityImpl.h"

class CBeamImpl : public CBaseModelEntityImpl, public virtual IBeam
{

public:
    explicit CBeamImpl(CBeam* p) : CBaseModelEntityImpl(p) {}

private:
    CBeam* Real() { return static_cast<CBeam*>(m_pReal); }
    CBeam* Real() const { return static_cast<CBeam*>(m_pReal); }

public:
    CBeam* GetOriginal() const override { return Real(); }
    float& FrameRate() override { return Real()->m_flFrameRate(); }
    void FrameRateUpdated() override { Real()->m_flFrameRate.NetworkStateChanged(); }
    float& HDRColorScale() override { return Real()->m_flHDRColorScale(); }
    void HDRColorScaleUpdated() override { Real()->m_flHDRColorScale.NetworkStateChanged(); }
    float& FireTime() override { return Real()->m_flFireTime(); }
    void FireTimeUpdated() override { Real()->m_flFireTime.NetworkStateChanged(); }
    float& Damage() override { return Real()->m_flDamage(); }
    void DamageUpdated() override { Real()->m_flDamage.NetworkStateChanged(); }
    uint8_t& NumBeamEnts() override { return Real()->m_nNumBeamEnts(); }
    void NumBeamEntsUpdated() override { Real()->m_nNumBeamEnts.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIMaterial2>& BaseMaterial() override { return Real()->m_hBaseMaterial(); }
    void BaseMaterialUpdated() override { Real()->m_hBaseMaterial.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeIMaterial2>& HaloIndex() override { return Real()->m_nHaloIndex(); }
    void HaloIndexUpdated() override { Real()->m_nHaloIndex.NetworkStateChanged(); }
    ::BeamType_t& BeamType() override { return Real()->m_nBeamType(); }
    void BeamTypeUpdated() override { Real()->m_nBeamType.NetworkStateChanged(); }
    uint32_t& BeamFlags() override { return Real()->m_nBeamFlags(); }
    void BeamFlagsUpdated() override { Real()->m_nBeamFlags.NetworkStateChanged(); }
    CHandle<CBaseEntity>* AttachEntity() override { return Real()->m_hAttachEntity(); }
    float& Width() override { return Real()->m_fWidth(); }
    void WidthUpdated() override { Real()->m_fWidth.NetworkStateChanged(); }
    float& EndWidth() override { return Real()->m_fEndWidth(); }
    void EndWidthUpdated() override { Real()->m_fEndWidth.NetworkStateChanged(); }
    float& FadeLength() override { return Real()->m_fFadeLength(); }
    void FadeLengthUpdated() override { Real()->m_fFadeLength.NetworkStateChanged(); }
    float& HaloScale() override { return Real()->m_fHaloScale(); }
    void HaloScaleUpdated() override { Real()->m_fHaloScale.NetworkStateChanged(); }
    float& Amplitude() override { return Real()->m_fAmplitude(); }
    void AmplitudeUpdated() override { Real()->m_fAmplitude.NetworkStateChanged(); }
    float& StartFrame() override { return Real()->m_fStartFrame(); }
    void StartFrameUpdated() override { Real()->m_fStartFrame.NetworkStateChanged(); }
    float& Speed() override { return Real()->m_fSpeed(); }
    void SpeedUpdated() override { Real()->m_fSpeed.NetworkStateChanged(); }
    float& Frame() override { return Real()->m_flFrame(); }
    void FrameUpdated() override { Real()->m_flFrame.NetworkStateChanged(); }
    ::BeamClipStyle_t& ClipStyle() override { return Real()->m_nClipStyle(); }
    void ClipStyleUpdated() override { Real()->m_nClipStyle.NetworkStateChanged(); }
    bool& TurnedOff() override { return Real()->m_bTurnedOff(); }
    void TurnedOffUpdated() override { Real()->m_bTurnedOff.NetworkStateChanged(); }
    Vector& EndPos() override { return Real()->m_vecEndPos(); }
    void EndPosUpdated() override { Real()->m_vecEndPos.NetworkStateChanged(); }
    CHandle<CBaseEntity>& EndEntity() override { return Real()->m_hEndEntity(); }
    void EndEntityUpdated() override { Real()->m_hEndEntity.NetworkStateChanged(); }
    int32_t& DissolveType() override { return Real()->m_nDissolveType(); }
    void DissolveTypeUpdated() override { Real()->m_nDissolveType.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IBeam* CBeam::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IBeam*>(tagIt->second.ptr_for_return);
    auto* impl = new CBeamImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IBeam*>(impl));
    return impl;
}
inline IBeam* IBeam::FromRaw(CEntityInstance* p) { return p ? static_cast<CBeam*>(p)->ToInterface() : nullptr; }
inline IBeam* IBeam::FromOriginal(CBeam* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBEAMIMPL_H
