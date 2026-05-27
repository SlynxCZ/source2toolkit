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

#ifndef _INCLUDE_CMARKUPVOLUMETAGGEDIMPL_H
#define _INCLUDE_CMARKUPVOLUMETAGGEDIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IMarkupVolumeTagged.h"
#include "schema/entity/classes/CMarkupVolumeTagged.h"
#include "CMarkupVolumeImpl.h"

class CMarkupVolumeTaggedImpl : public CMarkupVolumeImpl, public IMarkupVolumeTagged
{

public:
    explicit CMarkupVolumeTaggedImpl(CMarkupVolumeTagged* p) : CMarkupVolumeImpl(p) {}

private:
    CMarkupVolumeTagged* Real() { return static_cast<CMarkupVolumeTagged*>(m_pReal); }

public:
    CUtlVector<CGlobalSymbol>& GroupNames() override { return Real()->m_GroupNames(); }
    void GroupNamesUpdated() override { Real()->m_GroupNames.NetworkStateChanged(); }
    CUtlVector<CGlobalSymbol>& Tags() override { return Real()->m_Tags(); }
    void TagsUpdated() override { Real()->m_Tags.NetworkStateChanged(); }
    bool& IsGroup() override { return Real()->m_bIsGroup(); }
    void IsGroupUpdated() override { Real()->m_bIsGroup.NetworkStateChanged(); }
    bool& GroupByPrefab() override { return Real()->m_bGroupByPrefab(); }
    void GroupByPrefabUpdated() override { Real()->m_bGroupByPrefab.NetworkStateChanged(); }
    bool& GroupByVolume() override { return Real()->m_bGroupByVolume(); }
    void GroupByVolumeUpdated() override { Real()->m_bGroupByVolume.NetworkStateChanged(); }
    bool& GroupOtherGroups() override { return Real()->m_bGroupOtherGroups(); }
    void GroupOtherGroupsUpdated() override { Real()->m_bGroupOtherGroups.NetworkStateChanged(); }
    bool& IsInGroup() override { return Real()->m_bIsInGroup(); }
    void IsInGroupUpdated() override { Real()->m_bIsInGroup.NetworkStateChanged(); }
};

#endif // _INCLUDE_CMARKUPVOLUMETAGGEDIMPL_H
