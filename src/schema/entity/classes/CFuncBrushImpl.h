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

#ifndef _INCLUDE_CFUNCBRUSHIMPL_H
#define _INCLUDE_CFUNCBRUSHIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IFuncBrush.h"
#include "schema/entity/classes/CFuncBrush.h"
#include "CBaseModelEntityImpl.h"

class CFuncBrushImpl : public CBaseModelEntityImpl, public IFuncBrush
{

public:
    explicit CFuncBrushImpl(CFuncBrush* p) : CBaseModelEntityImpl(p) {}

private:
    CFuncBrush* Real() { return static_cast<CFuncBrush*>(m_pReal); }
    CFuncBrush* Real() const { return static_cast<CFuncBrush*>(m_pReal); }

public:
    CFuncBrush* GetOriginal() const override { return Real(); }
    BrushSolidities_e& Solidity() override { return Real()->m_iSolidity(); }
    void SolidityUpdated() override { Real()->m_iSolidity.NetworkStateChanged(); }
    int32_t& Disabled() override { return Real()->m_iDisabled(); }
    void DisabledUpdated() override { Real()->m_iDisabled.NetworkStateChanged(); }
    bool& SolidBsp() override { return Real()->m_bSolidBsp(); }
    void SolidBspUpdated() override { Real()->m_bSolidBsp.NetworkStateChanged(); }
    CUtlSymbolLarge& ExcludedClass() override { return Real()->m_iszExcludedClass(); }
    void ExcludedClassUpdated() override { Real()->m_iszExcludedClass.NetworkStateChanged(); }
    bool& InvertExclusion() override { return Real()->m_bInvertExclusion(); }
    void InvertExclusionUpdated() override { Real()->m_bInvertExclusion.NetworkStateChanged(); }
    bool& ScriptedMovement() override { return Real()->m_bScriptedMovement(); }
    void ScriptedMovementUpdated() override { Real()->m_bScriptedMovement.NetworkStateChanged(); }
};

inline IFuncBrush* CFuncBrush::ToInterface() { return new CFuncBrushImpl(this); }
inline IFuncBrush* IFuncBrush::FromOriginal(CFuncBrush* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CFUNCBRUSHIMPL_H
