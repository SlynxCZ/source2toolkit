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

#ifndef _INCLUDE_DYNPITCHVOL_BASE_TIMPL_H
#define _INCLUDE_DYNPITCHVOL_BASE_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/Idynpitchvol_base_t.h"
#include "schema/entity/classes/dynpitchvol_base_t.h"

class dynpitchvol_base_tImpl : public virtual Idynpitchvol_base_t
{

protected:
    void* m_pReal;

public:
    explicit dynpitchvol_base_tImpl(void* p) : m_pReal(p) {}

private:
    dynpitchvol_base_t* Real() { return static_cast<dynpitchvol_base_t*>(m_pReal); }
    dynpitchvol_base_t* Real() const { return static_cast<dynpitchvol_base_t*>(m_pReal); }

public:
    dynpitchvol_base_t* GetOriginal() const override { return Real(); }
    int32_t& Preset() override { return Real()->preset(); }
    void PresetUpdated() override { Real()->preset.NetworkStateChanged(); }
    int32_t& Pitchrun() override { return Real()->pitchrun(); }
    void PitchrunUpdated() override { Real()->pitchrun.NetworkStateChanged(); }
    int32_t& Pitchstart() override { return Real()->pitchstart(); }
    void PitchstartUpdated() override { Real()->pitchstart.NetworkStateChanged(); }
    int32_t& Spinup() override { return Real()->spinup(); }
    void SpinupUpdated() override { Real()->spinup.NetworkStateChanged(); }
    int32_t& Spindown() override { return Real()->spindown(); }
    void SpindownUpdated() override { Real()->spindown.NetworkStateChanged(); }
    int32_t& Volrun() override { return Real()->volrun(); }
    void VolrunUpdated() override { Real()->volrun.NetworkStateChanged(); }
    int32_t& Volstart() override { return Real()->volstart(); }
    void VolstartUpdated() override { Real()->volstart.NetworkStateChanged(); }
    int32_t& Fadein() override { return Real()->fadein(); }
    void FadeinUpdated() override { Real()->fadein.NetworkStateChanged(); }
    int32_t& Fadeout() override { return Real()->fadeout(); }
    void FadeoutUpdated() override { Real()->fadeout.NetworkStateChanged(); }
    int32_t& Lfotype() override { return Real()->lfotype(); }
    void LfotypeUpdated() override { Real()->lfotype.NetworkStateChanged(); }
    int32_t& Lforate() override { return Real()->lforate(); }
    void LforateUpdated() override { Real()->lforate.NetworkStateChanged(); }
    int32_t& Lfomodpitch() override { return Real()->lfomodpitch(); }
    void LfomodpitchUpdated() override { Real()->lfomodpitch.NetworkStateChanged(); }
    int32_t& Lfomodvol() override { return Real()->lfomodvol(); }
    void LfomodvolUpdated() override { Real()->lfomodvol.NetworkStateChanged(); }
    int32_t& Cspinup() override { return Real()->cspinup(); }
    void CspinupUpdated() override { Real()->cspinup.NetworkStateChanged(); }
    int32_t& Cspincount() override { return Real()->cspincount(); }
    void CspincountUpdated() override { Real()->cspincount.NetworkStateChanged(); }
    int32_t& Pitch() override { return Real()->pitch(); }
    void PitchUpdated() override { Real()->pitch.NetworkStateChanged(); }
    int32_t& Spinupsav() override { return Real()->spinupsav(); }
    void SpinupsavUpdated() override { Real()->spinupsav.NetworkStateChanged(); }
    int32_t& Spindownsav() override { return Real()->spindownsav(); }
    void SpindownsavUpdated() override { Real()->spindownsav.NetworkStateChanged(); }
    int32_t& Pitchfrac() override { return Real()->pitchfrac(); }
    void PitchfracUpdated() override { Real()->pitchfrac.NetworkStateChanged(); }
    int32_t& Vol() override { return Real()->vol(); }
    void VolUpdated() override { Real()->vol.NetworkStateChanged(); }
    int32_t& Fadeinsav() override { return Real()->fadeinsav(); }
    void FadeinsavUpdated() override { Real()->fadeinsav.NetworkStateChanged(); }
    int32_t& Fadeoutsav() override { return Real()->fadeoutsav(); }
    void FadeoutsavUpdated() override { Real()->fadeoutsav.NetworkStateChanged(); }
    int32_t& Volfrac() override { return Real()->volfrac(); }
    void VolfracUpdated() override { Real()->volfrac.NetworkStateChanged(); }
    int32_t& Lfofrac() override { return Real()->lfofrac(); }
    void LfofracUpdated() override { Real()->lfofrac.NetworkStateChanged(); }
    int32_t& Lfomult() override { return Real()->lfomult(); }
    void LfomultUpdated() override { Real()->lfomult.NetworkStateChanged(); }
};

inline Idynpitchvol_base_t* dynpitchvol_base_t::ToInterface() { return new dynpitchvol_base_tImpl(this); }
inline Idynpitchvol_base_t* Idynpitchvol_base_t::FromRaw(CEntityInstance*) { return nullptr; }
inline Idynpitchvol_base_t* Idynpitchvol_base_t::FromOriginal(dynpitchvol_base_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_DYNPITCHVOL_BASE_TIMPL_H
