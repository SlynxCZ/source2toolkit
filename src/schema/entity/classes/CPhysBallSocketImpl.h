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

#ifndef _INCLUDE_CPHYSBALLSOCKETIMPL_H
#define _INCLUDE_CPHYSBALLSOCKETIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysBallSocket.h"
#include "schema/entity/classes/CPhysBallSocket.h"
#include "CPhysConstraintImpl.h"

class CPhysBallSocketImpl : public CPhysConstraintImpl, public virtual IPhysBallSocket
{

public:
    explicit CPhysBallSocketImpl(CPhysBallSocket* p) : CPhysConstraintImpl(p) {}

private:
    CPhysBallSocket* Real() { return static_cast<CPhysBallSocket*>(m_pReal); }
    CPhysBallSocket* Real() const { return static_cast<CPhysBallSocket*>(m_pReal); }

public:
    CPhysBallSocket* GetOriginal() const override { return Real(); }
    float& JointFriction() override { return Real()->m_flJointFriction(); }
    void JointFrictionUpdated() override { Real()->m_flJointFriction.NetworkStateChanged(); }
    bool& EnableSwingLimit() override { return Real()->m_bEnableSwingLimit(); }
    void EnableSwingLimitUpdated() override { Real()->m_bEnableSwingLimit.NetworkStateChanged(); }
    float& SwingLimit() override { return Real()->m_flSwingLimit(); }
    void SwingLimitUpdated() override { Real()->m_flSwingLimit.NetworkStateChanged(); }
    bool& EnableTwistLimit() override { return Real()->m_bEnableTwistLimit(); }
    void EnableTwistLimitUpdated() override { Real()->m_bEnableTwistLimit.NetworkStateChanged(); }
    float& MinTwistAngle() override { return Real()->m_flMinTwistAngle(); }
    void MinTwistAngleUpdated() override { Real()->m_flMinTwistAngle.NetworkStateChanged(); }
    float& MaxTwistAngle() override { return Real()->m_flMaxTwistAngle(); }
    void MaxTwistAngleUpdated() override { Real()->m_flMaxTwistAngle.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPhysBallSocket* CPhysBallSocket::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPhysBallSocket*>(tagIt->second.ptr_for_return);
    auto* impl = new CPhysBallSocketImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPhysBallSocket*>(impl));
    return impl;
}
inline IPhysBallSocket* IPhysBallSocket::FromRaw(CEntityInstance* p) { return p ? static_cast<CPhysBallSocket*>(p)->ToInterface() : nullptr; }
inline IPhysBallSocket* IPhysBallSocket::FromOriginal(CPhysBallSocket* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPHYSBALLSOCKETIMPL_H
