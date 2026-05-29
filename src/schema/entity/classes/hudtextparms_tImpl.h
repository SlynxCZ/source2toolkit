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

#ifndef _INCLUDE_HUDTEXTPARMS_TIMPL_H
#define _INCLUDE_HUDTEXTPARMS_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/Ihudtextparms_t.h"
#include "schema/entity/classes/hudtextparms_t.h"

class hudtextparms_tImpl : public virtual Ihudtextparms_t
{

protected:
    void* m_pReal;

public:
    explicit hudtextparms_tImpl(void* p) : m_pReal(p) {}

private:
    hudtextparms_t* Real() { return static_cast<hudtextparms_t*>(m_pReal); }
    hudtextparms_t* Real() const { return static_cast<hudtextparms_t*>(m_pReal); }

public:
    hudtextparms_t* GetOriginal() const override { return Real(); }
    Color& Color1() override { return Real()->color1(); }
    void Color1Updated() override { Real()->color1.NetworkStateChanged(); }
    Color& Color2() override { return Real()->color2(); }
    void Color2Updated() override { Real()->color2.NetworkStateChanged(); }
    uint8_t& Effect() override { return Real()->effect(); }
    void EffectUpdated() override { Real()->effect.NetworkStateChanged(); }
    uint8_t& Channel() override { return Real()->channel(); }
    void ChannelUpdated() override { Real()->channel.NetworkStateChanged(); }
    float& X() override { return Real()->x(); }
    void XUpdated() override { Real()->x.NetworkStateChanged(); }
    float& Y() override { return Real()->y(); }
    void YUpdated() override { Real()->y.NetworkStateChanged(); }
};

inline Ihudtextparms_t* hudtextparms_t::ToInterface() { return new hudtextparms_tImpl(this); }
inline Ihudtextparms_t* Ihudtextparms_t::FromRaw(CEntityInstance*) { return nullptr; }
inline Ihudtextparms_t* Ihudtextparms_t::FromOriginal(hudtextparms_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_HUDTEXTPARMS_TIMPL_H
