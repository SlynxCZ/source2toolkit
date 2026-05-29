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

#ifndef _INCLUDE_CFUNCMOVELINEARIMPL_H
#define _INCLUDE_CFUNCMOVELINEARIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IFuncMoveLinear.h"
#include "schema/entity/classes/CFuncMoveLinear.h"
#include "CBaseToggleImpl.h"

class CFuncMoveLinearImpl : public CBaseToggleImpl, public IFuncMoveLinear
{

public:
    explicit CFuncMoveLinearImpl(CFuncMoveLinear* p) : CBaseToggleImpl(p) {}

private:
    CFuncMoveLinear* Real() { return static_cast<CFuncMoveLinear*>(m_pReal); }
    CFuncMoveLinear* Real() const { return static_cast<CFuncMoveLinear*>(m_pReal); }

public:
    CFuncMoveLinear* GetOriginal() const override { return Real(); }
    ::MoveLinearAuthoredPos_t& AuthoredPosition() override { return Real()->m_authoredPosition(); }
    void AuthoredPositionUpdated() override { Real()->m_authoredPosition.NetworkStateChanged(); }
    QAngle& MoveEntitySpace() override { return Real()->m_angMoveEntitySpace(); }
    void MoveEntitySpaceUpdated() override { Real()->m_angMoveEntitySpace.NetworkStateChanged(); }
    Vector& MoveDirParentSpace() override { return Real()->m_vecMoveDirParentSpace(); }
    void MoveDirParentSpaceUpdated() override { Real()->m_vecMoveDirParentSpace.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundStart() override { return Real()->m_soundStart(); }
    void SoundStartUpdated() override { Real()->m_soundStart.NetworkStateChanged(); }
    CUtlSymbolLarge& SoundStop() override { return Real()->m_soundStop(); }
    void SoundStopUpdated() override { Real()->m_soundStop.NetworkStateChanged(); }
    CUtlSymbolLarge& CurrentSound() override { return Real()->m_currentSound(); }
    void CurrentSoundUpdated() override { Real()->m_currentSound.NetworkStateChanged(); }
    float& BlockDamage() override { return Real()->m_flBlockDamage(); }
    void BlockDamageUpdated() override { Real()->m_flBlockDamage.NetworkStateChanged(); }
    float& StartPosition() override { return Real()->m_flStartPosition(); }
    void StartPositionUpdated() override { Real()->m_flStartPosition.NetworkStateChanged(); }
    ::CEntityIOOutput& OnFullyOpen() override { return Real()->m_OnFullyOpen(); }
    void OnFullyOpenUpdated() override { Real()->m_OnFullyOpen.NetworkStateChanged(); }
    ::CEntityIOOutput& OnFullyClosed() override { return Real()->m_OnFullyClosed(); }
    void OnFullyClosedUpdated() override { Real()->m_OnFullyClosed.NetworkStateChanged(); }
    bool& CreateMovableNavMesh() override { return Real()->m_bCreateMovableNavMesh(); }
    void CreateMovableNavMeshUpdated() override { Real()->m_bCreateMovableNavMesh.NetworkStateChanged(); }
    bool& AllowMovableNavMeshDockingOnEntireEntity() override { return Real()->m_bAllowMovableNavMeshDockingOnEntireEntity(); }
    void AllowMovableNavMeshDockingOnEntireEntityUpdated() override { Real()->m_bAllowMovableNavMeshDockingOnEntireEntity.NetworkStateChanged(); }
    bool& CreateNavObstacle() override { return Real()->m_bCreateNavObstacle(); }
    void CreateNavObstacleUpdated() override { Real()->m_bCreateNavObstacle.NetworkStateChanged(); }
};

inline IFuncMoveLinear* CFuncMoveLinear::ToInterface() { return new CFuncMoveLinearImpl(this); }
inline IFuncMoveLinear* IFuncMoveLinear::FromOriginal(CFuncMoveLinear* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CFUNCMOVELINEARIMPL_H
