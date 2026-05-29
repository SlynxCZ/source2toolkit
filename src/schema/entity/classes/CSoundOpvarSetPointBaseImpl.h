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

#ifndef _INCLUDE_CSOUNDOPVARSETPOINTBASEIMPL_H
#define _INCLUDE_CSOUNDOPVARSETPOINTBASEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISoundOpvarSetPointBase.h"
#include "schema/entity/classes/CSoundOpvarSetPointBase.h"
#include "CBaseEntityImpl.h"

class CSoundOpvarSetPointBaseImpl : public CBaseEntityImpl, public virtual ISoundOpvarSetPointBase
{

public:
    explicit CSoundOpvarSetPointBaseImpl(CSoundOpvarSetPointBase* p) : CBaseEntityImpl(p) {}

private:
    CSoundOpvarSetPointBase* Real() { return static_cast<CSoundOpvarSetPointBase*>(m_pReal); }
    CSoundOpvarSetPointBase* Real() const { return static_cast<CSoundOpvarSetPointBase*>(m_pReal); }

public:
    CSoundOpvarSetPointBase* GetOriginal() const override { return Real(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    CEntityHandle& Source() override { return Real()->m_hSource(); }
    void SourceUpdated() override { Real()->m_hSource.NetworkStateChanged(); }
    CUtlSymbolLarge& SourceEntityName() override { return Real()->m_iszSourceEntityName(); }
    void SourceEntityNameUpdated() override { Real()->m_iszSourceEntityName.NetworkStateChanged(); }
    Vector& LastPosition() override { return Real()->m_vLastPosition(); }
    void LastPositionUpdated() override { Real()->m_vLastPosition.NetworkStateChanged(); }
    float& RefreshTime() override { return Real()->m_flRefreshTime(); }
    void RefreshTimeUpdated() override { Real()->m_flRefreshTime.NetworkStateChanged(); }
    CUtlSymbolLarge& StackName() override { return Real()->m_iszStackName(); }
    void StackNameUpdated() override { Real()->m_iszStackName.NetworkStateChanged(); }
    CUtlSymbolLarge& OperatorName() override { return Real()->m_iszOperatorName(); }
    void OperatorNameUpdated() override { Real()->m_iszOperatorName.NetworkStateChanged(); }
    CUtlSymbolLarge& OpvarName() override { return Real()->m_iszOpvarName(); }
    void OpvarNameUpdated() override { Real()->m_iszOpvarName.NetworkStateChanged(); }
    int32_t& OpvarIndex() override { return Real()->m_iOpvarIndex(); }
    void OpvarIndexUpdated() override { Real()->m_iOpvarIndex.NetworkStateChanged(); }
    bool& UseAutoCompare() override { return Real()->m_bUseAutoCompare(); }
    void UseAutoCompareUpdated() override { Real()->m_bUseAutoCompare.NetworkStateChanged(); }
    bool& FastRefresh() override { return Real()->m_bFastRefresh(); }
    void FastRefreshUpdated() override { Real()->m_bFastRefresh.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ISoundOpvarSetPointBase* CSoundOpvarSetPointBase::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ISoundOpvarSetPointBase*>(tagIt->second.ptr_for_return);
    auto* impl = new CSoundOpvarSetPointBaseImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ISoundOpvarSetPointBase*>(impl));
    return impl;
}
inline ISoundOpvarSetPointBase* ISoundOpvarSetPointBase::FromRaw(CEntityInstance* p) { return p ? static_cast<CSoundOpvarSetPointBase*>(p)->ToInterface() : nullptr; }
inline ISoundOpvarSetPointBase* ISoundOpvarSetPointBase::FromOriginal(CSoundOpvarSetPointBase* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSOUNDOPVARSETPOINTBASEIMPL_H
