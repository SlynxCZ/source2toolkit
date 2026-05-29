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

#ifndef _INCLUDE_FOGPLAYERPARAMS_TIMPL_H
#define _INCLUDE_FOGPLAYERPARAMS_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/Ifogplayerparams_t.h"
#include "schema/entity/classes/fogplayerparams_t.h"

class fogplayerparams_tImpl : public virtual Ifogplayerparams_t
{

protected:
    void* m_pReal;

public:
    explicit fogplayerparams_tImpl(void* p) : m_pReal(p) {}

private:
    fogplayerparams_t* Real() { return static_cast<fogplayerparams_t*>(m_pReal); }
    fogplayerparams_t* Real() const { return static_cast<fogplayerparams_t*>(m_pReal); }

public:
    fogplayerparams_t* GetOriginal() const override { return Real(); }
    CHandle<CFogController>& Ctrl() override { return Real()->m_hCtrl(); }
    void CtrlUpdated() override { Real()->m_hCtrl.NetworkStateChanged(); }
    float& TransitionTime() override { return Real()->m_flTransitionTime(); }
    void TransitionTimeUpdated() override { Real()->m_flTransitionTime.NetworkStateChanged(); }
    Color& OldColor() override { return Real()->m_OldColor(); }
    void OldColorUpdated() override { Real()->m_OldColor.NetworkStateChanged(); }
    float& OldStart() override { return Real()->m_flOldStart(); }
    void OldStartUpdated() override { Real()->m_flOldStart.NetworkStateChanged(); }
    float& OldEnd() override { return Real()->m_flOldEnd(); }
    void OldEndUpdated() override { Real()->m_flOldEnd.NetworkStateChanged(); }
    float& OldMaxDensity() override { return Real()->m_flOldMaxDensity(); }
    void OldMaxDensityUpdated() override { Real()->m_flOldMaxDensity.NetworkStateChanged(); }
    float& OldHDRColorScale() override { return Real()->m_flOldHDRColorScale(); }
    void OldHDRColorScaleUpdated() override { Real()->m_flOldHDRColorScale.NetworkStateChanged(); }
    float& OldFarZ() override { return Real()->m_flOldFarZ(); }
    void OldFarZUpdated() override { Real()->m_flOldFarZ.NetworkStateChanged(); }
    Color& NewColor() override { return Real()->m_NewColor(); }
    void NewColorUpdated() override { Real()->m_NewColor.NetworkStateChanged(); }
    float& NewStart() override { return Real()->m_flNewStart(); }
    void NewStartUpdated() override { Real()->m_flNewStart.NetworkStateChanged(); }
    float& NewEnd() override { return Real()->m_flNewEnd(); }
    void NewEndUpdated() override { Real()->m_flNewEnd.NetworkStateChanged(); }
    float& NewMaxDensity() override { return Real()->m_flNewMaxDensity(); }
    void NewMaxDensityUpdated() override { Real()->m_flNewMaxDensity.NetworkStateChanged(); }
    float& NewHDRColorScale() override { return Real()->m_flNewHDRColorScale(); }
    void NewHDRColorScaleUpdated() override { Real()->m_flNewHDRColorScale.NetworkStateChanged(); }
    float& NewFarZ() override { return Real()->m_flNewFarZ(); }
    void NewFarZUpdated() override { Real()->m_flNewFarZ.NetworkStateChanged(); }
};

inline Ifogplayerparams_t* fogplayerparams_t::ToInterface() { return new fogplayerparams_tImpl(this); }
inline Ifogplayerparams_t* Ifogplayerparams_t::FromRaw(CEntityInstance*) { return nullptr; }
inline Ifogplayerparams_t* Ifogplayerparams_t::FromOriginal(fogplayerparams_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_FOGPLAYERPARAMS_TIMPL_H
