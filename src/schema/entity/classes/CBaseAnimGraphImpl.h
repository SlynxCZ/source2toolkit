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

#ifndef _INCLUDE_CBASEANIMGRAPHIMPL_H
#define _INCLUDE_CBASEANIMGRAPHIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBaseAnimGraph.h"
#include "schema/entity/classes/CBaseAnimGraph.h"
#include "CBaseModelEntityImpl.h"

class CBaseAnimGraphImpl : public CBaseModelEntityImpl, public IBaseAnimGraph
{

public:
    explicit CBaseAnimGraphImpl(CBaseAnimGraph* p) : CBaseModelEntityImpl(p) {}

private:
    CBaseAnimGraph* Real() { return static_cast<CBaseAnimGraph*>(m_pReal); }
    CBaseAnimGraph* Real() const { return static_cast<CBaseAnimGraph*>(m_pReal); }

public:
    CBaseAnimGraph* GetOriginal() const override { return Real(); }
    ::CAnimGraphControllerManager& GraphControllerManager() override { return Real()->m_graphControllerManager(); }
    void GraphControllerManagerUpdated() override { Real()->m_graphControllerManager.NetworkStateChanged(); }
    CAnimGraphControllerBase*& MainGraphController() override { return Real()->m_pMainGraphController(); }
    void MainGraphControllerUpdated() override { Real()->m_pMainGraphController.NetworkStateChanged(); }
    bool& InitiallyPopulateInterpHistory() override { return Real()->m_bInitiallyPopulateInterpHistory(); }
    void InitiallyPopulateInterpHistoryUpdated() override { Real()->m_bInitiallyPopulateInterpHistory.NetworkStateChanged(); }
    IChoreoServices*& ChoreoServices() override { return Real()->m_pChoreoServices(); }
    void ChoreoServicesUpdated() override { Real()->m_pChoreoServices.NetworkStateChanged(); }
    bool& AnimGraphUpdateEnabled() override { return Real()->m_bAnimGraphUpdateEnabled(); }
    void AnimGraphUpdateEnabledUpdated() override { Real()->m_bAnimGraphUpdateEnabled.NetworkStateChanged(); }
    bool& AnimationUpdateScheduled() override { return Real()->m_bAnimationUpdateScheduled(); }
    void AnimationUpdateScheduledUpdated() override { Real()->m_bAnimationUpdateScheduled.NetworkStateChanged(); }
    Vector& Force() override { return Real()->m_vecForce(); }
    void ForceUpdated() override { Real()->m_vecForce.NetworkStateChanged(); }
    int32_t& ForceBone() override { return Real()->m_nForceBone(); }
    void ForceBoneUpdated() override { Real()->m_nForceBone.NetworkStateChanged(); }
    IPhysicsRagdollControl*& RagdollControl() override { return Real()->m_pRagdollControl(); }
    void RagdollControlUpdated() override { Real()->m_pRagdollControl.NetworkStateChanged(); }
    ::PhysicsRagdollPose_t& RagdollPose() override { return Real()->m_RagdollPose(); }
    void RagdollPoseUpdated() override { Real()->m_RagdollPose.NetworkStateChanged(); }
    bool& RagdollEnabled() override { return Real()->m_bRagdollEnabled(); }
    void RagdollEnabledUpdated() override { Real()->m_bRagdollEnabled.NetworkStateChanged(); }
    bool& RagdollClientSide() override { return Real()->m_bRagdollClientSide(); }
    void RagdollClientSideUpdated() override { Real()->m_bRagdollClientSide.NetworkStateChanged(); }
    CTransform& XParentedRagdollRootInEntitySpace() override { return Real()->m_xParentedRagdollRootInEntitySpace(); }
    void XParentedRagdollRootInEntitySpaceUpdated() override { Real()->m_xParentedRagdollRootInEntitySpace.NetworkStateChanged(); }
};

inline IBaseAnimGraph* CBaseAnimGraph::ToInterface() { return new CBaseAnimGraphImpl(this); }
inline IBaseAnimGraph* IBaseAnimGraph::FromOriginal(CBaseAnimGraph* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBASEANIMGRAPHIMPL_H
