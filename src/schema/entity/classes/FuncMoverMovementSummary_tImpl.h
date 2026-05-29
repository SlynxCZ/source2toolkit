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

#ifndef _INCLUDE_FUNCMOVERMOVEMENTSUMMARY_TIMPL_H
#define _INCLUDE_FUNCMOVERMOVEMENTSUMMARY_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IFuncMoverMovementSummary_t.h"
#include "schema/entity/classes/FuncMoverMovementSummary_t.h"

class FuncMoverMovementSummary_tImpl : public virtual IFuncMoverMovementSummary_t
{

protected:
    void* m_pReal;

public:
    explicit FuncMoverMovementSummary_tImpl(void* p) : m_pReal(p) {}

private:
    FuncMoverMovementSummary_t* Real() { return static_cast<FuncMoverMovementSummary_t*>(m_pReal); }
    FuncMoverMovementSummary_t* Real() const { return static_cast<FuncMoverMovementSummary_t*>(m_pReal); }

public:
    FuncMoverMovementSummary_t* GetOriginal() const override { return Real(); }
    float& StartT() override { return Real()->flStartT(); }
    void StartTUpdated() override { Real()->flStartT.NetworkStateChanged(); }
    float& EndT() override { return Real()->flEndT(); }
    void EndTUpdated() override { Real()->flEndT.NetworkStateChanged(); }
    int32_t& StartNodeIndex() override { return Real()->nStartNodeIndex(); }
    void StartNodeIndexUpdated() override { Real()->nStartNodeIndex.NetworkStateChanged(); }
    int32_t& StopNodeIndex() override { return Real()->nStopNodeIndex(); }
    void StopNodeIndexUpdated() override { Real()->nStopNodeIndex.NetworkStateChanged(); }
    int32_t& MovementMode() override { return Real()->nMovementMode(); }
    void MovementModeUpdated() override { Real()->nMovementMode.NetworkStateChanged(); }
    FuncMoverMovementSummaryFlags_t& Flags() override { return Real()->nFlags(); }
    void FlagsUpdated() override { Real()->nFlags.NetworkStateChanged(); }
    int32_t& Tick() override { return Real()->nTick(); }
    void TickUpdated() override { Real()->nTick.NetworkStateChanged(); }
    CHandle<CPathMover>& PathMover() override { return Real()->hPathMover(); }
    void PathMoverUpdated() override { Real()->hPathMover.NetworkStateChanged(); }
};

inline IFuncMoverMovementSummary_t* FuncMoverMovementSummary_t::ToInterface() { return new FuncMoverMovementSummary_tImpl(this); }
inline IFuncMoverMovementSummary_t* IFuncMoverMovementSummary_t::FromOriginal(FuncMoverMovementSummary_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_FUNCMOVERMOVEMENTSUMMARY_TIMPL_H
