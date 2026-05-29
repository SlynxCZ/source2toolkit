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

#ifndef _INCLUDE_CMARKUPVOLUMETAGGED_NAVGAMEIMPL_H
#define _INCLUDE_CMARKUPVOLUMETAGGED_NAVGAMEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IMarkupVolumeTagged_NavGame.h"
#include "schema/entity/classes/CMarkupVolumeTagged_NavGame.h"
#include "CMarkupVolumeWithRefImpl.h"

class CMarkupVolumeTagged_NavGameImpl : public CMarkupVolumeWithRefImpl, public IMarkupVolumeTagged_NavGame
{

public:
    explicit CMarkupVolumeTagged_NavGameImpl(CMarkupVolumeTagged_NavGame* p) : CMarkupVolumeWithRefImpl(p) {}

private:
    CMarkupVolumeTagged_NavGame* Real() { return static_cast<CMarkupVolumeTagged_NavGame*>(m_pReal); }
    CMarkupVolumeTagged_NavGame* Real() const { return static_cast<CMarkupVolumeTagged_NavGame*>(m_pReal); }

public:
    CMarkupVolumeTagged_NavGame* GetOriginal() const override { return Real(); }
    ::NavScopeFlags_t& Scopes() override { return Real()->m_nScopes(); }
    void ScopesUpdated() override { Real()->m_nScopes.NetworkStateChanged(); }
    bool& FloodFillAttribute() override { return Real()->m_bFloodFillAttribute(); }
    void FloodFillAttributeUpdated() override { Real()->m_bFloodFillAttribute.NetworkStateChanged(); }
    bool& SplitNavSpace() override { return Real()->m_bSplitNavSpace(); }
    void SplitNavSpaceUpdated() override { Real()->m_bSplitNavSpace.NetworkStateChanged(); }
};

inline IMarkupVolumeTagged_NavGame* CMarkupVolumeTagged_NavGame::ToInterface() { return new CMarkupVolumeTagged_NavGameImpl(this); }
inline IMarkupVolumeTagged_NavGame* IMarkupVolumeTagged_NavGame::FromOriginal(CMarkupVolumeTagged_NavGame* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CMARKUPVOLUMETAGGED_NAVGAMEIMPL_H
