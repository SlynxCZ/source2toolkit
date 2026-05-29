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

#ifndef _INCLUDE_CECONITEMATTRIBUTEIMPL_H
#define _INCLUDE_CECONITEMATTRIBUTEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEconItemAttribute.h"
#include "schema/entity/classes/CEconItemAttribute.h"

class CEconItemAttributeImpl : public virtual IEconItemAttribute
{

protected:
    void* m_pReal;

public:
    explicit CEconItemAttributeImpl(void* p) : m_pReal(p) {}

private:
    CEconItemAttribute* Real() { return static_cast<CEconItemAttribute*>(m_pReal); }
    CEconItemAttribute* Real() const { return static_cast<CEconItemAttribute*>(m_pReal); }

public:
    CEconItemAttribute* GetOriginal() const override { return Real(); }
    uint16_t& AttributeDefinitionIndex() override { return Real()->m_iAttributeDefinitionIndex(); }
    void AttributeDefinitionIndexUpdated() override { Real()->m_iAttributeDefinitionIndex.NetworkStateChanged(); }
    float& Value() override { return Real()->m_flValue(); }
    void ValueUpdated() override { Real()->m_flValue.NetworkStateChanged(); }
    float& InitialValue() override { return Real()->m_flInitialValue(); }
    void InitialValueUpdated() override { Real()->m_flInitialValue.NetworkStateChanged(); }
    int32_t& RefundableCurrency() override { return Real()->m_nRefundableCurrency(); }
    void RefundableCurrencyUpdated() override { Real()->m_nRefundableCurrency.NetworkStateChanged(); }
    bool& SetBonus() override { return Real()->m_bSetBonus(); }
    void SetBonusUpdated() override { Real()->m_bSetBonus.NetworkStateChanged(); }
};

inline IEconItemAttribute* CEconItemAttribute::ToInterface() { return new CEconItemAttributeImpl(this); }
inline IEconItemAttribute* IEconItemAttribute::FromRaw(CEntityInstance*) { return nullptr; }
inline IEconItemAttribute* IEconItemAttribute::FromOriginal(CEconItemAttribute* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CECONITEMATTRIBUTEIMPL_H
