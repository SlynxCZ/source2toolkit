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

#ifndef _INCLUDE_CCSPLAYER_HOSTAGESERVICESIMPL_H
#define _INCLUDE_CCSPLAYER_HOSTAGESERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayer_HostageServices.h"
#include "schema/entity/classes/CCSPlayer_HostageServices.h"
#include "CPlayerPawnComponentImpl.h"

class CCSPlayer_HostageServicesImpl : public CPlayerPawnComponentImpl, public virtual ICSPlayer_HostageServices
{

public:
    explicit CCSPlayer_HostageServicesImpl(CCSPlayer_HostageServices* p) : CPlayerPawnComponentImpl(p) {}

private:
    CCSPlayer_HostageServices* Real() { return static_cast<CCSPlayer_HostageServices*>(m_pReal); }
    CCSPlayer_HostageServices* Real() const { return static_cast<CCSPlayer_HostageServices*>(m_pReal); }

public:
    CCSPlayer_HostageServices* GetOriginal() const override { return Real(); }
    CHandle<CBaseEntity>& CarriedHostage() override { return Real()->m_hCarriedHostage(); }
    void CarriedHostageUpdated() override { Real()->m_hCarriedHostage.NetworkStateChanged(); }
    CHandle<CBaseEntity>& CarriedHostageProp() override { return Real()->m_hCarriedHostageProp(); }
    void CarriedHostagePropUpdated() override { Real()->m_hCarriedHostageProp.NetworkStateChanged(); }
};

inline ICSPlayer_HostageServices* CCSPlayer_HostageServices::ToInterface() { return new CCSPlayer_HostageServicesImpl(this); }
inline ICSPlayer_HostageServices* ICSPlayer_HostageServices::FromRaw(CEntityInstance*) { return nullptr; }
inline ICSPlayer_HostageServices* ICSPlayer_HostageServices::FromOriginal(CCSPlayer_HostageServices* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSPLAYER_HOSTAGESERVICESIMPL_H
