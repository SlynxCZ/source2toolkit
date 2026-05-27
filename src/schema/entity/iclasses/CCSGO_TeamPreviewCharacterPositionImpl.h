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

#ifndef _INCLUDE_CCSGO_TEAMPREVIEWCHARACTERPOSITIONIMPL_H
#define _INCLUDE_CCSGO_TEAMPREVIEWCHARACTERPOSITIONIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ICSGO_TeamPreviewCharacterPosition.h"
#include "schema/entity/classes/CCSGO_TeamPreviewCharacterPosition.h"
#include "CBaseEntityImpl.h"

class CCSGO_TeamPreviewCharacterPositionImpl : public CBaseEntityImpl, public ICSGO_TeamPreviewCharacterPosition
{

public:
    explicit CCSGO_TeamPreviewCharacterPositionImpl(CCSGO_TeamPreviewCharacterPosition* p) : CBaseEntityImpl(p) {}

private:
    CCSGO_TeamPreviewCharacterPosition* Real() { return static_cast<CCSGO_TeamPreviewCharacterPosition*>(m_pReal); }

public:
    int32_t& Variant() override { return Real()->m_nVariant(); }
    void VariantUpdated() override { Real()->m_nVariant.NetworkStateChanged(); }
    int32_t& Random() override { return Real()->m_nRandom(); }
    void RandomUpdated() override { Real()->m_nRandom.NetworkStateChanged(); }
    int32_t& Ordinal() override { return Real()->m_nOrdinal(); }
    void OrdinalUpdated() override { Real()->m_nOrdinal.NetworkStateChanged(); }
    CUtlString& WeaponName() override { return Real()->m_sWeaponName(); }
    void WeaponNameUpdated() override { Real()->m_sWeaponName.NetworkStateChanged(); }
    uint64_t& Xuid() override { return Real()->m_xuid(); }
    void XuidUpdated() override { Real()->m_xuid.NetworkStateChanged(); }
    CEconItemView& AgentItem() override { return Real()->m_agentItem(); }
    void AgentItemUpdated() override { Real()->m_agentItem.NetworkStateChanged(); }
    CEconItemView& GlovesItem() override { return Real()->m_glovesItem(); }
    void GlovesItemUpdated() override { Real()->m_glovesItem.NetworkStateChanged(); }
    CEconItemView& WeaponItem() override { return Real()->m_weaponItem(); }
    void WeaponItemUpdated() override { Real()->m_weaponItem.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCSGO_TEAMPREVIEWCHARACTERPOSITIONIMPL_H
