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

#ifndef _INCLUDE_CAI_CHANGEHINTGROUPIMPL_H
#define _INCLUDE_CAI_CHANGEHINTGROUPIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IAI_ChangeHintGroup.h"
#include "schema/entity/classes/CAI_ChangeHintGroup.h"
#include "CBaseEntityImpl.h"

class CAI_ChangeHintGroupImpl : public CBaseEntityImpl, public IAI_ChangeHintGroup
{

public:
    explicit CAI_ChangeHintGroupImpl(CAI_ChangeHintGroup* p) : CBaseEntityImpl(p) {}

private:
    CAI_ChangeHintGroup* Real() { return static_cast<CAI_ChangeHintGroup*>(m_pReal); }

public:
    int32_t& SearchType() override { return Real()->m_iSearchType(); }
    void SearchTypeUpdated() override { Real()->m_iSearchType.NetworkStateChanged(); }
    CUtlSymbolLarge& StrSearchName() override { return Real()->m_strSearchName(); }
    void StrSearchNameUpdated() override { Real()->m_strSearchName.NetworkStateChanged(); }
    CUtlSymbolLarge& StrNewHintGroup() override { return Real()->m_strNewHintGroup(); }
    void StrNewHintGroupUpdated() override { Real()->m_strNewHintGroup.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_flRadius(); }
    void RadiusUpdated() override { Real()->m_flRadius.NetworkStateChanged(); }
};

#endif // _INCLUDE_CAI_CHANGEHINTGROUPIMPL_H
