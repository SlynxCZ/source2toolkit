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

#ifndef _INCLUDE_CGAMEGIBMANAGERIMPL_H
#define _INCLUDE_CGAMEGIBMANAGERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IGameGibManager.h"
#include "schema/entity/classes/CGameGibManager.h"
#include "CBaseEntityImpl.h"

class CGameGibManagerImpl : public CBaseEntityImpl, public virtual IGameGibManager
{

public:
    explicit CGameGibManagerImpl(CGameGibManager* p) : CBaseEntityImpl(p) {}

private:
    CGameGibManager* Real() { return static_cast<CGameGibManager*>(m_pReal); }
    CGameGibManager* Real() const { return static_cast<CGameGibManager*>(m_pReal); }

public:
    CGameGibManager* GetOriginal() const override { return Real(); }
    bool& AllowNewGibs() override { return Real()->m_bAllowNewGibs(); }
    void AllowNewGibsUpdated() override { Real()->m_bAllowNewGibs.NetworkStateChanged(); }
    int32_t& CurrentMaxPieces() override { return Real()->m_iCurrentMaxPieces(); }
    void CurrentMaxPiecesUpdated() override { Real()->m_iCurrentMaxPieces.NetworkStateChanged(); }
    int32_t& MaxPieces() override { return Real()->m_iMaxPieces(); }
    void MaxPiecesUpdated() override { Real()->m_iMaxPieces.NetworkStateChanged(); }
    int32_t& LastFrame() override { return Real()->m_iLastFrame(); }
    void LastFrameUpdated() override { Real()->m_iLastFrame.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IGameGibManager* CGameGibManager::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IGameGibManager*>(tagIt->second.ptr_for_return);
    auto* impl = new CGameGibManagerImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IGameGibManager*>(impl));
    return impl;
}
inline IGameGibManager* IGameGibManager::FromRaw(CEntityInstance* p) { return p ? static_cast<CGameGibManager*>(p)->ToInterface() : nullptr; }
inline IGameGibManager* IGameGibManager::FromOriginal(CGameGibManager* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CGAMEGIBMANAGERIMPL_H
