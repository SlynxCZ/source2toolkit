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

#ifndef _INCLUDE_CLOGICACTIVEAUTOSAVEIMPL_H
#define _INCLUDE_CLOGICACTIVEAUTOSAVEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ILogicActiveAutosave.h"
#include "schema/entity/classes/CLogicActiveAutosave.h"
#include "CLogicAutosaveImpl.h"

class CLogicActiveAutosaveImpl : public CLogicAutosaveImpl, public ILogicActiveAutosave
{

public:
    explicit CLogicActiveAutosaveImpl(CLogicActiveAutosave* p) : CLogicAutosaveImpl(p) {}

private:
    CLogicActiveAutosave* Real() { return static_cast<CLogicActiveAutosave*>(m_pReal); }
    CLogicActiveAutosave* Real() const { return static_cast<CLogicActiveAutosave*>(m_pReal); }

public:
    CLogicActiveAutosave* GetOriginal() const override { return Real(); }
    int32_t& TriggerHitPoints() override { return Real()->m_TriggerHitPoints(); }
    void TriggerHitPointsUpdated() override { Real()->m_TriggerHitPoints.NetworkStateChanged(); }
    float& TimeToTrigger() override { return Real()->m_flTimeToTrigger(); }
    void TimeToTriggerUpdated() override { Real()->m_flTimeToTrigger.NetworkStateChanged(); }
    float& StartTime() override { return Real()->m_flStartTime(); }
    void StartTimeUpdated() override { Real()->m_flStartTime.NetworkStateChanged(); }
    float& DangerousTime() override { return Real()->m_flDangerousTime(); }
    void DangerousTimeUpdated() override { Real()->m_flDangerousTime.NetworkStateChanged(); }
};

inline ILogicActiveAutosave* CLogicActiveAutosave::ToInterface() { return new CLogicActiveAutosaveImpl(this); }
inline ILogicActiveAutosave* ILogicActiveAutosave::FromOriginal(CLogicActiveAutosave* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CLOGICACTIVEAUTOSAVEIMPL_H
