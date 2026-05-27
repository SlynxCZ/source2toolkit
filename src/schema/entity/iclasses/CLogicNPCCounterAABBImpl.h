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

#ifndef _INCLUDE_CLOGICNPCCOUNTERAABBIMPL_H
#define _INCLUDE_CLOGICNPCCOUNTERAABBIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/ILogicNPCCounterAABB.h"
#include "schema/entity/classes/CLogicNPCCounterAABB.h"
#include "CLogicNPCCounterImpl.h"

class CLogicNPCCounterAABBImpl : public CLogicNPCCounterImpl, public ILogicNPCCounterAABB
{

public:
    explicit CLogicNPCCounterAABBImpl(CLogicNPCCounterAABB* p) : CLogicNPCCounterImpl(p) {}

private:
    CLogicNPCCounterAABB* Real() { return static_cast<CLogicNPCCounterAABB*>(m_pReal); }

public:
    Vector& DistanceOuterMins() override { return Real()->m_vDistanceOuterMins(); }
    void DistanceOuterMinsUpdated() override { Real()->m_vDistanceOuterMins.NetworkStateChanged(); }
    Vector& DistanceOuterMaxs() override { return Real()->m_vDistanceOuterMaxs(); }
    void DistanceOuterMaxsUpdated() override { Real()->m_vDistanceOuterMaxs.NetworkStateChanged(); }
    Vector& OuterMins() override { return Real()->m_vOuterMins(); }
    void OuterMinsUpdated() override { Real()->m_vOuterMins.NetworkStateChanged(); }
    Vector& OuterMaxs() override { return Real()->m_vOuterMaxs(); }
    void OuterMaxsUpdated() override { Real()->m_vOuterMaxs.NetworkStateChanged(); }
};

#endif // _INCLUDE_CLOGICNPCCOUNTERAABBIMPL_H
