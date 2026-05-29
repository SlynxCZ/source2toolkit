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

#ifndef _INCLUDE_CTRIGGERBRUSHIMPL_H
#define _INCLUDE_CTRIGGERBRUSHIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITriggerBrush.h"
#include "schema/entity/classes/CTriggerBrush.h"
#include "CBaseModelEntityImpl.h"

class CTriggerBrushImpl : public CBaseModelEntityImpl, public ITriggerBrush
{

public:
    explicit CTriggerBrushImpl(CTriggerBrush* p) : CBaseModelEntityImpl(p) {}

private:
    CTriggerBrush* Real() { return static_cast<CTriggerBrush*>(m_pReal); }
    CTriggerBrush* Real() const { return static_cast<CTriggerBrush*>(m_pReal); }

public:
    CTriggerBrush* GetOriginal() const override { return Real(); }
    CEntityIOOutput& OnStartTouch() override { return Real()->m_OnStartTouch(); }
    void OnStartTouchUpdated() override { Real()->m_OnStartTouch.NetworkStateChanged(); }
    CEntityIOOutput& OnEndTouch() override { return Real()->m_OnEndTouch(); }
    void OnEndTouchUpdated() override { Real()->m_OnEndTouch.NetworkStateChanged(); }
    CEntityIOOutput& OnUse() override { return Real()->m_OnUse(); }
    void OnUseUpdated() override { Real()->m_OnUse.NetworkStateChanged(); }
    int32_t& InputFilter() override { return Real()->m_iInputFilter(); }
    void InputFilterUpdated() override { Real()->m_iInputFilter.NetworkStateChanged(); }
    int32_t& DontMessageParent() override { return Real()->m_iDontMessageParent(); }
    void DontMessageParentUpdated() override { Real()->m_iDontMessageParent.NetworkStateChanged(); }
};

inline ITriggerBrush* CTriggerBrush::ToInterface() { return new CTriggerBrushImpl(this); }
inline ITriggerBrush* ITriggerBrush::FromOriginal(CTriggerBrush* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CTRIGGERBRUSHIMPL_H
