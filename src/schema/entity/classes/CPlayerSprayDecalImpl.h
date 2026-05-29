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

#ifndef _INCLUDE_CPLAYERSPRAYDECALIMPL_H
#define _INCLUDE_CPLAYERSPRAYDECALIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPlayerSprayDecal.h"
#include "schema/entity/classes/CPlayerSprayDecal.h"
#include "CModelPointEntityImpl.h"

class CPlayerSprayDecalImpl : public CModelPointEntityImpl, public IPlayerSprayDecal
{

public:
    explicit CPlayerSprayDecalImpl(CPlayerSprayDecal* p) : CModelPointEntityImpl(p) {}

private:
    CPlayerSprayDecal* Real() { return static_cast<CPlayerSprayDecal*>(m_pReal); }
    CPlayerSprayDecal* Real() const { return static_cast<CPlayerSprayDecal*>(m_pReal); }

public:
    CPlayerSprayDecal* GetOriginal() const override { return Real(); }
    int32_t& UniqueID() override { return Real()->m_nUniqueID(); }
    void UniqueIDUpdated() override { Real()->m_nUniqueID.NetworkStateChanged(); }
    uint32_t& AccountID() override { return Real()->m_unAccountID(); }
    void AccountIDUpdated() override { Real()->m_unAccountID.NetworkStateChanged(); }
    uint32_t& TraceID() override { return Real()->m_unTraceID(); }
    void TraceIDUpdated() override { Real()->m_unTraceID.NetworkStateChanged(); }
    uint32_t& RtGcTime() override { return Real()->m_rtGcTime(); }
    void RtGcTimeUpdated() override { Real()->m_rtGcTime.NetworkStateChanged(); }
    Vector& EndPos() override { return Real()->m_vecEndPos(); }
    void EndPosUpdated() override { Real()->m_vecEndPos.NetworkStateChanged(); }
    Vector& Start() override { return Real()->m_vecStart(); }
    void StartUpdated() override { Real()->m_vecStart.NetworkStateChanged(); }
    Vector& Left() override { return Real()->m_vecLeft(); }
    void LeftUpdated() override { Real()->m_vecLeft.NetworkStateChanged(); }
    Vector& Normal() override { return Real()->m_vecNormal(); }
    void NormalUpdated() override { Real()->m_vecNormal.NetworkStateChanged(); }
    int32_t& Player() override { return Real()->m_nPlayer(); }
    void PlayerUpdated() override { Real()->m_nPlayer.NetworkStateChanged(); }
    int32_t& Entity() override { return Real()->m_nEntity(); }
    void EntityUpdated() override { Real()->m_nEntity.NetworkStateChanged(); }
    int32_t& Hitbox() override { return Real()->m_nHitbox(); }
    void HitboxUpdated() override { Real()->m_nHitbox.NetworkStateChanged(); }
    float& CreationTime() override { return Real()->m_flCreationTime(); }
    void CreationTimeUpdated() override { Real()->m_flCreationTime.NetworkStateChanged(); }
    int32_t& TintID() override { return Real()->m_nTintID(); }
    void TintIDUpdated() override { Real()->m_nTintID.NetworkStateChanged(); }
    uint8_t& Version() override { return Real()->m_nVersion(); }
    void VersionUpdated() override { Real()->m_nVersion.NetworkStateChanged(); }
    uint8_t* Signature() override { return Real()->m_ubSignature(); }
};

inline IPlayerSprayDecal* CPlayerSprayDecal::ToInterface() { return new CPlayerSprayDecalImpl(this); }
inline IPlayerSprayDecal* IPlayerSprayDecal::FromOriginal(CPlayerSprayDecal* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPLAYERSPRAYDECALIMPL_H
