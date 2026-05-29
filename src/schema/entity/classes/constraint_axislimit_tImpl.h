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

#ifndef _INCLUDE_CONSTRAINT_AXISLIMIT_TIMPL_H
#define _INCLUDE_CONSTRAINT_AXISLIMIT_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/Iconstraint_axislimit_t.h"
#include "schema/entity/classes/constraint_axislimit_t.h"

class constraint_axislimit_tImpl : public virtual Iconstraint_axislimit_t
{

protected:
    void* m_pReal;

public:
    explicit constraint_axislimit_tImpl(void* p) : m_pReal(p) {}

private:
    constraint_axislimit_t* Real() { return static_cast<constraint_axislimit_t*>(m_pReal); }
    constraint_axislimit_t* Real() const { return static_cast<constraint_axislimit_t*>(m_pReal); }

public:
    constraint_axislimit_t* GetOriginal() const override { return Real(); }
    float& MinRotation() override { return Real()->flMinRotation(); }
    void MinRotationUpdated() override { Real()->flMinRotation.NetworkStateChanged(); }
    float& MaxRotation() override { return Real()->flMaxRotation(); }
    void MaxRotationUpdated() override { Real()->flMaxRotation.NetworkStateChanged(); }
    float& MotorTargetAngSpeed() override { return Real()->flMotorTargetAngSpeed(); }
    void MotorTargetAngSpeedUpdated() override { Real()->flMotorTargetAngSpeed.NetworkStateChanged(); }
    float& MotorMaxTorque() override { return Real()->flMotorMaxTorque(); }
    void MotorMaxTorqueUpdated() override { Real()->flMotorMaxTorque.NetworkStateChanged(); }
};

inline Iconstraint_axislimit_t* constraint_axislimit_t::ToInterface() { return new constraint_axislimit_tImpl(this); }
inline Iconstraint_axislimit_t* Iconstraint_axislimit_t::FromRaw(CEntityInstance*) { return nullptr; }
inline Iconstraint_axislimit_t* Iconstraint_axislimit_t::FromOriginal(constraint_axislimit_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CONSTRAINT_AXISLIMIT_TIMPL_H
