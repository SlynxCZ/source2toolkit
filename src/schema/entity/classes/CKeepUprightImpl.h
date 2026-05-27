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

#ifndef _INCLUDE_CKEEPUPRIGHTIMPL_H
#define _INCLUDE_CKEEPUPRIGHTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IKeepUpright.h"
#include "schema/entity/classes/CKeepUpright.h"
#include "CPointEntityImpl.h"

class CKeepUprightImpl : public CPointEntityImpl, public IKeepUpright
{

public:
    explicit CKeepUprightImpl(CKeepUpright* p) : CPointEntityImpl(p) {}

private:
    CKeepUpright* Real() { return static_cast<CKeepUpright*>(m_pReal); }

public:
    Vector& WorldGoalAxis() override { return Real()->m_worldGoalAxis(); }
    void WorldGoalAxisUpdated() override { Real()->m_worldGoalAxis.NetworkStateChanged(); }
    Vector& LocalTestAxis() override { return Real()->m_localTestAxis(); }
    void LocalTestAxisUpdated() override { Real()->m_localTestAxis.NetworkStateChanged(); }
    IPhysicsMotionController*& Controller() override { return Real()->m_pController(); }
    void ControllerUpdated() override { Real()->m_pController.NetworkStateChanged(); }
    CUtlSymbolLarge& NameAttach() override { return Real()->m_nameAttach(); }
    void NameAttachUpdated() override { Real()->m_nameAttach.NetworkStateChanged(); }
    CHandle<CBaseEntity>& AttachedObject() override { return Real()->m_attachedObject(); }
    void AttachedObjectUpdated() override { Real()->m_attachedObject.NetworkStateChanged(); }
    float& AngularLimit() override { return Real()->m_angularLimit(); }
    void AngularLimitUpdated() override { Real()->m_angularLimit.NetworkStateChanged(); }
    bool& Active() override { return Real()->m_bActive(); }
    void ActiveUpdated() override { Real()->m_bActive.NetworkStateChanged(); }
    bool& DampAllRotation() override { return Real()->m_bDampAllRotation(); }
    void DampAllRotationUpdated() override { Real()->m_bDampAllRotation.NetworkStateChanged(); }
};

#endif // _INCLUDE_CKEEPUPRIGHTIMPL_H
