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

#ifndef _INCLUDE_CENVLASERIMPL_H
#define _INCLUDE_CENVLASERIMPL_H

#pragma once

#include "source2toolkit/schema/entity/iclasses/IEnvLaser.h"
#include "schema/entity/classes/CEnvLaser.h"
#include "CBeamImpl.h"

class CEnvLaserImpl : public CBeamImpl, public IEnvLaser
{

public:
    explicit CEnvLaserImpl(CEnvLaser* p) : CBeamImpl(p) {}

private:
    CEnvLaser* Real() { return static_cast<CEnvLaser*>(m_pReal); }

public:
    CUtlSymbolLarge& LaserTarget() override { return Real()->m_iszLaserTarget(); }
    void LaserTargetUpdated() override { Real()->m_iszLaserTarget.NetworkStateChanged(); }
    CHandle<CSprite>& Sprite() override { return Real()->m_pSprite(); }
    void SpriteUpdated() override { Real()->m_pSprite.NetworkStateChanged(); }
    CUtlSymbolLarge& SpriteName() override { return Real()->m_iszSpriteName(); }
    void SpriteNameUpdated() override { Real()->m_iszSpriteName.NetworkStateChanged(); }
    Vector& FirePosition() override { return Real()->m_firePosition(); }
    void FirePositionUpdated() override { Real()->m_firePosition.NetworkStateChanged(); }
    float& StartFrame() override { return Real()->m_flStartFrame(); }
    void StartFrameUpdated() override { Real()->m_flStartFrame.NetworkStateChanged(); }
};

#endif // _INCLUDE_CENVLASERIMPL_H
