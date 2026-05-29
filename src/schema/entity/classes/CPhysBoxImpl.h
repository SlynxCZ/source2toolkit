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

#ifndef _INCLUDE_CPHYSBOXIMPL_H
#define _INCLUDE_CPHYSBOXIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysBox.h"
#include "schema/entity/classes/CPhysBox.h"
#include "CBreakableImpl.h"

class CPhysBoxImpl : public CBreakableImpl, public virtual IPhysBox
{

public:
    explicit CPhysBoxImpl(CPhysBox* p) : CBreakableImpl(p) {}

private:
    CPhysBox* Real() { return static_cast<CPhysBox*>(m_pReal); }
    CPhysBox* Real() const { return static_cast<CPhysBox*>(m_pReal); }

public:
    CPhysBox* GetOriginal() const override { return Real(); }
    int32_t& DamageType() override { return Real()->m_damageType(); }
    void DamageTypeUpdated() override { Real()->m_damageType.NetworkStateChanged(); }
    int32_t& DamageToEnableMotion() override { return Real()->m_damageToEnableMotion(); }
    void DamageToEnableMotionUpdated() override { Real()->m_damageToEnableMotion.NetworkStateChanged(); }
    float& ForceToEnableMotion() override { return Real()->m_flForceToEnableMotion(); }
    void ForceToEnableMotionUpdated() override { Real()->m_flForceToEnableMotion.NetworkStateChanged(); }
    Vector& HoverPosePosition() override { return Real()->m_vHoverPosePosition(); }
    void HoverPosePositionUpdated() override { Real()->m_vHoverPosePosition.NetworkStateChanged(); }
    QAngle& HoverPoseAngles() override { return Real()->m_angHoverPoseAngles(); }
    void HoverPoseAnglesUpdated() override { Real()->m_angHoverPoseAngles.NetworkStateChanged(); }
    bool& NotSolidToWorld() override { return Real()->m_bNotSolidToWorld(); }
    void NotSolidToWorldUpdated() override { Real()->m_bNotSolidToWorld.NetworkStateChanged(); }
    bool& EnableUseOutput() override { return Real()->m_bEnableUseOutput(); }
    void EnableUseOutputUpdated() override { Real()->m_bEnableUseOutput.NetworkStateChanged(); }
    ::HoverPoseFlags_t& HoverPoseFlags() override { return Real()->m_nHoverPoseFlags(); }
    void HoverPoseFlagsUpdated() override { Real()->m_nHoverPoseFlags.NetworkStateChanged(); }
    float& TouchOutputPerEntityDelay() override { return Real()->m_flTouchOutputPerEntityDelay(); }
    void TouchOutputPerEntityDelayUpdated() override { Real()->m_flTouchOutputPerEntityDelay.NetworkStateChanged(); }
    ::CEntityIOOutput& OnDamaged() override { return Real()->m_OnDamaged(); }
    void OnDamagedUpdated() override { Real()->m_OnDamaged.NetworkStateChanged(); }
    ::CEntityIOOutput& OnAwakened() override { return Real()->m_OnAwakened(); }
    void OnAwakenedUpdated() override { Real()->m_OnAwakened.NetworkStateChanged(); }
    ::CEntityIOOutput& OnMotionEnabled() override { return Real()->m_OnMotionEnabled(); }
    void OnMotionEnabledUpdated() override { Real()->m_OnMotionEnabled.NetworkStateChanged(); }
    ::CEntityIOOutput& OnPlayerUse() override { return Real()->m_OnPlayerUse(); }
    void OnPlayerUseUpdated() override { Real()->m_OnPlayerUse.NetworkStateChanged(); }
    ::CEntityIOOutput& OnStartTouch() override { return Real()->m_OnStartTouch(); }
    void OnStartTouchUpdated() override { Real()->m_OnStartTouch.NetworkStateChanged(); }
    CHandle<CBasePlayerPawn>& CarryingPlayer() override { return Real()->m_hCarryingPlayer(); }
    void CarryingPlayerUpdated() override { Real()->m_hCarryingPlayer.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPhysBox* CPhysBox::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPhysBox*>(tagIt->second.ptr_for_return);
    auto* impl = new CPhysBoxImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPhysBox*>(impl));
    return impl;
}
inline IPhysBox* IPhysBox::FromRaw(CEntityInstance* p) { return p ? static_cast<CPhysBox*>(p)->ToInterface() : nullptr; }
inline IPhysBox* IPhysBox::FromOriginal(CPhysBox* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPHYSBOXIMPL_H
