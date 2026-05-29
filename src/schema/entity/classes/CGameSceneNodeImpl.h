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

#ifndef _INCLUDE_CGAMESCENENODEIMPL_H
#define _INCLUDE_CGAMESCENENODEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IGameSceneNode.h"
#include "schema/entity/classes/CGameSceneNode.h"

class CGameSceneNodeImpl : public virtual IGameSceneNode
{

protected:
    void* m_pReal;

public:
    explicit CGameSceneNodeImpl(void* p) : m_pReal(p) {}

private:
    CGameSceneNode* Real() { return static_cast<CGameSceneNode*>(m_pReal); }
    CGameSceneNode* Real() const { return static_cast<CGameSceneNode*>(m_pReal); }

public:
    CGameSceneNode* GetOriginal() const override { return Real(); }
    CTransform& NodeToWorld() override { return Real()->m_nodeToWorld(); }
    void NodeToWorldUpdated() override { Real()->m_nodeToWorld.NetworkStateChanged(); }
    CEntityInstance*& Owner() override { return Real()->m_pOwner(); }
    void OwnerUpdated() override { Real()->m_pOwner.NetworkStateChanged(); }
    CGameSceneNode*& Parent() override { return Real()->m_pParent(); }
    void ParentUpdated() override { Real()->m_pParent.NetworkStateChanged(); }
    CGameSceneNode*& Child() override { return Real()->m_pChild(); }
    void ChildUpdated() override { Real()->m_pChild.NetworkStateChanged(); }
    CGameSceneNode*& NextSibling() override { return Real()->m_pNextSibling(); }
    void NextSiblingUpdated() override { Real()->m_pNextSibling.NetworkStateChanged(); }
    ::CNetworkOriginCellCoordQuantizedVector& Origin() override { return Real()->m_vecOrigin(); }
    void OriginUpdated() override { Real()->m_vecOrigin.NetworkStateChanged(); }
    QAngle& Rotation() override { return Real()->m_angRotation(); }
    void RotationUpdated() override { Real()->m_angRotation.NetworkStateChanged(); }
    float& Scale() override { return Real()->m_flScale(); }
    void ScaleUpdated() override { Real()->m_flScale.NetworkStateChanged(); }
    Vector& AbsOrigin() override { return Real()->m_vecAbsOrigin(); }
    void AbsOriginUpdated() override { Real()->m_vecAbsOrigin.NetworkStateChanged(); }
    QAngle& AbsRotation() override { return Real()->m_angAbsRotation(); }
    void AbsRotationUpdated() override { Real()->m_angAbsRotation.NetworkStateChanged(); }
    float& AbsScale() override { return Real()->m_flAbsScale(); }
    void AbsScaleUpdated() override { Real()->m_flAbsScale.NetworkStateChanged(); }
    int16_t& ParentAttachmentOrBone() override { return Real()->m_nParentAttachmentOrBone(); }
    void ParentAttachmentOrBoneUpdated() override { Real()->m_nParentAttachmentOrBone.NetworkStateChanged(); }
    bool& DebugAbsOriginChanges() override { return Real()->m_bDebugAbsOriginChanges(); }
    void DebugAbsOriginChangesUpdated() override { Real()->m_bDebugAbsOriginChanges.NetworkStateChanged(); }
    bool& Dormant() override { return Real()->m_bDormant(); }
    void DormantUpdated() override { Real()->m_bDormant.NetworkStateChanged(); }
    bool& ForceParentToBeNetworked() override { return Real()->m_bForceParentToBeNetworked(); }
    void ForceParentToBeNetworkedUpdated() override { Real()->m_bForceParentToBeNetworked.NetworkStateChanged(); }
    uint8_t& HierarchicalDepth() override { return Real()->m_nHierarchicalDepth(); }
    void HierarchicalDepthUpdated() override { Real()->m_nHierarchicalDepth.NetworkStateChanged(); }
    uint8_t& HierarchyType() override { return Real()->m_nHierarchyType(); }
    void HierarchyTypeUpdated() override { Real()->m_nHierarchyType.NetworkStateChanged(); }
    uint8_t& DoNotSetAnimTimeInInvalidatePhysicsCount() override { return Real()->m_nDoNotSetAnimTimeInInvalidatePhysicsCount(); }
    void DoNotSetAnimTimeInInvalidatePhysicsCountUpdated() override { Real()->m_nDoNotSetAnimTimeInInvalidatePhysicsCount.NetworkStateChanged(); }
    CUtlStringToken* Name() override { return Real()->m_name(); }
    CUtlStringToken* HierarchyAttachName() override { return Real()->m_hierarchyAttachName(); }
    float& ClientLocalScale() override { return Real()->m_flClientLocalScale(); }
    void ClientLocalScaleUpdated() override { Real()->m_flClientLocalScale.NetworkStateChanged(); }
    Vector& RenderOrigin() override { return Real()->m_vRenderOrigin(); }
    void RenderOriginUpdated() override { Real()->m_vRenderOrigin.NetworkStateChanged(); }
};

inline IGameSceneNode* CGameSceneNode::ToInterface() { return new CGameSceneNodeImpl(this); }
inline IGameSceneNode* IGameSceneNode::FromRaw(CEntityInstance*) { return nullptr; }
inline IGameSceneNode* IGameSceneNode::FromOriginal(CGameSceneNode* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CGAMESCENENODEIMPL_H
