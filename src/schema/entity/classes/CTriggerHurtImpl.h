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

#ifndef _INCLUDE_CTRIGGERHURTIMPL_H
#define _INCLUDE_CTRIGGERHURTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITriggerHurt.h"
#include "schema/entity/classes/CTriggerHurt.h"
#include "CBaseTriggerImpl.h"

class CTriggerHurtImpl : public CBaseTriggerImpl, public virtual ITriggerHurt
{

public:
    explicit CTriggerHurtImpl(CTriggerHurt* p) : CBaseTriggerImpl(p) {}

private:
    CTriggerHurt* Real() { return static_cast<CTriggerHurt*>(m_pReal); }
    CTriggerHurt* Real() const { return static_cast<CTriggerHurt*>(m_pReal); }

public:
    CTriggerHurt* GetOriginal() const override { return Real(); }
    float& OriginalDamage() override { return Real()->m_flOriginalDamage(); }
    void OriginalDamageUpdated() override { Real()->m_flOriginalDamage.NetworkStateChanged(); }
    float& Damage() override { return Real()->m_flDamage(); }
    void DamageUpdated() override { Real()->m_flDamage.NetworkStateChanged(); }
    float& DamageCap() override { return Real()->m_flDamageCap(); }
    void DamageCapUpdated() override { Real()->m_flDamageCap.NetworkStateChanged(); }
    float& LastDmgTime() override { return Real()->m_flLastDmgTime(); }
    void LastDmgTimeUpdated() override { Real()->m_flLastDmgTime.NetworkStateChanged(); }
    float& ForgivenessDelay() override { return Real()->m_flForgivenessDelay(); }
    void ForgivenessDelayUpdated() override { Real()->m_flForgivenessDelay.NetworkStateChanged(); }
    ::DamageTypes_t& BitsDamageInflict() override { return Real()->m_bitsDamageInflict(); }
    void BitsDamageInflictUpdated() override { Real()->m_bitsDamageInflict.NetworkStateChanged(); }
    int32_t& DamageModel() override { return Real()->m_damageModel(); }
    void DamageModelUpdated() override { Real()->m_damageModel.NetworkStateChanged(); }
    bool& NoDmgForce() override { return Real()->m_bNoDmgForce(); }
    void NoDmgForceUpdated() override { Real()->m_bNoDmgForce.NetworkStateChanged(); }
    Vector& DamageForce() override { return Real()->m_vDamageForce(); }
    void DamageForceUpdated() override { Real()->m_vDamageForce.NetworkStateChanged(); }
    bool& ThinkAlways() override { return Real()->m_thinkAlways(); }
    void ThinkAlwaysUpdated() override { Real()->m_thinkAlways.NetworkStateChanged(); }
    float& HurtThinkPeriod() override { return Real()->m_hurtThinkPeriod(); }
    void HurtThinkPeriodUpdated() override { Real()->m_hurtThinkPeriod.NetworkStateChanged(); }
    ::CEntityIOOutput& OnHurt() override { return Real()->m_OnHurt(); }
    void OnHurtUpdated() override { Real()->m_OnHurt.NetworkStateChanged(); }
    ::CEntityIOOutput& OnHurtPlayer() override { return Real()->m_OnHurtPlayer(); }
    void OnHurtPlayerUpdated() override { Real()->m_OnHurtPlayer.NetworkStateChanged(); }
    CUtlVector<CHandle<CBaseEntity>>& HurtEntities() override { return Real()->m_hurtEntities(); }
    void HurtEntitiesUpdated() override { Real()->m_hurtEntities.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ITriggerHurt* CTriggerHurt::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ITriggerHurt*>(tagIt->second.ptr_for_return);
    auto* impl = new CTriggerHurtImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ITriggerHurt*>(impl));
    return impl;
}
inline ITriggerHurt* ITriggerHurt::FromRaw(CEntityInstance* p) { return p ? static_cast<CTriggerHurt*>(p)->ToInterface() : nullptr; }
inline ITriggerHurt* ITriggerHurt::FromOriginal(CTriggerHurt* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CTRIGGERHURTIMPL_H
