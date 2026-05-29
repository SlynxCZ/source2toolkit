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

#ifndef _INCLUDE_CBLOODIMPL_H
#define _INCLUDE_CBLOODIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBlood.h"
#include "schema/entity/classes/CBlood.h"
#include "CPointEntityImpl.h"

class CBloodImpl : public CPointEntityImpl, public IBlood
{

public:
    explicit CBloodImpl(CBlood* p) : CPointEntityImpl(p) {}

private:
    CBlood* Real() { return static_cast<CBlood*>(m_pReal); }
    CBlood* Real() const { return static_cast<CBlood*>(m_pReal); }

public:
    CBlood* GetOriginal() const override { return Real(); }
    QAngle& SprayAngles() override { return Real()->m_vecSprayAngles(); }
    void SprayAnglesUpdated() override { Real()->m_vecSprayAngles.NetworkStateChanged(); }
    Vector& SprayDir() override { return Real()->m_vecSprayDir(); }
    void SprayDirUpdated() override { Real()->m_vecSprayDir.NetworkStateChanged(); }
    float& Amount() override { return Real()->m_flAmount(); }
    void AmountUpdated() override { Real()->m_flAmount.NetworkStateChanged(); }
    BloodType& Color() override { return Real()->m_Color(); }
    void ColorUpdated() override { Real()->m_Color.NetworkStateChanged(); }
};

inline IBlood* CBlood::ToInterface() { return new CBloodImpl(this); }
inline IBlood* IBlood::FromOriginal(CBlood* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBLOODIMPL_H
