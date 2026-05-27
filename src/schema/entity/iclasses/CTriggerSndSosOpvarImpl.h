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

#ifndef _INCLUDE_CTRIGGERSNDSOSOPVARIMPL_H
#define _INCLUDE_CTRIGGERSNDSOSOPVARIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ITriggerSndSosOpvar.h"
#include "schema/entity/classes/CTriggerSndSosOpvar.h"
#include "CBaseTriggerImpl.h"

class CTriggerSndSosOpvarImpl : public CBaseTriggerImpl, public ITriggerSndSosOpvar
{

public:
    explicit CTriggerSndSosOpvarImpl(CTriggerSndSosOpvar* p) : CBaseTriggerImpl(p) {}

private:
    CTriggerSndSosOpvar* Real() { return static_cast<CTriggerSndSosOpvar*>(m_pReal); }

public:
    CUtlVector<CHandle<CBaseEntity>>& TouchingPlayers() override { return Real()->m_hTouchingPlayers(); }
    void TouchingPlayersUpdated() override { Real()->m_hTouchingPlayers.NetworkStateChanged(); }
    Vector& Position() override { return Real()->m_flPosition(); }
    void PositionUpdated() override { Real()->m_flPosition.NetworkStateChanged(); }
    float& CenterSize() override { return Real()->m_flCenterSize(); }
    void CenterSizeUpdated() override { Real()->m_flCenterSize.NetworkStateChanged(); }
    float& MinVal() override { return Real()->m_flMinVal(); }
    void MinValUpdated() override { Real()->m_flMinVal.NetworkStateChanged(); }
    float& MaxVal() override { return Real()->m_flMaxVal(); }
    void MaxValUpdated() override { Real()->m_flMaxVal.NetworkStateChanged(); }
    CUtlSymbolLarge& OpvarName() override { return Real()->m_opvarName(); }
    void OpvarNameUpdated() override { Real()->m_opvarName.NetworkStateChanged(); }
    CUtlSymbolLarge& StackName() override { return Real()->m_stackName(); }
    void StackNameUpdated() override { Real()->m_stackName.NetworkStateChanged(); }
    CUtlSymbolLarge& OperatorName() override { return Real()->m_operatorName(); }
    void OperatorNameUpdated() override { Real()->m_operatorName.NetworkStateChanged(); }
    bool& VolIs2D() override { return Real()->m_bVolIs2D(); }
    void VolIs2DUpdated() override { Real()->m_bVolIs2D.NetworkStateChanged(); }
    char* OpvarNameChar() override { return Real()->m_opvarNameChar(); }
    char* StackNameChar() override { return Real()->m_stackNameChar(); }
    char* OperatorNameChar() override { return Real()->m_operatorNameChar(); }
    Vector& VecNormPos() override { return Real()->m_VecNormPos(); }
    void VecNormPosUpdated() override { Real()->m_VecNormPos.NetworkStateChanged(); }
    float& NormCenterSize() override { return Real()->m_flNormCenterSize(); }
    void NormCenterSizeUpdated() override { Real()->m_flNormCenterSize.NetworkStateChanged(); }
};

#endif // _INCLUDE_CTRIGGERSNDSOSOPVARIMPL_H
