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

#ifndef _INCLUDE_LERPDATA_TIMPL_H
#define _INCLUDE_LERPDATA_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/Ilerpdata_t.h"
#include "schema/entity/classes/lerpdata_t.h"

class lerpdata_tImpl : public virtual Ilerpdata_t
{

protected:
    void* m_pReal;

public:
    explicit lerpdata_tImpl(void* p) : m_pReal(p) {}

private:
    lerpdata_t* Real() { return static_cast<lerpdata_t*>(m_pReal); }
    lerpdata_t* Real() const { return static_cast<lerpdata_t*>(m_pReal); }

public:
    lerpdata_t* GetOriginal() const override { return Real(); }
    CHandle<CBaseEntity>& Ent() override { return Real()->m_hEnt(); }
    void EntUpdated() override { Real()->m_hEnt.NetworkStateChanged(); }
    ::MoveType_t& MoveType() override { return Real()->m_MoveType(); }
    void MoveTypeUpdated() override { Real()->m_MoveType.NetworkStateChanged(); }
    float& StartTime() override { return Real()->m_flStartTime(); }
    void StartTimeUpdated() override { Real()->m_flStartTime.NetworkStateChanged(); }
    Vector& StartOrigin() override { return Real()->m_vecStartOrigin(); }
    void StartOriginUpdated() override { Real()->m_vecStartOrigin.NetworkStateChanged(); }
    Quaternion& StartRot() override { return Real()->m_qStartRot(); }
    void StartRotUpdated() override { Real()->m_qStartRot.NetworkStateChanged(); }
    ::ParticleIndex_t& FXIndex() override { return Real()->m_nFXIndex(); }
    void FXIndexUpdated() override { Real()->m_nFXIndex.NetworkStateChanged(); }
};

inline Ilerpdata_t* lerpdata_t::ToInterface() { return new lerpdata_tImpl(this); }
inline Ilerpdata_t* Ilerpdata_t::FromOriginal(lerpdata_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_LERPDATA_TIMPL_H
