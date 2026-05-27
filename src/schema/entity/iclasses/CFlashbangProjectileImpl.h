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

#ifndef _INCLUDE_CFLASHBANGPROJECTILEIMPL_H
#define _INCLUDE_CFLASHBANGPROJECTILEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IFlashbangProjectile.h"
#include "schema/entity/classes/CFlashbangProjectile.h"
#include "CBaseCSGrenadeProjectileImpl.h"

class CFlashbangProjectileImpl : public CBaseCSGrenadeProjectileImpl, public IFlashbangProjectile
{

public:
    explicit CFlashbangProjectileImpl(CFlashbangProjectile* p) : CBaseCSGrenadeProjectileImpl(p) {}

private:
    CFlashbangProjectile* Real() { return static_cast<CFlashbangProjectile*>(m_pReal); }

public:
    float& TimeToDetonate() override { return Real()->m_flTimeToDetonate(); }
    void TimeToDetonateUpdated() override { Real()->m_flTimeToDetonate.NetworkStateChanged(); }
    uint8_t& NumOpponentsHit() override { return Real()->m_numOpponentsHit(); }
    void NumOpponentsHitUpdated() override { Real()->m_numOpponentsHit.NetworkStateChanged(); }
    uint8_t& NumTeammatesHit() override { return Real()->m_numTeammatesHit(); }
    void NumTeammatesHitUpdated() override { Real()->m_numTeammatesHit.NetworkStateChanged(); }
};

#endif // _INCLUDE_CFLASHBANGPROJECTILEIMPL_H
