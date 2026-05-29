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

#ifndef _INCLUDE_CLOGICNPCCOUNTERIMPL_H
#define _INCLUDE_CLOGICNPCCOUNTERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ILogicNPCCounter.h"
#include "schema/entity/classes/CLogicNPCCounter.h"
#include "CBaseEntityImpl.h"

class CLogicNPCCounterImpl : public CBaseEntityImpl, public virtual ILogicNPCCounter
{

public:
    explicit CLogicNPCCounterImpl(CLogicNPCCounter* p) : CBaseEntityImpl(p) {}

private:
    CLogicNPCCounter* Real() { return static_cast<CLogicNPCCounter*>(m_pReal); }
    CLogicNPCCounter* Real() const { return static_cast<CLogicNPCCounter*>(m_pReal); }

public:
    CLogicNPCCounter* GetOriginal() const override { return Real(); }
    ::CEntityIOOutput& OnMinCountAll() override { return Real()->m_OnMinCountAll(); }
    void OnMinCountAllUpdated() override { Real()->m_OnMinCountAll.NetworkStateChanged(); }
    ::CEntityIOOutput& OnMaxCountAll() override { return Real()->m_OnMaxCountAll(); }
    void OnMaxCountAllUpdated() override { Real()->m_OnMaxCountAll.NetworkStateChanged(); }
    ::CEntityIOOutput& OnMinCount_1() override { return Real()->m_OnMinCount_1(); }
    void OnMinCount_1Updated() override { Real()->m_OnMinCount_1.NetworkStateChanged(); }
    ::CEntityIOOutput& OnMaxCount_1() override { return Real()->m_OnMaxCount_1(); }
    void OnMaxCount_1Updated() override { Real()->m_OnMaxCount_1.NetworkStateChanged(); }
    ::CEntityIOOutput& OnMinCount_2() override { return Real()->m_OnMinCount_2(); }
    void OnMinCount_2Updated() override { Real()->m_OnMinCount_2.NetworkStateChanged(); }
    ::CEntityIOOutput& OnMaxCount_2() override { return Real()->m_OnMaxCount_2(); }
    void OnMaxCount_2Updated() override { Real()->m_OnMaxCount_2.NetworkStateChanged(); }
    ::CEntityIOOutput& OnMinCount_3() override { return Real()->m_OnMinCount_3(); }
    void OnMinCount_3Updated() override { Real()->m_OnMinCount_3.NetworkStateChanged(); }
    ::CEntityIOOutput& OnMaxCount_3() override { return Real()->m_OnMaxCount_3(); }
    void OnMaxCount_3Updated() override { Real()->m_OnMaxCount_3.NetworkStateChanged(); }
    CEntityHandle& Source() override { return Real()->m_hSource(); }
    void SourceUpdated() override { Real()->m_hSource.NetworkStateChanged(); }
    CUtlSymbolLarge& SourceEntityName() override { return Real()->m_iszSourceEntityName(); }
    void SourceEntityNameUpdated() override { Real()->m_iszSourceEntityName.NetworkStateChanged(); }
    float& DistanceMax() override { return Real()->m_flDistanceMax(); }
    void DistanceMaxUpdated() override { Real()->m_flDistanceMax.NetworkStateChanged(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    int32_t& MinCountAll() override { return Real()->m_nMinCountAll(); }
    void MinCountAllUpdated() override { Real()->m_nMinCountAll.NetworkStateChanged(); }
    int32_t& MaxCountAll() override { return Real()->m_nMaxCountAll(); }
    void MaxCountAllUpdated() override { Real()->m_nMaxCountAll.NetworkStateChanged(); }
    int32_t& MinFactorAll() override { return Real()->m_nMinFactorAll(); }
    void MinFactorAllUpdated() override { Real()->m_nMinFactorAll.NetworkStateChanged(); }
    int32_t& MaxFactorAll() override { return Real()->m_nMaxFactorAll(); }
    void MaxFactorAllUpdated() override { Real()->m_nMaxFactorAll.NetworkStateChanged(); }
    CUtlSymbolLarge& NPCClassname_1() override { return Real()->m_iszNPCClassname_1(); }
    void NPCClassname_1Updated() override { Real()->m_iszNPCClassname_1.NetworkStateChanged(); }
    int32_t& NPCState_1() override { return Real()->m_nNPCState_1(); }
    void NPCState_1Updated() override { Real()->m_nNPCState_1.NetworkStateChanged(); }
    bool& InvertState_1() override { return Real()->m_bInvertState_1(); }
    void InvertState_1Updated() override { Real()->m_bInvertState_1.NetworkStateChanged(); }
    int32_t& MinCount_1() override { return Real()->m_nMinCount_1(); }
    void MinCount_1Updated() override { Real()->m_nMinCount_1.NetworkStateChanged(); }
    int32_t& MaxCount_1() override { return Real()->m_nMaxCount_1(); }
    void MaxCount_1Updated() override { Real()->m_nMaxCount_1.NetworkStateChanged(); }
    int32_t& MinFactor_1() override { return Real()->m_nMinFactor_1(); }
    void MinFactor_1Updated() override { Real()->m_nMinFactor_1.NetworkStateChanged(); }
    int32_t& MaxFactor_1() override { return Real()->m_nMaxFactor_1(); }
    void MaxFactor_1Updated() override { Real()->m_nMaxFactor_1.NetworkStateChanged(); }
    float& DefaultDist_1() override { return Real()->m_flDefaultDist_1(); }
    void DefaultDist_1Updated() override { Real()->m_flDefaultDist_1.NetworkStateChanged(); }
    CUtlSymbolLarge& NPCClassname_2() override { return Real()->m_iszNPCClassname_2(); }
    void NPCClassname_2Updated() override { Real()->m_iszNPCClassname_2.NetworkStateChanged(); }
    int32_t& NPCState_2() override { return Real()->m_nNPCState_2(); }
    void NPCState_2Updated() override { Real()->m_nNPCState_2.NetworkStateChanged(); }
    bool& InvertState_2() override { return Real()->m_bInvertState_2(); }
    void InvertState_2Updated() override { Real()->m_bInvertState_2.NetworkStateChanged(); }
    int32_t& MinCount_2() override { return Real()->m_nMinCount_2(); }
    void MinCount_2Updated() override { Real()->m_nMinCount_2.NetworkStateChanged(); }
    int32_t& MaxCount_2() override { return Real()->m_nMaxCount_2(); }
    void MaxCount_2Updated() override { Real()->m_nMaxCount_2.NetworkStateChanged(); }
    int32_t& MinFactor_2() override { return Real()->m_nMinFactor_2(); }
    void MinFactor_2Updated() override { Real()->m_nMinFactor_2.NetworkStateChanged(); }
    int32_t& MaxFactor_2() override { return Real()->m_nMaxFactor_2(); }
    void MaxFactor_2Updated() override { Real()->m_nMaxFactor_2.NetworkStateChanged(); }
    float& DefaultDist_2() override { return Real()->m_flDefaultDist_2(); }
    void DefaultDist_2Updated() override { Real()->m_flDefaultDist_2.NetworkStateChanged(); }
    CUtlSymbolLarge& NPCClassname_3() override { return Real()->m_iszNPCClassname_3(); }
    void NPCClassname_3Updated() override { Real()->m_iszNPCClassname_3.NetworkStateChanged(); }
    int32_t& NPCState_3() override { return Real()->m_nNPCState_3(); }
    void NPCState_3Updated() override { Real()->m_nNPCState_3.NetworkStateChanged(); }
    bool& InvertState_3() override { return Real()->m_bInvertState_3(); }
    void InvertState_3Updated() override { Real()->m_bInvertState_3.NetworkStateChanged(); }
    int32_t& MinCount_3() override { return Real()->m_nMinCount_3(); }
    void MinCount_3Updated() override { Real()->m_nMinCount_3.NetworkStateChanged(); }
    int32_t& MaxCount_3() override { return Real()->m_nMaxCount_3(); }
    void MaxCount_3Updated() override { Real()->m_nMaxCount_3.NetworkStateChanged(); }
    int32_t& MinFactor_3() override { return Real()->m_nMinFactor_3(); }
    void MinFactor_3Updated() override { Real()->m_nMinFactor_3.NetworkStateChanged(); }
    int32_t& MaxFactor_3() override { return Real()->m_nMaxFactor_3(); }
    void MaxFactor_3Updated() override { Real()->m_nMaxFactor_3.NetworkStateChanged(); }
    float& DefaultDist_3() override { return Real()->m_flDefaultDist_3(); }
    void DefaultDist_3Updated() override { Real()->m_flDefaultDist_3.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ILogicNPCCounter* CLogicNPCCounter::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ILogicNPCCounter*>(tagIt->second.ptr_for_return);
    auto* impl = new CLogicNPCCounterImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ILogicNPCCounter*>(impl));
    return impl;
}
inline ILogicNPCCounter* ILogicNPCCounter::FromRaw(CEntityInstance* p) { return p ? static_cast<CLogicNPCCounter*>(p)->ToInterface() : nullptr; }
inline ILogicNPCCounter* ILogicNPCCounter::FromOriginal(CLogicNPCCounter* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CLOGICNPCCOUNTERIMPL_H
