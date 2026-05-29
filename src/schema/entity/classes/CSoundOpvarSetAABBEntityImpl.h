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

#ifndef _INCLUDE_CSOUNDOPVARSETAABBENTITYIMPL_H
#define _INCLUDE_CSOUNDOPVARSETAABBENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISoundOpvarSetAABBEntity.h"
#include "schema/entity/classes/CSoundOpvarSetAABBEntity.h"
#include "CSoundOpvarSetPointEntityImpl.h"

class CSoundOpvarSetAABBEntityImpl : public CSoundOpvarSetPointEntityImpl, public ISoundOpvarSetAABBEntity
{

public:
    explicit CSoundOpvarSetAABBEntityImpl(CSoundOpvarSetAABBEntity* p) : CSoundOpvarSetPointEntityImpl(p) {}

private:
    CSoundOpvarSetAABBEntity* Real() { return static_cast<CSoundOpvarSetAABBEntity*>(m_pReal); }
    CSoundOpvarSetAABBEntity* Real() const { return static_cast<CSoundOpvarSetAABBEntity*>(m_pReal); }

public:
    CSoundOpvarSetAABBEntity* GetOriginal() const override { return Real(); }
    Vector& DistanceInnerMins() override { return Real()->m_vDistanceInnerMins(); }
    void DistanceInnerMinsUpdated() override { Real()->m_vDistanceInnerMins.NetworkStateChanged(); }
    Vector& DistanceInnerMaxs() override { return Real()->m_vDistanceInnerMaxs(); }
    void DistanceInnerMaxsUpdated() override { Real()->m_vDistanceInnerMaxs.NetworkStateChanged(); }
    Vector& DistanceOuterMins() override { return Real()->m_vDistanceOuterMins(); }
    void DistanceOuterMinsUpdated() override { Real()->m_vDistanceOuterMins.NetworkStateChanged(); }
    Vector& DistanceOuterMaxs() override { return Real()->m_vDistanceOuterMaxs(); }
    void DistanceOuterMaxsUpdated() override { Real()->m_vDistanceOuterMaxs.NetworkStateChanged(); }
    int32_t& AABBDirection() override { return Real()->m_nAABBDirection(); }
    void AABBDirectionUpdated() override { Real()->m_nAABBDirection.NetworkStateChanged(); }
    Vector& InnerMins() override { return Real()->m_vInnerMins(); }
    void InnerMinsUpdated() override { Real()->m_vInnerMins.NetworkStateChanged(); }
    Vector& InnerMaxs() override { return Real()->m_vInnerMaxs(); }
    void InnerMaxsUpdated() override { Real()->m_vInnerMaxs.NetworkStateChanged(); }
    Vector& OuterMins() override { return Real()->m_vOuterMins(); }
    void OuterMinsUpdated() override { Real()->m_vOuterMins.NetworkStateChanged(); }
    Vector& OuterMaxs() override { return Real()->m_vOuterMaxs(); }
    void OuterMaxsUpdated() override { Real()->m_vOuterMaxs.NetworkStateChanged(); }
};

inline ISoundOpvarSetAABBEntity* CSoundOpvarSetAABBEntity::ToInterface() { return new CSoundOpvarSetAABBEntityImpl(this); }
inline ISoundOpvarSetAABBEntity* ISoundOpvarSetAABBEntity::FromOriginal(CSoundOpvarSetAABBEntity* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSOUNDOPVARSETAABBENTITYIMPL_H
