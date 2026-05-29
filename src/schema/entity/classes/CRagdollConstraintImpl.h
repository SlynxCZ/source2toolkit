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

#ifndef _INCLUDE_CRAGDOLLCONSTRAINTIMPL_H
#define _INCLUDE_CRAGDOLLCONSTRAINTIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IRagdollConstraint.h"
#include "schema/entity/classes/CRagdollConstraint.h"
#include "CPhysConstraintImpl.h"

class CRagdollConstraintImpl : public CPhysConstraintImpl, public IRagdollConstraint
{

public:
    explicit CRagdollConstraintImpl(CRagdollConstraint* p) : CPhysConstraintImpl(p) {}

private:
    CRagdollConstraint* Real() { return static_cast<CRagdollConstraint*>(m_pReal); }
    CRagdollConstraint* Real() const { return static_cast<CRagdollConstraint*>(m_pReal); }

public:
    CRagdollConstraint* GetOriginal() const override { return Real(); }
    float& Xmin() override { return Real()->m_xmin(); }
    void XminUpdated() override { Real()->m_xmin.NetworkStateChanged(); }
    float& Xmax() override { return Real()->m_xmax(); }
    void XmaxUpdated() override { Real()->m_xmax.NetworkStateChanged(); }
    float& Ymin() override { return Real()->m_ymin(); }
    void YminUpdated() override { Real()->m_ymin.NetworkStateChanged(); }
    float& Ymax() override { return Real()->m_ymax(); }
    void YmaxUpdated() override { Real()->m_ymax.NetworkStateChanged(); }
    float& Zmin() override { return Real()->m_zmin(); }
    void ZminUpdated() override { Real()->m_zmin.NetworkStateChanged(); }
    float& Zmax() override { return Real()->m_zmax(); }
    void ZmaxUpdated() override { Real()->m_zmax.NetworkStateChanged(); }
    float& Xfriction() override { return Real()->m_xfriction(); }
    void XfrictionUpdated() override { Real()->m_xfriction.NetworkStateChanged(); }
    float& Yfriction() override { return Real()->m_yfriction(); }
    void YfrictionUpdated() override { Real()->m_yfriction.NetworkStateChanged(); }
    float& Zfriction() override { return Real()->m_zfriction(); }
    void ZfrictionUpdated() override { Real()->m_zfriction.NetworkStateChanged(); }
};

inline IRagdollConstraint* CRagdollConstraint::ToInterface() { return new CRagdollConstraintImpl(this); }
inline IRagdollConstraint* IRagdollConstraint::FromOriginal(CRagdollConstraint* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CRAGDOLLCONSTRAINTIMPL_H
