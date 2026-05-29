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

#ifndef _INCLUDE_CTESTPULSEIOCOMPONENT_DERIVEDIMPL_H
#define _INCLUDE_CTESTPULSEIOCOMPONENT_DERIVEDIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITestPulseIOComponent_Derived.h"
#include "schema/entity/classes/CTestPulseIOComponent_Derived.h"
#include "CTestPulseIOComponentImpl.h"

class CTestPulseIOComponent_DerivedImpl : public CTestPulseIOComponentImpl, public ITestPulseIOComponent_Derived
{

public:
    explicit CTestPulseIOComponent_DerivedImpl(CTestPulseIOComponent_Derived* p) : CTestPulseIOComponentImpl(p) {}

private:
    CTestPulseIOComponent_Derived* Real() { return static_cast<CTestPulseIOComponent_Derived*>(m_pReal); }
    CTestPulseIOComponent_Derived* Real() const { return static_cast<CTestPulseIOComponent_Derived*>(m_pReal); }

public:
    CTestPulseIOComponent_Derived* GetOriginal() const override { return Real(); }
};

inline ITestPulseIOComponent_Derived* CTestPulseIOComponent_Derived::ToInterface() { return new CTestPulseIOComponent_DerivedImpl(this); }
inline ITestPulseIOComponent_Derived* ITestPulseIOComponent_Derived::FromOriginal(CTestPulseIOComponent_Derived* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CTESTPULSEIOCOMPONENT_DERIVEDIMPL_H
