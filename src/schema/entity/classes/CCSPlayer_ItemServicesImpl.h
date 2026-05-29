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

#ifndef _INCLUDE_CCSPLAYER_ITEMSERVICESIMPL_H
#define _INCLUDE_CCSPLAYER_ITEMSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayer_ItemServices.h"
#include "schema/entity/classes/CCSPlayer_ItemServices.h"

class CCSPlayer_ItemServicesImpl : public virtual ICSPlayer_ItemServices
{

protected:
    void* m_pReal;

public:
    explicit CCSPlayer_ItemServicesImpl(void* p) : m_pReal(p) {}

private:
    CCSPlayer_ItemServices* Real() { return static_cast<CCSPlayer_ItemServices*>(m_pReal); }
    CCSPlayer_ItemServices* Real() const { return static_cast<CCSPlayer_ItemServices*>(m_pReal); }

public:
    CCSPlayer_ItemServices* GetOriginal() const override { return Real(); }
    bool& HasDefuser() override { return Real()->m_bHasDefuser(); }
    void HasDefuserUpdated() override { Real()->m_bHasDefuser.NetworkStateChanged(); }
    bool& HasHelmet() override { return Real()->m_bHasHelmet(); }
    void HasHelmetUpdated() override { Real()->m_bHasHelmet.NetworkStateChanged(); }

    void DropActivePlayerWeapon(IBasePlayerWeapon* pActiveWeapon) override { Real()->DropActivePlayerWeapon(pActiveWeapon); }
    void RemoveWeapons() override { Real()->RemoveWeapons(); }
    IBasePlayerWeapon* GiveNamedItem(const char* pszItem) override { return Real()->GiveNamedItem(pszItem); }
};

#endif // _INCLUDE_CCSPLAYER_ITEMSERVICESIMPL_H
