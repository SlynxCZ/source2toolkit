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

#ifndef _INCLUDE_CMULTISOURCEIMPL_H
#define _INCLUDE_CMULTISOURCEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IMultiSource.h"
#include "schema/entity/classes/CMultiSource.h"
#include "CLogicalEntityImpl.h"

class CMultiSourceImpl : public CLogicalEntityImpl, public virtual IMultiSource
{

public:
    explicit CMultiSourceImpl(CMultiSource* p) : CLogicalEntityImpl(p) {}

private:
    CMultiSource* Real() { return static_cast<CMultiSource*>(m_pReal); }
    CMultiSource* Real() const { return static_cast<CMultiSource*>(m_pReal); }

public:
    CMultiSource* GetOriginal() const override { return Real(); }
    CHandle<CBaseEntity>* RgEntities() override { return Real()->m_rgEntities(); }
    int32_t* RgTriggered() override { return Real()->m_rgTriggered(); }
    ::CEntityIOOutput& OnTrigger() override { return Real()->m_OnTrigger(); }
    void OnTriggerUpdated() override { Real()->m_OnTrigger.NetworkStateChanged(); }
    int32_t& Total() override { return Real()->m_iTotal(); }
    void TotalUpdated() override { Real()->m_iTotal.NetworkStateChanged(); }
    CUtlSymbolLarge& Globalstate() override { return Real()->m_globalstate(); }
    void GlobalstateUpdated() override { Real()->m_globalstate.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IMultiSource* CMultiSource::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IMultiSource*>(tagIt->second.ptr_for_return);
    auto* impl = new CMultiSourceImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IMultiSource*>(impl));
    return impl;
}
inline IMultiSource* IMultiSource::FromRaw(CEntityInstance* p) { return p ? static_cast<CMultiSource*>(p)->ToInterface() : nullptr; }
inline IMultiSource* IMultiSource::FromOriginal(CMultiSource* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CMULTISOURCEIMPL_H
