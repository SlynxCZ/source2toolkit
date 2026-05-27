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

#ifndef _INCLUDE_CPOINTHURTIMPL_H
#define _INCLUDE_CPOINTHURTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointHurt.h"
#include "schema/entity/classes/CPointHurt.h"
#include "CPointEntityImpl.h"

class CPointHurtImpl : public CPointEntityImpl, public IPointHurt
{

public:
    explicit CPointHurtImpl(CPointHurt* p) : CPointEntityImpl(p) {}

private:
    CPointHurt* Real() { return static_cast<CPointHurt*>(m_pReal); }

public:
    int32_t& Damage() override { return Real()->m_nDamage(); }
    void DamageUpdated() override { Real()->m_nDamage.NetworkStateChanged(); }
    DamageTypes_t& BitsDamageType() override { return Real()->m_bitsDamageType(); }
    void BitsDamageTypeUpdated() override { Real()->m_bitsDamageType.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_flRadius(); }
    void RadiusUpdated() override { Real()->m_flRadius.NetworkStateChanged(); }
    float& Delay() override { return Real()->m_flDelay(); }
    void DelayUpdated() override { Real()->m_flDelay.NetworkStateChanged(); }
    CUtlSymbolLarge& StrTarget() override { return Real()->m_strTarget(); }
    void StrTargetUpdated() override { Real()->m_strTarget.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Activator() override { return Real()->m_pActivator(); }
    void ActivatorUpdated() override { Real()->m_pActivator.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPOINTHURTIMPL_H
