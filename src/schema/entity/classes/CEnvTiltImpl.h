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

#ifndef _INCLUDE_CENVTILTIMPL_H
#define _INCLUDE_CENVTILTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvTilt.h"
#include "schema/entity/classes/CEnvTilt.h"
#include "CPointEntityImpl.h"

class CEnvTiltImpl : public CPointEntityImpl, public IEnvTilt
{

public:
    explicit CEnvTiltImpl(CEnvTilt* p) : CPointEntityImpl(p) {}

private:
    CEnvTilt* Real() { return static_cast<CEnvTilt*>(m_pReal); }
    CEnvTilt* Real() const { return static_cast<CEnvTilt*>(m_pReal); }

public:
    CEnvTilt* GetOriginal() const override { return Real(); }
    float& Duration() override { return Real()->m_Duration(); }
    void DurationUpdated() override { Real()->m_Duration.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_Radius(); }
    void RadiusUpdated() override { Real()->m_Radius.NetworkStateChanged(); }
    float& TiltTime() override { return Real()->m_TiltTime(); }
    void TiltTimeUpdated() override { Real()->m_TiltTime.NetworkStateChanged(); }
    float& StopTime() override { return Real()->m_stopTime(); }
    void StopTimeUpdated() override { Real()->m_stopTime.NetworkStateChanged(); }
};

inline IEnvTilt* CEnvTilt::ToInterface() { return new CEnvTiltImpl(this); }
inline IEnvTilt* IEnvTilt::FromOriginal(CEnvTilt* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENVTILTIMPL_H
