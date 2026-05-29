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

#ifndef _INCLUDE_CPATHTRACKIMPL_H
#define _INCLUDE_CPATHTRACKIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPathTrack.h"
#include "schema/entity/classes/CPathTrack.h"
#include "CPointEntityImpl.h"

class CPathTrackImpl : public CPointEntityImpl, public IPathTrack
{

public:
    explicit CPathTrackImpl(CPathTrack* p) : CPointEntityImpl(p) {}

private:
    CPathTrack* Real() { return static_cast<CPathTrack*>(m_pReal); }
    CPathTrack* Real() const { return static_cast<CPathTrack*>(m_pReal); }

public:
    CPathTrack* GetOriginal() const override { return Real(); }
    CHandle<CPathTrack>& Pnext() override { return Real()->m_pnext(); }
    void PnextUpdated() override { Real()->m_pnext.NetworkStateChanged(); }
    CHandle<CPathTrack>& Pprevious() override { return Real()->m_pprevious(); }
    void PpreviousUpdated() override { Real()->m_pprevious.NetworkStateChanged(); }
    CHandle<CPathTrack>& Paltpath() override { return Real()->m_paltpath(); }
    void PaltpathUpdated() override { Real()->m_paltpath.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_flRadius(); }
    void RadiusUpdated() override { Real()->m_flRadius.NetworkStateChanged(); }
    float& Length() override { return Real()->m_length(); }
    void LengthUpdated() override { Real()->m_length.NetworkStateChanged(); }
    CUtlSymbolLarge& AltName() override { return Real()->m_altName(); }
    void AltNameUpdated() override { Real()->m_altName.NetworkStateChanged(); }
    int32_t& IterVal() override { return Real()->m_nIterVal(); }
    void IterValUpdated() override { Real()->m_nIterVal.NetworkStateChanged(); }
    ::TrackOrientationType_t& OrientationType() override { return Real()->m_eOrientationType(); }
    void OrientationTypeUpdated() override { Real()->m_eOrientationType.NetworkStateChanged(); }
    ::CEntityIOOutput& OnPass() override { return Real()->m_OnPass(); }
    void OnPassUpdated() override { Real()->m_OnPass.NetworkStateChanged(); }
};

inline IPathTrack* CPathTrack::ToInterface() { return new CPathTrackImpl(this); }
inline IPathTrack* IPathTrack::FromOriginal(CPathTrack* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPATHTRACKIMPL_H
