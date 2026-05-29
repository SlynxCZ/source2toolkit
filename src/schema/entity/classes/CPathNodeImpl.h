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

#ifndef _INCLUDE_CPATHNODEIMPL_H
#define _INCLUDE_CPATHNODEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPathNode.h"
#include "schema/entity/classes/CPathNode.h"
#include "CPointEntityImpl.h"

class CPathNodeImpl : public CPointEntityImpl, public IPathNode
{

public:
    explicit CPathNodeImpl(CPathNode* p) : CPointEntityImpl(p) {}

private:
    CPathNode* Real() { return static_cast<CPathNode*>(m_pReal); }
    CPathNode* Real() const { return static_cast<CPathNode*>(m_pReal); }

public:
    CPathNode* GetOriginal() const override { return Real(); }
    Vector& InTangentLocal() override { return Real()->m_vInTangentLocal(); }
    void InTangentLocalUpdated() override { Real()->m_vInTangentLocal.NetworkStateChanged(); }
    Vector& OutTangentLocal() override { return Real()->m_vOutTangentLocal(); }
    void OutTangentLocalUpdated() override { Real()->m_vOutTangentLocal.NetworkStateChanged(); }
    CUtlString& StrParentPathUniqueID() override { return Real()->m_strParentPathUniqueID(); }
    void StrParentPathUniqueIDUpdated() override { Real()->m_strParentPathUniqueID.NetworkStateChanged(); }
    CUtlString& StrPathNodeParameter() override { return Real()->m_strPathNodeParameter(); }
    void StrPathNodeParameterUpdated() override { Real()->m_strPathNodeParameter.NetworkStateChanged(); }
    CTransform& XWSPrevParent() override { return Real()->m_xWSPrevParent(); }
    void XWSPrevParentUpdated() override { Real()->m_xWSPrevParent.NetworkStateChanged(); }
    CHandle<CPathWithDynamicNodes>& Path() override { return Real()->m_hPath(); }
    void PathUpdated() override { Real()->m_hPath.NetworkStateChanged(); }
};

inline IPathNode* CPathNode::ToInterface() { return new CPathNodeImpl(this); }
inline IPathNode* IPathNode::FromOriginal(CPathNode* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPATHNODEIMPL_H
