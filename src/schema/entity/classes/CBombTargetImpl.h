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

#ifndef _INCLUDE_CBOMBTARGETIMPL_H
#define _INCLUDE_CBOMBTARGETIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBombTarget.h"
#include "schema/entity/classes/CBombTarget.h"
#include "CBaseTriggerImpl.h"

class CBombTargetImpl : public CBaseTriggerImpl, public virtual IBombTarget
{

public:
    explicit CBombTargetImpl(CBombTarget* p) : CBaseTriggerImpl(p) {}

private:
    CBombTarget* Real() { return static_cast<CBombTarget*>(m_pReal); }
    CBombTarget* Real() const { return static_cast<CBombTarget*>(m_pReal); }

public:
    CBombTarget* GetOriginal() const override { return Real(); }
    ::CEntityIOOutput& OnBombExplode() override { return Real()->m_OnBombExplode(); }
    void OnBombExplodeUpdated() override { Real()->m_OnBombExplode.NetworkStateChanged(); }
    ::CEntityIOOutput& OnBombPlanted() override { return Real()->m_OnBombPlanted(); }
    void OnBombPlantedUpdated() override { Real()->m_OnBombPlanted.NetworkStateChanged(); }
    ::CEntityIOOutput& OnBombDefused() override { return Real()->m_OnBombDefused(); }
    void OnBombDefusedUpdated() override { Real()->m_OnBombDefused.NetworkStateChanged(); }
    bool& IsBombSiteB() override { return Real()->m_bIsBombSiteB(); }
    void IsBombSiteBUpdated() override { Real()->m_bIsBombSiteB.NetworkStateChanged(); }
    bool& IsHeistBombTarget() override { return Real()->m_bIsHeistBombTarget(); }
    void IsHeistBombTargetUpdated() override { Real()->m_bIsHeistBombTarget.NetworkStateChanged(); }
    bool& BombPlantedHere() override { return Real()->m_bBombPlantedHere(); }
    void BombPlantedHereUpdated() override { Real()->m_bBombPlantedHere.NetworkStateChanged(); }
    CUtlSymbolLarge& MountTarget() override { return Real()->m_szMountTarget(); }
    void MountTargetUpdated() override { Real()->m_szMountTarget.NetworkStateChanged(); }
    CHandle<CBaseEntity>& InstructorHint() override { return Real()->m_hInstructorHint(); }
    void InstructorHintUpdated() override { Real()->m_hInstructorHint.NetworkStateChanged(); }
    int32_t& BombSiteDesignation() override { return Real()->m_nBombSiteDesignation(); }
    void BombSiteDesignationUpdated() override { Real()->m_nBombSiteDesignation.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IBombTarget* CBombTarget::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IBombTarget*>(tagIt->second.ptr_for_return);
    auto* impl = new CBombTargetImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IBombTarget*>(impl));
    return impl;
}
inline IBombTarget* IBombTarget::FromRaw(CEntityInstance* p) { return p ? static_cast<CBombTarget*>(p)->ToInterface() : nullptr; }
inline IBombTarget* IBombTarget::FromOriginal(CBombTarget* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBOMBTARGETIMPL_H
