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

#ifndef _INCLUDE_DESTRUCTIBLEPARTDAMAGEREQUEST_TIMPL_H
#define _INCLUDE_DESTRUCTIBLEPARTDAMAGEREQUEST_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IDestructiblePartDamageRequest_t.h"
#include "schema/entity/classes/DestructiblePartDamageRequest_t.h"

class DestructiblePartDamageRequest_tImpl : public virtual IDestructiblePartDamageRequest_t
{

protected:
    void* m_pReal;

public:
    explicit DestructiblePartDamageRequest_tImpl(void* p) : m_pReal(p) {}

private:
    DestructiblePartDamageRequest_t* Real() { return static_cast<DestructiblePartDamageRequest_t*>(m_pReal); }
    DestructiblePartDamageRequest_t* Real() const { return static_cast<DestructiblePartDamageRequest_t*>(m_pReal); }

public:
    DestructiblePartDamageRequest_t* GetOriginal() const override { return Real(); }
    ::HitGroup_t& HitGroup() override { return Real()->m_nHitGroup(); }
    void HitGroupUpdated() override { Real()->m_nHitGroup.NetworkStateChanged(); }
    int32_t& DamageLevel() override { return Real()->m_nDamageLevel(); }
    void DamageLevelUpdated() override { Real()->m_nDamageLevel.NetworkStateChanged(); }
    uint16_t& DesiredHealth() override { return Real()->m_nDesiredHealth(); }
    void DesiredHealthUpdated() override { Real()->m_nDesiredHealth.NetworkStateChanged(); }
    ::EDestructibleParts_DestroyParameterFlags& DestroyFlags() override { return Real()->m_nDestroyFlags(); }
    void DestroyFlagsUpdated() override { Real()->m_nDestroyFlags.NetworkStateChanged(); }
    ::DamageTypes_t& DamageType() override { return Real()->m_nDamageType(); }
    void DamageTypeUpdated() override { Real()->m_nDamageType.NetworkStateChanged(); }
    float& BreakDamage() override { return Real()->m_flBreakDamage(); }
    void BreakDamageUpdated() override { Real()->m_flBreakDamage.NetworkStateChanged(); }
    float& BreakDamageRadius() override { return Real()->m_flBreakDamageRadius(); }
    void BreakDamageRadiusUpdated() override { Real()->m_flBreakDamageRadius.NetworkStateChanged(); }
    Vector& WsBreakDamageOrigin() override { return Real()->m_vWsBreakDamageOrigin(); }
    void WsBreakDamageOriginUpdated() override { Real()->m_vWsBreakDamageOrigin.NetworkStateChanged(); }
    Vector& WsBreakDamageForce() override { return Real()->m_vWsBreakDamageForce(); }
    void WsBreakDamageForceUpdated() override { Real()->m_vWsBreakDamageForce.NetworkStateChanged(); }
};

inline IDestructiblePartDamageRequest_t* DestructiblePartDamageRequest_t::ToInterface() { return new DestructiblePartDamageRequest_tImpl(this); }
inline IDestructiblePartDamageRequest_t* IDestructiblePartDamageRequest_t::FromOriginal(DestructiblePartDamageRequest_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_DESTRUCTIBLEPARTDAMAGEREQUEST_TIMPL_H
