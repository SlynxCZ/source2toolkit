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

#ifndef _INCLUDE_CPATHKEYFRAMEIMPL_H
#define _INCLUDE_CPATHKEYFRAMEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IPathKeyFrame.h"
#include "schema/entity/classes/CPathKeyFrame.h"
#include "CLogicalEntityImpl.h"

class CPathKeyFrameImpl : public CLogicalEntityImpl, public IPathKeyFrame
{

public:
    explicit CPathKeyFrameImpl(CPathKeyFrame* p) : CLogicalEntityImpl(p) {}

private:
    CPathKeyFrame* Real() { return static_cast<CPathKeyFrame*>(m_pReal); }

public:
    Vector& Origin() override { return Real()->m_Origin(); }
    void OriginUpdated() override { Real()->m_Origin.NetworkStateChanged(); }
    QAngle& Angles() override { return Real()->m_Angles(); }
    void AnglesUpdated() override { Real()->m_Angles.NetworkStateChanged(); }
    Quaternion& Angle() override { return Real()->m_qAngle(); }
    void AngleUpdated() override { Real()->m_qAngle.NetworkStateChanged(); }
    CUtlSymbolLarge& NextKey() override { return Real()->m_iNextKey(); }
    void NextKeyUpdated() override { Real()->m_iNextKey.NetworkStateChanged(); }
    float& NextTime() override { return Real()->m_flNextTime(); }
    void NextTimeUpdated() override { Real()->m_flNextTime.NetworkStateChanged(); }
    CHandle<CPathKeyFrame>& NextKey() override { return Real()->m_pNextKey(); }
    void NextKeyUpdated() override { Real()->m_pNextKey.NetworkStateChanged(); }
    CHandle<CPathKeyFrame>& PrevKey() override { return Real()->m_pPrevKey(); }
    void PrevKeyUpdated() override { Real()->m_pPrevKey.NetworkStateChanged(); }
    float& MoveSpeed() override { return Real()->m_flMoveSpeed(); }
    void MoveSpeedUpdated() override { Real()->m_flMoveSpeed.NetworkStateChanged(); }
};

#endif // _INCLUDE_CPATHKEYFRAMEIMPL_H
