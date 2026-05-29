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

#ifndef _INCLUDE_SNDOPVARLATCHDATA_TIMPL_H
#define _INCLUDE_SNDOPVARLATCHDATA_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/Isndopvarlatchdata_t.h"
#include "schema/entity/classes/sndopvarlatchdata_t.h"

class sndopvarlatchdata_tImpl : public virtual Isndopvarlatchdata_t
{

protected:
    void* m_pReal;

public:
    explicit sndopvarlatchdata_tImpl(void* p) : m_pReal(p) {}

private:
    sndopvarlatchdata_t* Real() { return static_cast<sndopvarlatchdata_t*>(m_pReal); }
    sndopvarlatchdata_t* Real() const { return static_cast<sndopvarlatchdata_t*>(m_pReal); }

public:
    sndopvarlatchdata_t* GetOriginal() const override { return Real(); }
    CUtlSymbolLarge& Stack() override { return Real()->m_iszStack(); }
    void StackUpdated() override { Real()->m_iszStack.NetworkStateChanged(); }
    CUtlSymbolLarge& Operator() override { return Real()->m_iszOperator(); }
    void OperatorUpdated() override { Real()->m_iszOperator.NetworkStateChanged(); }
    CUtlSymbolLarge& Opvar() override { return Real()->m_iszOpvar(); }
    void OpvarUpdated() override { Real()->m_iszOpvar.NetworkStateChanged(); }
    float& Val() override { return Real()->m_flVal(); }
    void ValUpdated() override { Real()->m_flVal.NetworkStateChanged(); }
    Vector& Pos() override { return Real()->m_vPos(); }
    void PosUpdated() override { Real()->m_vPos.NetworkStateChanged(); }
};

inline Isndopvarlatchdata_t* sndopvarlatchdata_t::ToInterface() { return new sndopvarlatchdata_tImpl(this); }
inline Isndopvarlatchdata_t* Isndopvarlatchdata_t::FromRaw(CEntityInstance*) { return nullptr; }
inline Isndopvarlatchdata_t* Isndopvarlatchdata_t::FromOriginal(sndopvarlatchdata_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_SNDOPVARLATCHDATA_TIMPL_H
