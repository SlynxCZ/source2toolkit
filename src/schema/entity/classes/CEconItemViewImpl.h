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

#ifndef _INCLUDE_CECONITEMVIEWIMPL_H
#define _INCLUDE_CECONITEMVIEWIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEconItemView.h"
#include "schema/entity/classes/CEconItemView.h"
#include "IEconItemInterfaceImpl.h"

class CEconItemViewImpl : public IEconItemInterfaceImpl, public IEconItemView
{

public:
    explicit CEconItemViewImpl(CEconItemView* p) : IEconItemInterfaceImpl(p) {}

private:
    CEconItemView* Real() { return static_cast<CEconItemView*>(m_pReal); }
    CEconItemView* Real() const { return static_cast<CEconItemView*>(m_pReal); }

public:
    CEconItemView* GetOriginal() const override { return Real(); }
    uint16_t& ItemDefinitionIndex() override { return Real()->m_iItemDefinitionIndex(); }
    void ItemDefinitionIndexUpdated() override { Real()->m_iItemDefinitionIndex.NetworkStateChanged(); }
    int32_t& EntityQuality() override { return Real()->m_iEntityQuality(); }
    void EntityQualityUpdated() override { Real()->m_iEntityQuality.NetworkStateChanged(); }
    uint32_t& EntityLevel() override { return Real()->m_iEntityLevel(); }
    void EntityLevelUpdated() override { Real()->m_iEntityLevel.NetworkStateChanged(); }
    uint64_t& ItemID() override { return Real()->m_iItemID(); }
    void ItemIDUpdated() override { Real()->m_iItemID.NetworkStateChanged(); }
    uint32_t& ItemIDHigh() override { return Real()->m_iItemIDHigh(); }
    void ItemIDHighUpdated() override { Real()->m_iItemIDHigh.NetworkStateChanged(); }
    uint32_t& ItemIDLow() override { return Real()->m_iItemIDLow(); }
    void ItemIDLowUpdated() override { Real()->m_iItemIDLow.NetworkStateChanged(); }
    uint32_t& AccountID() override { return Real()->m_iAccountID(); }
    void AccountIDUpdated() override { Real()->m_iAccountID.NetworkStateChanged(); }
    uint32_t& InventoryPosition() override { return Real()->m_iInventoryPosition(); }
    void InventoryPositionUpdated() override { Real()->m_iInventoryPosition.NetworkStateChanged(); }
    bool& Initialized() override { return Real()->m_bInitialized(); }
    void InitializedUpdated() override { Real()->m_bInitialized.NetworkStateChanged(); }
    CAttributeList& AttributeList() override { return Real()->m_AttributeList(); }
    void AttributeListUpdated() override { Real()->m_AttributeList.NetworkStateChanged(); }
    CAttributeList& NetworkedDynamicAttributes() override { return Real()->m_NetworkedDynamicAttributes(); }
    void NetworkedDynamicAttributesUpdated() override { Real()->m_NetworkedDynamicAttributes.NetworkStateChanged(); }
    char* CustomName() override { return Real()->m_szCustomName(); }
    char* CustomNameOverride() override { return Real()->m_szCustomNameOverride(); }
};

inline IEconItemView* CEconItemView::ToInterface() { return new CEconItemViewImpl(this); }
inline IEconItemView* IEconItemView::FromOriginal(CEconItemView* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CECONITEMVIEWIMPL_H
