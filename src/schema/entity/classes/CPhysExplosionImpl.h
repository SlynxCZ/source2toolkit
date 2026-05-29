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

#ifndef _INCLUDE_CPHYSEXPLOSIONIMPL_H
#define _INCLUDE_CPHYSEXPLOSIONIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPhysExplosion.h"
#include "schema/entity/classes/CPhysExplosion.h"
#include "CPointEntityImpl.h"

class CPhysExplosionImpl : public CPointEntityImpl, public virtual IPhysExplosion
{

public:
    explicit CPhysExplosionImpl(CPhysExplosion* p) : CPointEntityImpl(p) {}

private:
    CPhysExplosion* Real() { return static_cast<CPhysExplosion*>(m_pReal); }
    CPhysExplosion* Real() const { return static_cast<CPhysExplosion*>(m_pReal); }

public:
    CPhysExplosion* GetOriginal() const override { return Real(); }
    bool& ExplodeOnSpawn() override { return Real()->m_bExplodeOnSpawn(); }
    void ExplodeOnSpawnUpdated() override { Real()->m_bExplodeOnSpawn.NetworkStateChanged(); }
    float& Magnitude() override { return Real()->m_flMagnitude(); }
    void MagnitudeUpdated() override { Real()->m_flMagnitude.NetworkStateChanged(); }
    float& Damage() override { return Real()->m_flDamage(); }
    void DamageUpdated() override { Real()->m_flDamage.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_radius(); }
    void RadiusUpdated() override { Real()->m_radius.NetworkStateChanged(); }
    CUtlSymbolLarge& TargetEntityName() override { return Real()->m_targetEntityName(); }
    void TargetEntityNameUpdated() override { Real()->m_targetEntityName.NetworkStateChanged(); }
    float& InnerRadius() override { return Real()->m_flInnerRadius(); }
    void InnerRadiusUpdated() override { Real()->m_flInnerRadius.NetworkStateChanged(); }
    float& PushScale() override { return Real()->m_flPushScale(); }
    void PushScaleUpdated() override { Real()->m_flPushScale.NetworkStateChanged(); }
    bool& ConvertToDebrisWhenPossible() override { return Real()->m_bConvertToDebrisWhenPossible(); }
    void ConvertToDebrisWhenPossibleUpdated() override { Real()->m_bConvertToDebrisWhenPossible.NetworkStateChanged(); }
    bool& AffectInvulnerableEnts() override { return Real()->m_bAffectInvulnerableEnts(); }
    void AffectInvulnerableEntsUpdated() override { Real()->m_bAffectInvulnerableEnts.NetworkStateChanged(); }
    bool& DisablePushClamp() override { return Real()->m_bDisablePushClamp(); }
    void DisablePushClampUpdated() override { Real()->m_bDisablePushClamp.NetworkStateChanged(); }
    ::CEntityIOOutput& OnPushedPlayer() override { return Real()->m_OnPushedPlayer(); }
    void OnPushedPlayerUpdated() override { Real()->m_OnPushedPlayer.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPhysExplosion* CPhysExplosion::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPhysExplosion*>(tagIt->second.ptr_for_return);
    auto* impl = new CPhysExplosionImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPhysExplosion*>(impl));
    return impl;
}
inline IPhysExplosion* IPhysExplosion::FromRaw(CEntityInstance* p) { return p ? static_cast<CPhysExplosion*>(p)->ToInterface() : nullptr; }
inline IPhysExplosion* IPhysExplosion::FromOriginal(CPhysExplosion* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPHYSEXPLOSIONIMPL_H
