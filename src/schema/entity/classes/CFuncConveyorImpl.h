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

#ifndef _INCLUDE_CFUNCCONVEYORIMPL_H
#define _INCLUDE_CFUNCCONVEYORIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IFuncConveyor.h"
#include "schema/entity/classes/CFuncConveyor.h"
#include "CBaseModelEntityImpl.h"

class CFuncConveyorImpl : public CBaseModelEntityImpl, public virtual IFuncConveyor
{

public:
    explicit CFuncConveyorImpl(CFuncConveyor* p) : CBaseModelEntityImpl(p) {}

private:
    CFuncConveyor* Real() { return static_cast<CFuncConveyor*>(m_pReal); }
    CFuncConveyor* Real() const { return static_cast<CFuncConveyor*>(m_pReal); }

public:
    CFuncConveyor* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge& ConveyorModels() override { return Real()->m_szConveyorModels(); }
    void ConveyorModelsUpdated() override { Real()->m_szConveyorModels.NetworkStateChanged(); }
    float& TransitionDurationSeconds() override { return Real()->m_flTransitionDurationSeconds(); }
    void TransitionDurationSecondsUpdated() override { Real()->m_flTransitionDurationSeconds.NetworkStateChanged(); }
    QAngle& MoveEntitySpace() override { return Real()->m_angMoveEntitySpace(); }
    void MoveEntitySpaceUpdated() override { Real()->m_angMoveEntitySpace.NetworkStateChanged(); }
    Vector& MoveDirEntitySpace() override { return Real()->m_vecMoveDirEntitySpace(); }
    void MoveDirEntitySpaceUpdated() override { Real()->m_vecMoveDirEntitySpace.NetworkStateChanged(); }
    float& TargetSpeed() override { return Real()->m_flTargetSpeed(); }
    void TargetSpeedUpdated() override { Real()->m_flTargetSpeed.NetworkStateChanged(); }
    int32_t& TransitionStartTick() override { return Real()->m_nTransitionStartTick(); }
    void TransitionStartTickUpdated() override { Real()->m_nTransitionStartTick.NetworkStateChanged(); }
    int32_t& TransitionDurationTicks() override { return Real()->m_nTransitionDurationTicks(); }
    void TransitionDurationTicksUpdated() override { Real()->m_nTransitionDurationTicks.NetworkStateChanged(); }
    float& TransitionStartSpeed() override { return Real()->m_flTransitionStartSpeed(); }
    void TransitionStartSpeedUpdated() override { Real()->m_flTransitionStartSpeed.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IFuncConveyor* CFuncConveyor::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IFuncConveyor*>(tagIt->second.ptr_for_return);
    auto* impl = new CFuncConveyorImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IFuncConveyor*>(impl));
    return impl;
}
inline IFuncConveyor* IFuncConveyor::FromRaw(CEntityInstance* p) { return p ? static_cast<CFuncConveyor*>(p)->ToInterface() : nullptr; }
inline IFuncConveyor* IFuncConveyor::FromOriginal(CFuncConveyor* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CFUNCCONVEYORIMPL_H
