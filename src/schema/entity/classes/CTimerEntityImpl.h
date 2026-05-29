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

#ifndef _INCLUDE_CTIMERENTITYIMPL_H
#define _INCLUDE_CTIMERENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITimerEntity.h"
#include "schema/entity/classes/CTimerEntity.h"
#include "CLogicalEntityImpl.h"

class CTimerEntityImpl : public CLogicalEntityImpl, public virtual ITimerEntity
{

public:
    explicit CTimerEntityImpl(CTimerEntity* p) : CLogicalEntityImpl(p) {}

private:
    CTimerEntity* Real() { return static_cast<CTimerEntity*>(m_pReal); }
    CTimerEntity* Real() const { return static_cast<CTimerEntity*>(m_pReal); }

public:
    CTimerEntity* GetOriginal() const override { return Real(); }
    ::CEntityIOOutput& OnTimer() override { return Real()->m_OnTimer(); }
    void OnTimerUpdated() override { Real()->m_OnTimer.NetworkStateChanged(); }
    ::CEntityIOOutput& OnTimerHigh() override { return Real()->m_OnTimerHigh(); }
    void OnTimerHighUpdated() override { Real()->m_OnTimerHigh.NetworkStateChanged(); }
    ::CEntityIOOutput& OnTimerLow() override { return Real()->m_OnTimerLow(); }
    void OnTimerLowUpdated() override { Real()->m_OnTimerLow.NetworkStateChanged(); }
    int32_t& Disabled() override { return Real()->m_iDisabled(); }
    void DisabledUpdated() override { Real()->m_iDisabled.NetworkStateChanged(); }
    float& InitialDelay() override { return Real()->m_flInitialDelay(); }
    void InitialDelayUpdated() override { Real()->m_flInitialDelay.NetworkStateChanged(); }
    float& RefireTime() override { return Real()->m_flRefireTime(); }
    void RefireTimeUpdated() override { Real()->m_flRefireTime.NetworkStateChanged(); }
    bool& UpDownState() override { return Real()->m_bUpDownState(); }
    void UpDownStateUpdated() override { Real()->m_bUpDownState.NetworkStateChanged(); }
    int32_t& UseRandomTime() override { return Real()->m_iUseRandomTime(); }
    void UseRandomTimeUpdated() override { Real()->m_iUseRandomTime.NetworkStateChanged(); }
    bool& PauseAfterFiring() override { return Real()->m_bPauseAfterFiring(); }
    void PauseAfterFiringUpdated() override { Real()->m_bPauseAfterFiring.NetworkStateChanged(); }
    float& LowerRandomBound() override { return Real()->m_flLowerRandomBound(); }
    void LowerRandomBoundUpdated() override { Real()->m_flLowerRandomBound.NetworkStateChanged(); }
    float& UpperRandomBound() override { return Real()->m_flUpperRandomBound(); }
    void UpperRandomBoundUpdated() override { Real()->m_flUpperRandomBound.NetworkStateChanged(); }
    float& RemainingTime() override { return Real()->m_flRemainingTime(); }
    void RemainingTimeUpdated() override { Real()->m_flRemainingTime.NetworkStateChanged(); }
    bool& Paused() override { return Real()->m_bPaused(); }
    void PausedUpdated() override { Real()->m_bPaused.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ITimerEntity* CTimerEntity::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ITimerEntity*>(tagIt->second.ptr_for_return);
    auto* impl = new CTimerEntityImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ITimerEntity*>(impl));
    return impl;
}
inline ITimerEntity* ITimerEntity::FromRaw(CEntityInstance* p) { return p ? static_cast<CTimerEntity*>(p)->ToInterface() : nullptr; }
inline ITimerEntity* ITimerEntity::FromOriginal(CTimerEntity* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CTIMERENTITYIMPL_H
