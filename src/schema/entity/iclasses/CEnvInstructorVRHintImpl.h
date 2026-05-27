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

#ifndef _INCLUDE_CENVINSTRUCTORVRHINTIMPL_H
#define _INCLUDE_CENVINSTRUCTORVRHINTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IEnvInstructorVRHint.h"
#include "schema/entity/classes/CEnvInstructorVRHint.h"
#include "CPointEntityImpl.h"

class CEnvInstructorVRHintImpl : public CPointEntityImpl, public IEnvInstructorVRHint
{

public:
    explicit CEnvInstructorVRHintImpl(CEnvInstructorVRHint* p) : CPointEntityImpl(p) {}

private:
    CEnvInstructorVRHint* Real() { return static_cast<CEnvInstructorVRHint*>(m_pReal); }

public:
    CUtlSymbolLarge& Name() override { return Real()->m_iszName(); }
    void NameUpdated() override { Real()->m_iszName.NetworkStateChanged(); }
    CUtlSymbolLarge& HintTargetEntity() override { return Real()->m_iszHintTargetEntity(); }
    void HintTargetEntityUpdated() override { Real()->m_iszHintTargetEntity.NetworkStateChanged(); }
    int32_t& Timeout() override { return Real()->m_iTimeout(); }
    void TimeoutUpdated() override { Real()->m_iTimeout.NetworkStateChanged(); }
    CUtlSymbolLarge& Caption() override { return Real()->m_iszCaption(); }
    void CaptionUpdated() override { Real()->m_iszCaption.NetworkStateChanged(); }
    CUtlSymbolLarge& StartSound() override { return Real()->m_iszStartSound(); }
    void StartSoundUpdated() override { Real()->m_iszStartSound.NetworkStateChanged(); }
    int32_t& LayoutFileType() override { return Real()->m_iLayoutFileType(); }
    void LayoutFileTypeUpdated() override { Real()->m_iLayoutFileType.NetworkStateChanged(); }
    CUtlSymbolLarge& CustomLayoutFile() override { return Real()->m_iszCustomLayoutFile(); }
    void CustomLayoutFileUpdated() override { Real()->m_iszCustomLayoutFile.NetworkStateChanged(); }
    int32_t& AttachType() override { return Real()->m_iAttachType(); }
    void AttachTypeUpdated() override { Real()->m_iAttachType.NetworkStateChanged(); }
    float& HeightOffset() override { return Real()->m_flHeightOffset(); }
    void HeightOffsetUpdated() override { Real()->m_flHeightOffset.NetworkStateChanged(); }
};

#endif // _INCLUDE_CENVINSTRUCTORVRHINTIMPL_H
