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

#ifndef _INCLUDE_CMESSAGEIMPL_H
#define _INCLUDE_CMESSAGEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IMessage.h"
#include "schema/entity/classes/CMessage.h"
#include "CPointEntityImpl.h"

class CMessageImpl : public CPointEntityImpl, public IMessage
{

public:
    explicit CMessageImpl(CMessage* p) : CPointEntityImpl(p) {}

private:
    CMessage* Real() { return static_cast<CMessage*>(m_pReal); }
    CMessage* Real() const { return static_cast<CMessage*>(m_pReal); }

public:
    CMessage* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge& Message() override { return Real()->m_iszMessage(); }
    void MessageUpdated() override { Real()->m_iszMessage.NetworkStateChanged(); }
    float& MessageVolume() override { return Real()->m_MessageVolume(); }
    void MessageVolumeUpdated() override { Real()->m_MessageVolume.NetworkStateChanged(); }
    int32_t& MessageAttenuation() override { return Real()->m_MessageAttenuation(); }
    void MessageAttenuationUpdated() override { Real()->m_MessageAttenuation.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_Radius(); }
    void RadiusUpdated() override { Real()->m_Radius.NetworkStateChanged(); }
    CUtlSymbolLarge& Noise() override { return Real()->m_sNoise(); }
    void NoiseUpdated() override { Real()->m_sNoise.NetworkStateChanged(); }
    ::CEntityIOOutput& OnShowMessage() override { return Real()->m_OnShowMessage(); }
    void OnShowMessageUpdated() override { Real()->m_OnShowMessage.NetworkStateChanged(); }
};

inline IMessage* CMessage::ToInterface() { return new CMessageImpl(this); }
inline IMessage* IMessage::FromOriginal(CMessage* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CMESSAGEIMPL_H
