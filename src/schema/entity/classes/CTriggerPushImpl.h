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

#ifndef _INCLUDE_CTRIGGERPUSHIMPL_H
#define _INCLUDE_CTRIGGERPUSHIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITriggerPush.h"
#include "schema/entity/classes/CTriggerPush.h"
#include "CBaseTriggerImpl.h"

class CTriggerPushImpl : public CBaseTriggerImpl, public virtual ITriggerPush
{

public:
    explicit CTriggerPushImpl(CTriggerPush* p) : CBaseTriggerImpl(p) {}

private:
    CTriggerPush* Real() { return static_cast<CTriggerPush*>(m_pReal); }
    CTriggerPush* Real() const { return static_cast<CTriggerPush*>(m_pReal); }

public:
    CTriggerPush* GetOriginal() const override { return Real(); }
    QAngle& PushEntitySpace() override { return Real()->m_angPushEntitySpace(); }
    void PushEntitySpaceUpdated() override { Real()->m_angPushEntitySpace.NetworkStateChanged(); }
    Vector& PushDirEntitySpace() override { return Real()->m_vecPushDirEntitySpace(); }
    void PushDirEntitySpaceUpdated() override { Real()->m_vecPushDirEntitySpace.NetworkStateChanged(); }
    bool& TriggerOnStartTouch() override { return Real()->m_bTriggerOnStartTouch(); }
    void TriggerOnStartTouchUpdated() override { Real()->m_bTriggerOnStartTouch.NetworkStateChanged(); }
    bool& UsePathSimple() override { return Real()->m_bUsePathSimple(); }
    void UsePathSimpleUpdated() override { Real()->m_bUsePathSimple.NetworkStateChanged(); }
    CUtlSymbolLarge& PathSimpleName() override { return Real()->m_iszPathSimpleName(); }
    void PathSimpleNameUpdated() override { Real()->m_iszPathSimpleName.NetworkStateChanged(); }
    CHandle<CPathSimple>& PathSimple() override { return Real()->m_PathSimple(); }
    void PathSimpleUpdated() override { Real()->m_PathSimple.NetworkStateChanged(); }
    uint32_t& SplinePushType() override { return Real()->m_splinePushType(); }
    void SplinePushTypeUpdated() override { Real()->m_splinePushType.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ITriggerPush* CTriggerPush::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ITriggerPush*>(tagIt->second.ptr_for_return);
    auto* impl = new CTriggerPushImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ITriggerPush*>(impl));
    return impl;
}
inline ITriggerPush* ITriggerPush::FromRaw(CEntityInstance* p) { return p ? static_cast<CTriggerPush*>(p)->ToInterface() : nullptr; }
inline ITriggerPush* ITriggerPush::FromOriginal(CTriggerPush* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CTRIGGERPUSHIMPL_H
