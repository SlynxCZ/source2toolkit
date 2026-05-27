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

#ifndef _INCLUDE_CLOGICMEASUREMOVEMENTIMPL_H
#define _INCLUDE_CLOGICMEASUREMOVEMENTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ILogicMeasureMovement.h"
#include "schema/entity/classes/CLogicMeasureMovement.h"
#include "CLogicalEntityImpl.h"

class CLogicMeasureMovementImpl : public CLogicalEntityImpl, public ILogicMeasureMovement
{

public:
    explicit CLogicMeasureMovementImpl(CLogicMeasureMovement* p) : CLogicalEntityImpl(p) {}

private:
    CLogicMeasureMovement* Real() { return static_cast<CLogicMeasureMovement*>(m_pReal); }

public:
    CUtlSymbolLarge& StrMeasureTarget() override { return Real()->m_strMeasureTarget(); }
    void StrMeasureTargetUpdated() override { Real()->m_strMeasureTarget.NetworkStateChanged(); }
    CUtlSymbolLarge& StrMeasureReference() override { return Real()->m_strMeasureReference(); }
    void StrMeasureReferenceUpdated() override { Real()->m_strMeasureReference.NetworkStateChanged(); }
    CUtlSymbolLarge& StrTargetReference() override { return Real()->m_strTargetReference(); }
    void StrTargetReferenceUpdated() override { Real()->m_strTargetReference.NetworkStateChanged(); }
    CHandle<CBaseEntity>& MeasureTarget() override { return Real()->m_hMeasureTarget(); }
    void MeasureTargetUpdated() override { Real()->m_hMeasureTarget.NetworkStateChanged(); }
    CHandle<CBaseEntity>& MeasureReference() override { return Real()->m_hMeasureReference(); }
    void MeasureReferenceUpdated() override { Real()->m_hMeasureReference.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Target() override { return Real()->m_hTarget(); }
    void TargetUpdated() override { Real()->m_hTarget.NetworkStateChanged(); }
    CHandle<CBaseEntity>& TargetReference() override { return Real()->m_hTargetReference(); }
    void TargetReferenceUpdated() override { Real()->m_hTargetReference.NetworkStateChanged(); }
    float& Scale() override { return Real()->m_flScale(); }
    void ScaleUpdated() override { Real()->m_flScale.NetworkStateChanged(); }
    int32_t& MeasureType() override { return Real()->m_nMeasureType(); }
    void MeasureTypeUpdated() override { Real()->m_nMeasureType.NetworkStateChanged(); }
};

#endif // _INCLUDE_CLOGICMEASUREMOVEMENTIMPL_H
