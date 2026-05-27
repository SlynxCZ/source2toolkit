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

#ifndef _INCLUDE_CECONENTITYIMPL_H
#define _INCLUDE_CECONENTITYIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IEconEntity.h"
#include "schema/entity/classes/CEconEntity.h"
#include "CBaseAnimGraphImpl.h"

class CEconEntityImpl : public CBaseAnimGraphImpl, public IEconEntity
{

public:
    explicit CEconEntityImpl(CEconEntity* p) : CBaseAnimGraphImpl(p) {}

private:
    CEconEntity* Real() { return static_cast<CEconEntity*>(m_pReal); }

public:
    CAttributeContainer& AttributeManager() override { return Real()->m_AttributeManager(); }
    void AttributeManagerUpdated() override { Real()->m_AttributeManager.NetworkStateChanged(); }
    uint32_t& OriginalOwnerXuidLow() override { return Real()->m_OriginalOwnerXuidLow(); }
    void OriginalOwnerXuidLowUpdated() override { Real()->m_OriginalOwnerXuidLow.NetworkStateChanged(); }
    uint32_t& OriginalOwnerXuidHigh() override { return Real()->m_OriginalOwnerXuidHigh(); }
    void OriginalOwnerXuidHighUpdated() override { Real()->m_OriginalOwnerXuidHigh.NetworkStateChanged(); }
    int32_t& FallbackPaintKit() override { return Real()->m_nFallbackPaintKit(); }
    void FallbackPaintKitUpdated() override { Real()->m_nFallbackPaintKit.NetworkStateChanged(); }
    int32_t& FallbackSeed() override { return Real()->m_nFallbackSeed(); }
    void FallbackSeedUpdated() override { Real()->m_nFallbackSeed.NetworkStateChanged(); }
    float& FallbackWear() override { return Real()->m_flFallbackWear(); }
    void FallbackWearUpdated() override { Real()->m_flFallbackWear.NetworkStateChanged(); }
    int32_t& FallbackStatTrak() override { return Real()->m_nFallbackStatTrak(); }
    void FallbackStatTrakUpdated() override { Real()->m_nFallbackStatTrak.NetworkStateChanged(); }
    CHandle<CBaseEntity>& OldProvidee() override { return Real()->m_hOldProvidee(); }
    void OldProvideeUpdated() override { Real()->m_hOldProvidee.NetworkStateChanged(); }
    int32_t& OldOwnerClass() override { return Real()->m_iOldOwnerClass(); }
    void OldOwnerClassUpdated() override { Real()->m_iOldOwnerClass.NetworkStateChanged(); }
};

#endif // _INCLUDE_CECONENTITYIMPL_H
