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

#ifndef _INCLUDE_CAI_EXPRESSERWITHFOLLOWUPIMPL_H
#define _INCLUDE_CAI_EXPRESSERWITHFOLLOWUPIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IAI_ExpresserWithFollowup.h"
#include "schema/entity/classes/CAI_ExpresserWithFollowup.h"
#include "CAI_ExpresserImpl.h"

class CAI_ExpresserWithFollowupImpl : public CAI_ExpresserImpl, public IAI_ExpresserWithFollowup
{

public:
    explicit CAI_ExpresserWithFollowupImpl(CAI_ExpresserWithFollowup* p) : CAI_ExpresserImpl(p) {}

private:
    CAI_ExpresserWithFollowup* Real() { return static_cast<CAI_ExpresserWithFollowup*>(m_pReal); }
    CAI_ExpresserWithFollowup* Real() const { return static_cast<CAI_ExpresserWithFollowup*>(m_pReal); }

public:
    CAI_ExpresserWithFollowup* GetOriginal() const override { return Real(); }
};

inline IAI_ExpresserWithFollowup* CAI_ExpresserWithFollowup::ToInterface() { return new CAI_ExpresserWithFollowupImpl(this); }
inline IAI_ExpresserWithFollowup* IAI_ExpresserWithFollowup::FromOriginal(CAI_ExpresserWithFollowup* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CAI_EXPRESSERWITHFOLLOWUPIMPL_H
