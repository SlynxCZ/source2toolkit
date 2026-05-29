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

#ifndef _INCLUDE_SKY3DPARAMS_TIMPL_H
#define _INCLUDE_SKY3DPARAMS_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/Isky3dparams_t.h"
#include "schema/entity/classes/sky3dparams_t.h"

class sky3dparams_tImpl : public virtual Isky3dparams_t
{

protected:
    void* m_pReal;

public:
    explicit sky3dparams_tImpl(void* p) : m_pReal(p) {}

private:
    sky3dparams_t* Real() { return static_cast<sky3dparams_t*>(m_pReal); }
    sky3dparams_t* Real() const { return static_cast<sky3dparams_t*>(m_pReal); }

public:
    sky3dparams_t* GetOriginal() const override { return Real(); }
    int16_t& Scale() override { return Real()->scale(); }
    void ScaleUpdated() override { Real()->scale.NetworkStateChanged(); }
    Vector& Origin() override { return Real()->origin(); }
    void OriginUpdated() override { Real()->origin.NetworkStateChanged(); }
    bool& Clip3DSkyBoxNearToWorldFar() override { return Real()->bClip3DSkyBoxNearToWorldFar(); }
    void Clip3DSkyBoxNearToWorldFarUpdated() override { Real()->bClip3DSkyBoxNearToWorldFar.NetworkStateChanged(); }
    float& Clip3DSkyBoxNearToWorldFarOffset() override { return Real()->flClip3DSkyBoxNearToWorldFarOffset(); }
    void Clip3DSkyBoxNearToWorldFarOffsetUpdated() override { Real()->flClip3DSkyBoxNearToWorldFarOffset.NetworkStateChanged(); }
    ::fogparams_t& Fog() override { return Real()->fog(); }
    void FogUpdated() override { Real()->fog.NetworkStateChanged(); }
    WorldGroupId_t& WorldGroupID() override { return Real()->m_nWorldGroupID(); }
    void WorldGroupIDUpdated() override { Real()->m_nWorldGroupID.NetworkStateChanged(); }
};

inline Isky3dparams_t* sky3dparams_t::ToInterface() { return new sky3dparams_tImpl(this); }
inline Isky3dparams_t* Isky3dparams_t::FromOriginal(sky3dparams_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_SKY3DPARAMS_TIMPL_H
