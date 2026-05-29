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

#ifndef _INCLUDE_CATTRIBUTEMANAGERIMPL_H
#define _INCLUDE_CATTRIBUTEMANAGERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IAttributeManager.h"
#include "schema/entity/classes/CAttributeManager.h"

class CAttributeManagerImpl : public virtual IAttributeManager
{

protected:
    void* m_pReal;

public:
    explicit CAttributeManagerImpl(void* p) : m_pReal(p) {}

private:
    CAttributeManager* Real() { return static_cast<CAttributeManager*>(m_pReal); }
    CAttributeManager* Real() const { return static_cast<CAttributeManager*>(m_pReal); }

public:
    CAttributeManager* GetOriginal() const override { return Real(); }
    CUtlVector<CHandle<CBaseEntity>>& Providers() override { return Real()->m_Providers(); }
    void ProvidersUpdated() override { Real()->m_Providers.NetworkStateChanged(); }
    int32_t& ReapplyProvisionParity() override { return Real()->m_iReapplyProvisionParity(); }
    void ReapplyProvisionParityUpdated() override { Real()->m_iReapplyProvisionParity.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Outer() override { return Real()->m_hOuter(); }
    void OuterUpdated() override { Real()->m_hOuter.NetworkStateChanged(); }
    bool& PreventLoopback() override { return Real()->m_bPreventLoopback(); }
    void PreventLoopbackUpdated() override { Real()->m_bPreventLoopback.NetworkStateChanged(); }
    ::attributeprovidertypes_t& ProviderType() override { return Real()->m_ProviderType(); }
    void ProviderTypeUpdated() override { Real()->m_ProviderType.NetworkStateChanged(); }
    CUtlVector<CAttributeManager__cached_attribute_float_t>& CachedResults() override { return Real()->m_CachedResults(); }
    void CachedResultsUpdated() override { Real()->m_CachedResults.NetworkStateChanged(); }
};

inline IAttributeManager* CAttributeManager::ToInterface() { return new CAttributeManagerImpl(this); }
inline IAttributeManager* IAttributeManager::FromRaw(CEntityInstance*) { return nullptr; }
inline IAttributeManager* IAttributeManager::FromOriginal(CAttributeManager* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CATTRIBUTEMANAGERIMPL_H
