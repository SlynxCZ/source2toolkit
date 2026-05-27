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

#ifndef _INCLUDE_CDECOYPROJECTILEIMPL_H
#define _INCLUDE_CDECOYPROJECTILEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IDecoyProjectile.h"
#include "schema/entity/classes/CDecoyProjectile.h"
#include "CBaseCSGrenadeProjectileImpl.h"

class CDecoyProjectileImpl : public CBaseCSGrenadeProjectileImpl, public IDecoyProjectile
{

public:
    explicit CDecoyProjectileImpl(CDecoyProjectile* p) : CBaseCSGrenadeProjectileImpl(p) {}

private:
    CDecoyProjectile* Real() { return static_cast<CDecoyProjectile*>(m_pReal); }

public:
    int32_t& DecoyShotTick() override { return Real()->m_nDecoyShotTick(); }
    void DecoyShotTickUpdated() override { Real()->m_nDecoyShotTick.NetworkStateChanged(); }
    int32_t& ShotsRemaining() override { return Real()->m_shotsRemaining(); }
    void ShotsRemainingUpdated() override { Real()->m_shotsRemaining.NetworkStateChanged(); }
    float& ExpireTime() override { return Real()->m_fExpireTime(); }
    void ExpireTimeUpdated() override { Real()->m_fExpireTime.NetworkStateChanged(); }
    uint16_t& DecoyWeaponDefIndex() override { return Real()->m_decoyWeaponDefIndex(); }
    void DecoyWeaponDefIndexUpdated() override { Real()->m_decoyWeaponDefIndex.NetworkStateChanged(); }
};

#endif // _INCLUDE_CDECOYPROJECTILEIMPL_H
