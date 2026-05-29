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

#ifndef _INCLUDE_CCSPLAYER_BULLETSERVICESIMPL_H
#define _INCLUDE_CCSPLAYER_BULLETSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayer_BulletServices.h"
#include "schema/entity/classes/CCSPlayer_BulletServices.h"
#include "CPlayerPawnComponentImpl.h"

class CCSPlayer_BulletServicesImpl : public CPlayerPawnComponentImpl, public ICSPlayer_BulletServices
{

public:
    explicit CCSPlayer_BulletServicesImpl(CCSPlayer_BulletServices* p) : CPlayerPawnComponentImpl(p) {}

private:
    CCSPlayer_BulletServices* Real() { return static_cast<CCSPlayer_BulletServices*>(m_pReal); }
    CCSPlayer_BulletServices* Real() const { return static_cast<CCSPlayer_BulletServices*>(m_pReal); }

public:
    CCSPlayer_BulletServices* GetOriginal() const override { return Real(); }
    int32_t& TotalHitsOnServer() override { return Real()->m_totalHitsOnServer(); }
    void TotalHitsOnServerUpdated() override { Real()->m_totalHitsOnServer.NetworkStateChanged(); }
};

inline ICSPlayer_BulletServices* CCSPlayer_BulletServices::ToInterface() { return new CCSPlayer_BulletServicesImpl(this); }
inline ICSPlayer_BulletServices* ICSPlayer_BulletServices::FromOriginal(CCSPlayer_BulletServices* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSPLAYER_BULLETSERVICESIMPL_H
