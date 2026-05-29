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

#ifndef _INCLUDE_CBASEBUTTONIMPL_H
#define _INCLUDE_CBASEBUTTONIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IBaseButton.h"
#include "schema/entity/classes/CBaseButton.h"
#include "CBaseToggleImpl.h"

class CBaseButtonImpl : public CBaseToggleImpl, public IBaseButton
{

public:
    explicit CBaseButtonImpl(CBaseButton* p) : CBaseToggleImpl(p) {}

private:
    CBaseButton* Real() { return static_cast<CBaseButton*>(m_pReal); }
    CBaseButton* Real() const { return static_cast<CBaseButton*>(m_pReal); }

public:
    CBaseButton* GetOriginal() const override { return Real(); }
    QAngle& MoveEntitySpace() override { return Real()->m_angMoveEntitySpace(); }
    void MoveEntitySpaceUpdated() override { Real()->m_angMoveEntitySpace.NetworkStateChanged(); }
    bool& StayPushed() override { return Real()->m_fStayPushed(); }
    void StayPushedUpdated() override { Real()->m_fStayPushed.NetworkStateChanged(); }
    bool& Rotating() override { return Real()->m_fRotating(); }
    void RotatingUpdated() override { Real()->m_fRotating.NetworkStateChanged(); }
    locksound_t& Ls() override { return Real()->m_ls(); }
    void LsUpdated() override { Real()->m_ls.NetworkStateChanged(); }
    CUtlSymbolLarge& UseSound() override { return Real()->m_sUseSound(); }
    void UseSoundUpdated() override { Real()->m_sUseSound.NetworkStateChanged(); }
    CUtlSymbolLarge& LockedSound() override { return Real()->m_sLockedSound(); }
    void LockedSoundUpdated() override { Real()->m_sLockedSound.NetworkStateChanged(); }
    CUtlSymbolLarge& UnlockedSound() override { return Real()->m_sUnlockedSound(); }
    void UnlockedSoundUpdated() override { Real()->m_sUnlockedSound.NetworkStateChanged(); }
    CUtlSymbolLarge& OverrideAnticipationName() override { return Real()->m_sOverrideAnticipationName(); }
    void OverrideAnticipationNameUpdated() override { Real()->m_sOverrideAnticipationName.NetworkStateChanged(); }
    bool& Locked() override { return Real()->m_bLocked(); }
    void LockedUpdated() override { Real()->m_bLocked.NetworkStateChanged(); }
    bool& Disabled() override { return Real()->m_bDisabled(); }
    void DisabledUpdated() override { Real()->m_bDisabled.NetworkStateChanged(); }
    float& UseLockedTime() override { return Real()->m_flUseLockedTime(); }
    void UseLockedTimeUpdated() override { Real()->m_flUseLockedTime.NetworkStateChanged(); }
    bool& SolidBsp() override { return Real()->m_bSolidBsp(); }
    void SolidBspUpdated() override { Real()->m_bSolidBsp.NetworkStateChanged(); }
    CEntityIOOutput& OnDamaged() override { return Real()->m_OnDamaged(); }
    void OnDamagedUpdated() override { Real()->m_OnDamaged.NetworkStateChanged(); }
    CEntityIOOutput& OnPressed() override { return Real()->m_OnPressed(); }
    void OnPressedUpdated() override { Real()->m_OnPressed.NetworkStateChanged(); }
    CEntityIOOutput& OnUseLocked() override { return Real()->m_OnUseLocked(); }
    void OnUseLockedUpdated() override { Real()->m_OnUseLocked.NetworkStateChanged(); }
    CEntityIOOutput& OnIn() override { return Real()->m_OnIn(); }
    void OnInUpdated() override { Real()->m_OnIn.NetworkStateChanged(); }
    CEntityIOOutput& OnOut() override { return Real()->m_OnOut(); }
    void OnOutUpdated() override { Real()->m_OnOut.NetworkStateChanged(); }
    int32_t& State() override { return Real()->m_nState(); }
    void StateUpdated() override { Real()->m_nState.NetworkStateChanged(); }
    CEntityHandle& Constraint() override { return Real()->m_hConstraint(); }
    void ConstraintUpdated() override { Real()->m_hConstraint.NetworkStateChanged(); }
    CEntityHandle& ConstraintParent() override { return Real()->m_hConstraintParent(); }
    void ConstraintParentUpdated() override { Real()->m_hConstraintParent.NetworkStateChanged(); }
    bool& ForceNpcExclude() override { return Real()->m_bForceNpcExclude(); }
    void ForceNpcExcludeUpdated() override { Real()->m_bForceNpcExclude.NetworkStateChanged(); }
    CUtlSymbolLarge& GlowEntity() override { return Real()->m_sGlowEntity(); }
    void GlowEntityUpdated() override { Real()->m_sGlowEntity.NetworkStateChanged(); }
    CHandle<CBaseModelEntity>& GlowEntity() override { return Real()->m_glowEntity(); }
    void GlowEntityUpdated() override { Real()->m_glowEntity.NetworkStateChanged(); }
    bool& Usable() override { return Real()->m_usable(); }
    void UsableUpdated() override { Real()->m_usable.NetworkStateChanged(); }
    CUtlSymbolLarge& DisplayText() override { return Real()->m_szDisplayText(); }
    void DisplayTextUpdated() override { Real()->m_szDisplayText.NetworkStateChanged(); }
};

inline IBaseButton* CBaseButton::ToInterface() { return new CBaseButtonImpl(this); }
inline IBaseButton* IBaseButton::FromOriginal(CBaseButton* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CBASEBUTTONIMPL_H
