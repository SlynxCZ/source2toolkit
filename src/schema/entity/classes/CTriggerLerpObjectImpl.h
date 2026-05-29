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

#ifndef _INCLUDE_CTRIGGERLERPOBJECTIMPL_H
#define _INCLUDE_CTRIGGERLERPOBJECTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITriggerLerpObject.h"
#include "schema/entity/classes/CTriggerLerpObject.h"
#include "CBaseTriggerImpl.h"

class CTriggerLerpObjectImpl : public CBaseTriggerImpl, public ITriggerLerpObject
{

public:
    explicit CTriggerLerpObjectImpl(CTriggerLerpObject* p) : CBaseTriggerImpl(p) {}

private:
    CTriggerLerpObject* Real() { return static_cast<CTriggerLerpObject*>(m_pReal); }
    CTriggerLerpObject* Real() const { return static_cast<CTriggerLerpObject*>(m_pReal); }

public:
    CTriggerLerpObject* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge& LerpTarget() override { return Real()->m_iszLerpTarget(); }
    void LerpTargetUpdated() override { Real()->m_iszLerpTarget.NetworkStateChanged(); }
    CHandle<CBaseEntity>& LerpTarget() override { return Real()->m_hLerpTarget(); }
    void LerpTargetUpdated() override { Real()->m_hLerpTarget.NetworkStateChanged(); }
    CUtlSymbolLarge& LerpTargetAttachment() override { return Real()->m_iszLerpTargetAttachment(); }
    void LerpTargetAttachmentUpdated() override { Real()->m_iszLerpTargetAttachment.NetworkStateChanged(); }
    float& LerpDuration() override { return Real()->m_flLerpDuration(); }
    void LerpDurationUpdated() override { Real()->m_flLerpDuration.NetworkStateChanged(); }
    bool& AttachedEntityWasParented() override { return Real()->m_bAttachedEntityWasParented(); }
    void AttachedEntityWasParentedUpdated() override { Real()->m_bAttachedEntityWasParented.NetworkStateChanged(); }
    bool& LerpRestoreMoveType() override { return Real()->m_bLerpRestoreMoveType(); }
    void LerpRestoreMoveTypeUpdated() override { Real()->m_bLerpRestoreMoveType.NetworkStateChanged(); }
    bool& SingleLerpObject() override { return Real()->m_bSingleLerpObject(); }
    void SingleLerpObjectUpdated() override { Real()->m_bSingleLerpObject.NetworkStateChanged(); }
    CUtlVector<lerpdata_t>& LerpingObjects() override { return Real()->m_vecLerpingObjects(); }
    void LerpingObjectsUpdated() override { Real()->m_vecLerpingObjects.NetworkStateChanged(); }
    CUtlSymbolLarge& LerpEffect() override { return Real()->m_iszLerpEffect(); }
    void LerpEffectUpdated() override { Real()->m_iszLerpEffect.NetworkStateChanged(); }
    CUtlSymbolLarge& LerpSound() override { return Real()->m_iszLerpSound(); }
    void LerpSoundUpdated() override { Real()->m_iszLerpSound.NetworkStateChanged(); }
    bool& AttachTouchingObject() override { return Real()->m_bAttachTouchingObject(); }
    void AttachTouchingObjectUpdated() override { Real()->m_bAttachTouchingObject.NetworkStateChanged(); }
    CHandle<CBaseEntity>& EntityToWaitForDisconnect() override { return Real()->m_hEntityToWaitForDisconnect(); }
    void EntityToWaitForDisconnectUpdated() override { Real()->m_hEntityToWaitForDisconnect.NetworkStateChanged(); }
    CEntityIOOutput& OnLerpStarted() override { return Real()->m_OnLerpStarted(); }
    void OnLerpStartedUpdated() override { Real()->m_OnLerpStarted.NetworkStateChanged(); }
    CEntityIOOutput& OnLerpFinished() override { return Real()->m_OnLerpFinished(); }
    void OnLerpFinishedUpdated() override { Real()->m_OnLerpFinished.NetworkStateChanged(); }
    CEntityIOOutput& OnDetached() override { return Real()->m_OnDetached(); }
    void OnDetachedUpdated() override { Real()->m_OnDetached.NetworkStateChanged(); }
};

inline ITriggerLerpObject* CTriggerLerpObject::ToInterface() { return new CTriggerLerpObjectImpl(this); }
inline ITriggerLerpObject* ITriggerLerpObject::FromOriginal(CTriggerLerpObject* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CTRIGGERLERPOBJECTIMPL_H
