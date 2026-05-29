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

#ifndef _INCLUDE_CBASETRIGGERIMPL_H
#define _INCLUDE_CBASETRIGGERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBaseTrigger.h"
#include "schema/entity/classes/CBaseTrigger.h"
#include "CBaseToggleImpl.h"

class CBaseTriggerImpl : public CBaseToggleImpl, public virtual IBaseTrigger
{

public:
    explicit CBaseTriggerImpl(CBaseTrigger* p) : CBaseToggleImpl(p) {}

private:
    CBaseTrigger* Real() { return static_cast<CBaseTrigger*>(m_pReal); }
    CBaseTrigger* Real() const { return static_cast<CBaseTrigger*>(m_pReal); }

public:
    CBaseTrigger* GetOriginal() const override { return Real(); }
    ::CEntityIOOutput& OnStartTouch() override { return Real()->m_OnStartTouch(); }
    void OnStartTouchUpdated() override { Real()->m_OnStartTouch.NetworkStateChanged(); }
    ::CEntityIOOutput& OnStartTouchAll() override { return Real()->m_OnStartTouchAll(); }
    void OnStartTouchAllUpdated() override { Real()->m_OnStartTouchAll.NetworkStateChanged(); }
    ::CEntityIOOutput& OnEndTouch() override { return Real()->m_OnEndTouch(); }
    void OnEndTouchUpdated() override { Real()->m_OnEndTouch.NetworkStateChanged(); }
    ::CEntityIOOutput& OnEndTouchAll() override { return Real()->m_OnEndTouchAll(); }
    void OnEndTouchAllUpdated() override { Real()->m_OnEndTouchAll.NetworkStateChanged(); }
    ::CEntityIOOutput& OnTouching() override { return Real()->m_OnTouching(); }
    void OnTouchingUpdated() override { Real()->m_OnTouching.NetworkStateChanged(); }
    ::CEntityIOOutput& OnTouchingEachEntity() override { return Real()->m_OnTouchingEachEntity(); }
    void OnTouchingEachEntityUpdated() override { Real()->m_OnTouchingEachEntity.NetworkStateChanged(); }
    ::CEntityIOOutput& OnNotTouching() override { return Real()->m_OnNotTouching(); }
    void OnNotTouchingUpdated() override { Real()->m_OnNotTouching.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseEntity>>& TouchingEntities() override { return Real()->m_hTouchingEntities(); }
    void TouchingEntitiesUpdated() override { Real()->m_hTouchingEntities.NetworkStateChanged(); }
    CUtlSymbolLarge& FilterName() override { return Real()->m_iFilterName(); }
    void FilterNameUpdated() override { Real()->m_iFilterName.NetworkStateChanged(); }
    CHandle<CBaseFilter>& Filter() override { return Real()->m_hFilter(); }
    void FilterUpdated() override { Real()->m_hFilter.NetworkStateChanged(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    bool& UseAsyncQueries() override { return Real()->m_bUseAsyncQueries(); }
    void UseAsyncQueriesUpdated() override { Real()->m_bUseAsyncQueries.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IBaseTrigger* CBaseTrigger::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IBaseTrigger*>(tagIt->second.ptr_for_return);
    auto* impl = new CBaseTriggerImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IBaseTrigger*>(impl));
    return impl;
}
inline IBaseTrigger* IBaseTrigger::FromRaw(CEntityInstance* p) { return p ? static_cast<CBaseTrigger*>(p)->ToInterface() : nullptr; }
inline IBaseTrigger* IBaseTrigger::FromOriginal(CBaseTrigger* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBASETRIGGERIMPL_H
