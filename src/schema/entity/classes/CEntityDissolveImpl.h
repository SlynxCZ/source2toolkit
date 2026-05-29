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

#ifndef _INCLUDE_CENTITYDISSOLVEIMPL_H
#define _INCLUDE_CENTITYDISSOLVEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEntityDissolve.h"
#include "schema/entity/classes/CEntityDissolve.h"
#include "CBaseModelEntityImpl.h"

class CEntityDissolveImpl : public CBaseModelEntityImpl, public virtual IEntityDissolve
{

public:
    explicit CEntityDissolveImpl(CEntityDissolve* p) : CBaseModelEntityImpl(p) {}

private:
    CEntityDissolve* Real() { return static_cast<CEntityDissolve*>(m_pReal); }
    CEntityDissolve* Real() const { return static_cast<CEntityDissolve*>(m_pReal); }

public:
    CEntityDissolve* GetOriginal() const override { return Real(); }
    float& FadeInStart() override { return Real()->m_flFadeInStart(); }
    void FadeInStartUpdated() override { Real()->m_flFadeInStart.NetworkStateChanged(); }
    float& FadeInLength() override { return Real()->m_flFadeInLength(); }
    void FadeInLengthUpdated() override { Real()->m_flFadeInLength.NetworkStateChanged(); }
    float& FadeOutModelStart() override { return Real()->m_flFadeOutModelStart(); }
    void FadeOutModelStartUpdated() override { Real()->m_flFadeOutModelStart.NetworkStateChanged(); }
    float& FadeOutModelLength() override { return Real()->m_flFadeOutModelLength(); }
    void FadeOutModelLengthUpdated() override { Real()->m_flFadeOutModelLength.NetworkStateChanged(); }
    float& FadeOutStart() override { return Real()->m_flFadeOutStart(); }
    void FadeOutStartUpdated() override { Real()->m_flFadeOutStart.NetworkStateChanged(); }
    float& FadeOutLength() override { return Real()->m_flFadeOutLength(); }
    void FadeOutLengthUpdated() override { Real()->m_flFadeOutLength.NetworkStateChanged(); }
    float& StartTime() override { return Real()->m_flStartTime(); }
    void StartTimeUpdated() override { Real()->m_flStartTime.NetworkStateChanged(); }
    ::EntityDisolveType_t& DissolveType() override { return Real()->m_nDissolveType(); }
    void DissolveTypeUpdated() override { Real()->m_nDissolveType.NetworkStateChanged(); }
    Vector& DissolverOrigin() override { return Real()->m_vDissolverOrigin(); }
    void DissolverOriginUpdated() override { Real()->m_vDissolverOrigin.NetworkStateChanged(); }
    uint32_t& Magnitude() override { return Real()->m_nMagnitude(); }
    void MagnitudeUpdated() override { Real()->m_nMagnitude.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IEntityDissolve* CEntityDissolve::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IEntityDissolve*>(tagIt->second.ptr_for_return);
    auto* impl = new CEntityDissolveImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IEntityDissolve*>(impl));
    return impl;
}
inline IEntityDissolve* IEntityDissolve::FromRaw(CEntityInstance* p) { return p ? static_cast<CEntityDissolve*>(p)->ToInterface() : nullptr; }
inline IEntityDissolve* IEntityDissolve::FromOriginal(CEntityDissolve* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENTITYDISSOLVEIMPL_H
