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

#ifndef _INCLUDE_CTESTPULSEIO__ENTITYHANDLEINTARGS_TIMPL_H
#define _INCLUDE_CTESTPULSEIO__ENTITYHANDLEINTARGS_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITestPulseIO__EntityHandleIntArgs_t.h"
#include "schema/entity/classes/CTestPulseIO__EntityHandleIntArgs_t.h"

class CTestPulseIO__EntityHandleIntArgs_tImpl : public virtual ITestPulseIO__EntityHandleIntArgs_t
{

protected:
    void* m_pReal;

public:
    explicit CTestPulseIO__EntityHandleIntArgs_tImpl(void* p) : m_pReal(p) {}

private:
    CTestPulseIO__EntityHandleIntArgs_t* Real() { return static_cast<CTestPulseIO__EntityHandleIntArgs_t*>(m_pReal); }
    CTestPulseIO__EntityHandleIntArgs_t* Real() const { return static_cast<CTestPulseIO__EntityHandleIntArgs_t*>(m_pReal); }

public:
    CTestPulseIO__EntityHandleIntArgs_t* GetOriginal() const override { return Real(); }
    CEntityHandle& HandleA() override { return Real()->handleA(); }
    void HandleAUpdated() override { Real()->handleA.NetworkStateChanged(); }
    int32_t& ValueB() override { return Real()->valueB(); }
    void ValueBUpdated() override { Real()->valueB.NetworkStateChanged(); }
};

inline ITestPulseIO__EntityHandleIntArgs_t* CTestPulseIO__EntityHandleIntArgs_t::ToInterface() { return new CTestPulseIO__EntityHandleIntArgs_tImpl(this); }
inline ITestPulseIO__EntityHandleIntArgs_t* ITestPulseIO__EntityHandleIntArgs_t::FromRaw(CEntityInstance*) { return nullptr; }
inline ITestPulseIO__EntityHandleIntArgs_t* ITestPulseIO__EntityHandleIntArgs_t::FromOriginal(CTestPulseIO__EntityHandleIntArgs_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CTESTPULSEIO__ENTITYHANDLEINTARGS_TIMPL_H
