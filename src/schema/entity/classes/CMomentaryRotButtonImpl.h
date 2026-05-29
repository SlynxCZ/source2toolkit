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

#ifndef _INCLUDE_CMOMENTARYROTBUTTONIMPL_H
#define _INCLUDE_CMOMENTARYROTBUTTONIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IMomentaryRotButton.h"
#include "schema/entity/classes/CMomentaryRotButton.h"
#include "CRotButtonImpl.h"

class CMomentaryRotButtonImpl : public CRotButtonImpl, public virtual IMomentaryRotButton
{

public:
    explicit CMomentaryRotButtonImpl(CMomentaryRotButton* p) : CRotButtonImpl(p) {}

private:
    CMomentaryRotButton* Real() { return static_cast<CMomentaryRotButton*>(m_pReal); }
    CMomentaryRotButton* Real() const { return static_cast<CMomentaryRotButton*>(m_pReal); }

public:
    CMomentaryRotButton* GetOriginal() const override { return Real(); }
    ::CEntityIOOutput& OnUnpressed() override { return Real()->m_OnUnpressed(); }
    void OnUnpressedUpdated() override { Real()->m_OnUnpressed.NetworkStateChanged(); }
    ::CEntityIOOutput& OnFullyOpen() override { return Real()->m_OnFullyOpen(); }
    void OnFullyOpenUpdated() override { Real()->m_OnFullyOpen.NetworkStateChanged(); }
    ::CEntityIOOutput& OnFullyClosed() override { return Real()->m_OnFullyClosed(); }
    void OnFullyClosedUpdated() override { Real()->m_OnFullyClosed.NetworkStateChanged(); }
    ::CEntityIOOutput& OnReachedPosition() override { return Real()->m_OnReachedPosition(); }
    void OnReachedPositionUpdated() override { Real()->m_OnReachedPosition.NetworkStateChanged(); }
    int32_t& LastUsed() override { return Real()->m_lastUsed(); }
    void LastUsedUpdated() override { Real()->m_lastUsed.NetworkStateChanged(); }
    QAngle& Start() override { return Real()->m_start(); }
    void StartUpdated() override { Real()->m_start.NetworkStateChanged(); }
    QAngle& End() override { return Real()->m_end(); }
    void EndUpdated() override { Real()->m_end.NetworkStateChanged(); }
    float& IdealYaw() override { return Real()->m_IdealYaw(); }
    void IdealYawUpdated() override { Real()->m_IdealYaw.NetworkStateChanged(); }
    CUtlSymbolLarge& Noise() override { return Real()->m_sNoise(); }
    void NoiseUpdated() override { Real()->m_sNoise.NetworkStateChanged(); }
    bool& UpdateTarget() override { return Real()->m_bUpdateTarget(); }
    void UpdateTargetUpdated() override { Real()->m_bUpdateTarget.NetworkStateChanged(); }
    int32_t& Direction() override { return Real()->m_direction(); }
    void DirectionUpdated() override { Real()->m_direction.NetworkStateChanged(); }
    float& ReturnSpeed() override { return Real()->m_returnSpeed(); }
    void ReturnSpeedUpdated() override { Real()->m_returnSpeed.NetworkStateChanged(); }
    float& StartPosition() override { return Real()->m_flStartPosition(); }
    void StartPositionUpdated() override { Real()->m_flStartPosition.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IMomentaryRotButton* CMomentaryRotButton::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IMomentaryRotButton*>(tagIt->second.ptr_for_return);
    auto* impl = new CMomentaryRotButtonImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IMomentaryRotButton*>(impl));
    return impl;
}
inline IMomentaryRotButton* IMomentaryRotButton::FromRaw(CEntityInstance* p) { return p ? static_cast<CMomentaryRotButton*>(p)->ToInterface() : nullptr; }
inline IMomentaryRotButton* IMomentaryRotButton::FromOriginal(CMomentaryRotButton* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CMOMENTARYROTBUTTONIMPL_H
