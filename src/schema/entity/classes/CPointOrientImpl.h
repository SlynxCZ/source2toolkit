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

#ifndef _INCLUDE_CPOINTORIENTIMPL_H
#define _INCLUDE_CPOINTORIENTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointOrient.h"
#include "schema/entity/classes/CPointOrient.h"
#include "CBaseEntityImpl.h"

class CPointOrientImpl : public CBaseEntityImpl, public virtual IPointOrient
{

public:
    explicit CPointOrientImpl(CPointOrient* p) : CBaseEntityImpl(p) {}

private:
    CPointOrient* Real() { return static_cast<CPointOrient*>(m_pReal); }
    CPointOrient* Real() const { return static_cast<CPointOrient*>(m_pReal); }

public:
    CPointOrient* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge& SpawnTargetName() override { return Real()->m_iszSpawnTargetName(); }
    void SpawnTargetNameUpdated() override { Real()->m_iszSpawnTargetName.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Target() override { return Real()->m_hTarget(); }
    void TargetUpdated() override { Real()->m_hTarget.NetworkStateChanged(); }
    bool& Active() override { return Real()->m_bActive(); }
    void ActiveUpdated() override { Real()->m_bActive.NetworkStateChanged(); }
    ::PointOrientGoalDirectionType_t& GoalDirection() override { return Real()->m_nGoalDirection(); }
    void GoalDirectionUpdated() override { Real()->m_nGoalDirection.NetworkStateChanged(); }
    ::PointOrientConstraint_t& Constraint() override { return Real()->m_nConstraint(); }
    void ConstraintUpdated() override { Real()->m_nConstraint.NetworkStateChanged(); }
    float& MaxTurnRate() override { return Real()->m_flMaxTurnRate(); }
    void MaxTurnRateUpdated() override { Real()->m_flMaxTurnRate.NetworkStateChanged(); }
    float& LastGameTime() override { return Real()->m_flLastGameTime(); }
    void LastGameTimeUpdated() override { Real()->m_flLastGameTime.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPointOrient* CPointOrient::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPointOrient*>(tagIt->second.ptr_for_return);
    auto* impl = new CPointOrientImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPointOrient*>(impl));
    return impl;
}
inline IPointOrient* IPointOrient::FromRaw(CEntityInstance* p) { return p ? static_cast<CPointOrient*>(p)->ToInterface() : nullptr; }
inline IPointOrient* IPointOrient::FromOriginal(CPointOrient* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPOINTORIENTIMPL_H
