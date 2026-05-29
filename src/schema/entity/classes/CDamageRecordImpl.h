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

#ifndef _INCLUDE_CDAMAGERECORDIMPL_H
#define _INCLUDE_CDAMAGERECORDIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IDamageRecord.h"
#include "schema/entity/classes/CDamageRecord.h"

class CDamageRecordImpl : public virtual IDamageRecord
{

protected:
    void* m_pReal;

public:
    explicit CDamageRecordImpl(void* p) : m_pReal(p) {}

private:
    CDamageRecord* Real() { return static_cast<CDamageRecord*>(m_pReal); }
    CDamageRecord* Real() const { return static_cast<CDamageRecord*>(m_pReal); }

public:
    CDamageRecord* GetOriginal() const override { return Real(); }
    CHandle<CCSPlayerPawn>& PlayerDamager() override { return Real()->m_PlayerDamager(); }
    void PlayerDamagerUpdated() override { Real()->m_PlayerDamager.NetworkStateChanged(); }
    CHandle<CCSPlayerPawn>& PlayerRecipient() override { return Real()->m_PlayerRecipient(); }
    void PlayerRecipientUpdated() override { Real()->m_PlayerRecipient.NetworkStateChanged(); }
    CHandle<CCSPlayerController>& PlayerControllerDamager() override { return Real()->m_hPlayerControllerDamager(); }
    void PlayerControllerDamagerUpdated() override { Real()->m_hPlayerControllerDamager.NetworkStateChanged(); }
    CHandle<CCSPlayerController>& PlayerControllerRecipient() override { return Real()->m_hPlayerControllerRecipient(); }
    void PlayerControllerRecipientUpdated() override { Real()->m_hPlayerControllerRecipient.NetworkStateChanged(); }
    CUtlString& PlayerDamagerName() override { return Real()->m_szPlayerDamagerName(); }
    void PlayerDamagerNameUpdated() override { Real()->m_szPlayerDamagerName.NetworkStateChanged(); }
    CUtlString& PlayerRecipientName() override { return Real()->m_szPlayerRecipientName(); }
    void PlayerRecipientNameUpdated() override { Real()->m_szPlayerRecipientName.NetworkStateChanged(); }
    uint64_t& DamagerXuid() override { return Real()->m_DamagerXuid(); }
    void DamagerXuidUpdated() override { Real()->m_DamagerXuid.NetworkStateChanged(); }
    uint64_t& RecipientXuid() override { return Real()->m_RecipientXuid(); }
    void RecipientXuidUpdated() override { Real()->m_RecipientXuid.NetworkStateChanged(); }
    float& BulletsDamage() override { return Real()->m_flBulletsDamage(); }
    void BulletsDamageUpdated() override { Real()->m_flBulletsDamage.NetworkStateChanged(); }
    float& Damage() override { return Real()->m_flDamage(); }
    void DamageUpdated() override { Real()->m_flDamage.NetworkStateChanged(); }
    float& ActualHealthRemoved() override { return Real()->m_flActualHealthRemoved(); }
    void ActualHealthRemovedUpdated() override { Real()->m_flActualHealthRemoved.NetworkStateChanged(); }
    int32_t& NumHits() override { return Real()->m_iNumHits(); }
    void NumHitsUpdated() override { Real()->m_iNumHits.NetworkStateChanged(); }
    int32_t& LastBulletUpdate() override { return Real()->m_iLastBulletUpdate(); }
    void LastBulletUpdateUpdated() override { Real()->m_iLastBulletUpdate.NetworkStateChanged(); }
    bool& IsOtherEnemy() override { return Real()->m_bIsOtherEnemy(); }
    void IsOtherEnemyUpdated() override { Real()->m_bIsOtherEnemy.NetworkStateChanged(); }
    ::EKillTypes_t& KillType() override { return Real()->m_killType(); }
    void KillTypeUpdated() override { Real()->m_killType.NetworkStateChanged(); }
};

inline IDamageRecord* CDamageRecord::ToInterface() { return new CDamageRecordImpl(this); }
inline IDamageRecord* IDamageRecord::FromOriginal(CDamageRecord* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CDAMAGERECORDIMPL_H
