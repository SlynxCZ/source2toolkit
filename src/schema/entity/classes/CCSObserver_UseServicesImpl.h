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

#ifndef _INCLUDE_CCSOBSERVER_USESERVICESIMPL_H
#define _INCLUDE_CCSOBSERVER_USESERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSObserver_UseServices.h"
#include "schema/entity/classes/CCSObserver_UseServices.h"
#include "CPlayer_UseServicesImpl.h"

class CCSObserver_UseServicesImpl : public CPlayer_UseServicesImpl, public virtual ICSObserver_UseServices
{

public:
    explicit CCSObserver_UseServicesImpl(CCSObserver_UseServices* p) : CPlayer_UseServicesImpl(p) {}

private:
    CCSObserver_UseServices* Real() { return static_cast<CCSObserver_UseServices*>(m_pReal); }
    CCSObserver_UseServices* Real() const { return static_cast<CCSObserver_UseServices*>(m_pReal); }

public:
    CCSObserver_UseServices* GetOriginal() const override { return Real(); }
};

inline ICSObserver_UseServices* CCSObserver_UseServices::ToInterface() { return new CCSObserver_UseServicesImpl(this); }
inline ICSObserver_UseServices* ICSObserver_UseServices::FromRaw(CEntityInstance*) { return nullptr; }
inline ICSObserver_UseServices* ICSObserver_UseServices::FromOriginal(CCSObserver_UseServices* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CCSOBSERVER_USESERVICESIMPL_H
