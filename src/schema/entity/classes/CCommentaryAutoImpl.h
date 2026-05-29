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

#ifndef _INCLUDE_CCOMMENTARYAUTOIMPL_H
#define _INCLUDE_CCOMMENTARYAUTOIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICommentaryAuto.h"
#include "schema/entity/classes/CCommentaryAuto.h"
#include "CBaseEntityImpl.h"

class CCommentaryAutoImpl : public CBaseEntityImpl, public ICommentaryAuto
{

public:
    explicit CCommentaryAutoImpl(CCommentaryAuto* p) : CBaseEntityImpl(p) {}

private:
    CCommentaryAuto* Real() { return static_cast<CCommentaryAuto*>(m_pReal); }
    CCommentaryAuto* Real() const { return static_cast<CCommentaryAuto*>(m_pReal); }

public:
    CCommentaryAuto* GetOriginal() const override { return Real(); }
    ::CEntityIOOutput& OnCommentaryNewGame() override { return Real()->m_OnCommentaryNewGame(); }
    void OnCommentaryNewGameUpdated() override { Real()->m_OnCommentaryNewGame.NetworkStateChanged(); }
    ::CEntityIOOutput& OnCommentaryMidGame() override { return Real()->m_OnCommentaryMidGame(); }
    void OnCommentaryMidGameUpdated() override { Real()->m_OnCommentaryMidGame.NetworkStateChanged(); }
    ::CEntityIOOutput& OnCommentaryMultiplayerSpawn() override { return Real()->m_OnCommentaryMultiplayerSpawn(); }
    void OnCommentaryMultiplayerSpawnUpdated() override { Real()->m_OnCommentaryMultiplayerSpawn.NetworkStateChanged(); }
};

inline ICommentaryAuto* CCommentaryAuto::ToInterface() { return new CCommentaryAutoImpl(this); }
inline ICommentaryAuto* ICommentaryAuto::FromOriginal(CCommentaryAuto* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCOMMENTARYAUTOIMPL_H
