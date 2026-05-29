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

#ifndef _INCLUDE_CCS2WEAPONGRAPHCONTROLLERIMPL_H
#define _INCLUDE_CCS2WEAPONGRAPHCONTROLLERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICS2WeaponGraphController.h"
#include "schema/entity/classes/CCS2WeaponGraphController.h"
#include "CAnimGraphControllerBaseImpl.h"

class CCS2WeaponGraphControllerImpl : public CAnimGraphControllerBaseImpl, public ICS2WeaponGraphController
{

public:
    explicit CCS2WeaponGraphControllerImpl(CCS2WeaponGraphController* p) : CAnimGraphControllerBaseImpl(p) {}

private:
    CCS2WeaponGraphController* Real() { return static_cast<CCS2WeaponGraphController*>(m_pReal); }
    CCS2WeaponGraphController* Real() const { return static_cast<CCS2WeaponGraphController*>(m_pReal); }

public:
    CCS2WeaponGraphController* GetOriginal() const override { return Real(); }
};

inline ICS2WeaponGraphController* CCS2WeaponGraphController::ToInterface() { return new CCS2WeaponGraphControllerImpl(this); }
inline ICS2WeaponGraphController* ICS2WeaponGraphController::FromOriginal(CCS2WeaponGraphController* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCS2WEAPONGRAPHCONTROLLERIMPL_H
