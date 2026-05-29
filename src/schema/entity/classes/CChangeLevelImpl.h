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

#ifndef _INCLUDE_CCHANGELEVELIMPL_H
#define _INCLUDE_CCHANGELEVELIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IChangeLevel.h"
#include "schema/entity/classes/CChangeLevel.h"
#include "CBaseTriggerImpl.h"

class CChangeLevelImpl : public CBaseTriggerImpl, public IChangeLevel
{

public:
    explicit CChangeLevelImpl(CChangeLevel* p) : CBaseTriggerImpl(p) {}

private:
    CChangeLevel* Real() { return static_cast<CChangeLevel*>(m_pReal); }
    CChangeLevel* Real() const { return static_cast<CChangeLevel*>(m_pReal); }

public:
    CChangeLevel* GetOriginal() const override { return Real(); }
    CUtlString& MapName() override { return Real()->m_sMapName(); }
    void MapNameUpdated() override { Real()->m_sMapName.NetworkStateChanged(); }
    CUtlString& LandmarkName() override { return Real()->m_sLandmarkName(); }
    void LandmarkNameUpdated() override { Real()->m_sLandmarkName.NetworkStateChanged(); }
    ::CEntityIOOutput& OnChangeLevel() override { return Real()->m_OnChangeLevel(); }
    void OnChangeLevelUpdated() override { Real()->m_OnChangeLevel.NetworkStateChanged(); }
    bool& Touched() override { return Real()->m_bTouched(); }
    void TouchedUpdated() override { Real()->m_bTouched.NetworkStateChanged(); }
    bool& NoTouch() override { return Real()->m_bNoTouch(); }
    void NoTouchUpdated() override { Real()->m_bNoTouch.NetworkStateChanged(); }
    bool& NewChapter() override { return Real()->m_bNewChapter(); }
    void NewChapterUpdated() override { Real()->m_bNewChapter.NetworkStateChanged(); }
    bool& OnChangeLevelFired() override { return Real()->m_bOnChangeLevelFired(); }
    void OnChangeLevelFiredUpdated() override { Real()->m_bOnChangeLevelFired.NetworkStateChanged(); }
};

inline IChangeLevel* CChangeLevel::ToInterface() { return new CChangeLevelImpl(this); }
inline IChangeLevel* IChangeLevel::FromOriginal(CChangeLevel* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCHANGELEVELIMPL_H
