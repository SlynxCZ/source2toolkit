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

#ifndef _INCLUDE_CBASEMOVEBEHAVIORIMPL_H
#define _INCLUDE_CBASEMOVEBEHAVIORIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBaseMoveBehavior.h"
#include "schema/entity/classes/CBaseMoveBehavior.h"
#include "CPathKeyFrameImpl.h"

class CBaseMoveBehaviorImpl : public CPathKeyFrameImpl, public IBaseMoveBehavior
{

public:
    explicit CBaseMoveBehaviorImpl(CBaseMoveBehavior* p) : CPathKeyFrameImpl(p) {}

private:
    CBaseMoveBehavior* Real() { return static_cast<CBaseMoveBehavior*>(m_pReal); }
    CBaseMoveBehavior* Real() const { return static_cast<CBaseMoveBehavior*>(m_pReal); }

public:
    CBaseMoveBehavior* GetOriginal() const override { return Real(); }
    int32_t& PositionInterpolator() override { return Real()->m_iPositionInterpolator(); }
    void PositionInterpolatorUpdated() override { Real()->m_iPositionInterpolator.NetworkStateChanged(); }
    int32_t& RotationInterpolator() override { return Real()->m_iRotationInterpolator(); }
    void RotationInterpolatorUpdated() override { Real()->m_iRotationInterpolator.NetworkStateChanged(); }
    float& AnimStartTime() override { return Real()->m_flAnimStartTime(); }
    void AnimStartTimeUpdated() override { Real()->m_flAnimStartTime.NetworkStateChanged(); }
    float& AnimEndTime() override { return Real()->m_flAnimEndTime(); }
    void AnimEndTimeUpdated() override { Real()->m_flAnimEndTime.NetworkStateChanged(); }
    float& AverageSpeedAcrossFrame() override { return Real()->m_flAverageSpeedAcrossFrame(); }
    void AverageSpeedAcrossFrameUpdated() override { Real()->m_flAverageSpeedAcrossFrame.NetworkStateChanged(); }
    CHandle<CPathKeyFrame>& CurrentKeyFrame() override { return Real()->m_pCurrentKeyFrame(); }
    void CurrentKeyFrameUpdated() override { Real()->m_pCurrentKeyFrame.NetworkStateChanged(); }
    CHandle<CPathKeyFrame>& TargetKeyFrame() override { return Real()->m_pTargetKeyFrame(); }
    void TargetKeyFrameUpdated() override { Real()->m_pTargetKeyFrame.NetworkStateChanged(); }
    CHandle<CPathKeyFrame>& PreKeyFrame() override { return Real()->m_pPreKeyFrame(); }
    void PreKeyFrameUpdated() override { Real()->m_pPreKeyFrame.NetworkStateChanged(); }
    CHandle<CPathKeyFrame>& PostKeyFrame() override { return Real()->m_pPostKeyFrame(); }
    void PostKeyFrameUpdated() override { Real()->m_pPostKeyFrame.NetworkStateChanged(); }
    float& TimeIntoFrame() override { return Real()->m_flTimeIntoFrame(); }
    void TimeIntoFrameUpdated() override { Real()->m_flTimeIntoFrame.NetworkStateChanged(); }
    int32_t& Direction() override { return Real()->m_iDirection(); }
    void DirectionUpdated() override { Real()->m_iDirection.NetworkStateChanged(); }
};

inline IBaseMoveBehavior* CBaseMoveBehavior::ToInterface() { return new CBaseMoveBehaviorImpl(this); }
inline IBaseMoveBehavior* IBaseMoveBehavior::FromOriginal(CBaseMoveBehavior* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBASEMOVEBEHAVIORIMPL_H
