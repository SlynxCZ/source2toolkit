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

#ifndef _INCLUDE_CCOLORCORRECTIONIMPL_H
#define _INCLUDE_CCOLORCORRECTIONIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IColorCorrection.h"
#include "schema/entity/classes/CColorCorrection.h"
#include "CBaseEntityImpl.h"

class CColorCorrectionImpl : public CBaseEntityImpl, public IColorCorrection
{

public:
    explicit CColorCorrectionImpl(CColorCorrection* p) : CBaseEntityImpl(p) {}

private:
    CColorCorrection* Real() { return static_cast<CColorCorrection*>(m_pReal); }
    CColorCorrection* Real() const { return static_cast<CColorCorrection*>(m_pReal); }

public:
    CColorCorrection* GetOriginal() const override { return Real(); }
    float& FadeInDuration() override { return Real()->m_flFadeInDuration(); }
    void FadeInDurationUpdated() override { Real()->m_flFadeInDuration.NetworkStateChanged(); }
    float& FadeOutDuration() override { return Real()->m_flFadeOutDuration(); }
    void FadeOutDurationUpdated() override { Real()->m_flFadeOutDuration.NetworkStateChanged(); }
    float& StartFadeInWeight() override { return Real()->m_flStartFadeInWeight(); }
    void StartFadeInWeightUpdated() override { Real()->m_flStartFadeInWeight.NetworkStateChanged(); }
    float& StartFadeOutWeight() override { return Real()->m_flStartFadeOutWeight(); }
    void StartFadeOutWeightUpdated() override { Real()->m_flStartFadeOutWeight.NetworkStateChanged(); }
    float& TimeStartFadeIn() override { return Real()->m_flTimeStartFadeIn(); }
    void TimeStartFadeInUpdated() override { Real()->m_flTimeStartFadeIn.NetworkStateChanged(); }
    float& TimeStartFadeOut() override { return Real()->m_flTimeStartFadeOut(); }
    void TimeStartFadeOutUpdated() override { Real()->m_flTimeStartFadeOut.NetworkStateChanged(); }
    float& MaxWeight() override { return Real()->m_flMaxWeight(); }
    void MaxWeightUpdated() override { Real()->m_flMaxWeight.NetworkStateChanged(); }
    bool& StartDisabled() override { return Real()->m_bStartDisabled(); }
    void StartDisabledUpdated() override { Real()->m_bStartDisabled.NetworkStateChanged(); }
    bool& Enabled() override { return Real()->m_bEnabled(); }
    void EnabledUpdated() override { Real()->m_bEnabled.NetworkStateChanged(); }
    bool& Master() override { return Real()->m_bMaster(); }
    void MasterUpdated() override { Real()->m_bMaster.NetworkStateChanged(); }
    bool& ClientSide() override { return Real()->m_bClientSide(); }
    void ClientSideUpdated() override { Real()->m_bClientSide.NetworkStateChanged(); }
    bool& Exclusive() override { return Real()->m_bExclusive(); }
    void ExclusiveUpdated() override { Real()->m_bExclusive.NetworkStateChanged(); }
    float& MinFalloff() override { return Real()->m_MinFalloff(); }
    void MinFalloffUpdated() override { Real()->m_MinFalloff.NetworkStateChanged(); }
    float& MaxFalloff() override { return Real()->m_MaxFalloff(); }
    void MaxFalloffUpdated() override { Real()->m_MaxFalloff.NetworkStateChanged(); }
    float& CurWeight() override { return Real()->m_flCurWeight(); }
    void CurWeightUpdated() override { Real()->m_flCurWeight.NetworkStateChanged(); }
    char* NetlookupFilename() override { return Real()->m_netlookupFilename(); }
    CUtlSymbolLarge& LookupFilename() override { return Real()->m_lookupFilename(); }
    void LookupFilenameUpdated() override { Real()->m_lookupFilename.NetworkStateChanged(); }
};

inline IColorCorrection* CColorCorrection::ToInterface() { return new CColorCorrectionImpl(this); }
inline IColorCorrection* IColorCorrection::FromOriginal(CColorCorrection* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCOLORCORRECTIONIMPL_H
