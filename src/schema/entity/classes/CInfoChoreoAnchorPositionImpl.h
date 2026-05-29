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

#ifndef _INCLUDE_CINFOCHOREOANCHORPOSITIONIMPL_H
#define _INCLUDE_CINFOCHOREOANCHORPOSITIONIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IInfoChoreoAnchorPosition.h"
#include "schema/entity/classes/CInfoChoreoAnchorPosition.h"

class CInfoChoreoAnchorPositionImpl : public virtual IInfoChoreoAnchorPosition
{

protected:
    void* m_pReal;

public:
    explicit CInfoChoreoAnchorPositionImpl(void* p) : m_pReal(p) {}

private:
    CInfoChoreoAnchorPosition* Real() { return static_cast<CInfoChoreoAnchorPosition*>(m_pReal); }
    CInfoChoreoAnchorPosition* Real() const { return static_cast<CInfoChoreoAnchorPosition*>(m_pReal); }

public:
    CInfoChoreoAnchorPosition* GetOriginal() const override { return Real(); }
    Vector& Origin() override { return Real()->m_vOrigin(); }
    void OriginUpdated() override { Real()->m_vOrigin.NetworkStateChanged(); }
    QAngle& Angles() override { return Real()->m_qAngles(); }
    void AnglesUpdated() override { Real()->m_qAngles.NetworkStateChanged(); }
    Vector& ExtentsMin() override { return Real()->m_vExtentsMin(); }
    void ExtentsMinUpdated() override { Real()->m_vExtentsMin.NetworkStateChanged(); }
    Vector& ExtentsMax() override { return Real()->m_vExtentsMax(); }
    void ExtentsMaxUpdated() override { Real()->m_vExtentsMax.NetworkStateChanged(); }
    float& Radius() override { return Real()->m_flRadius(); }
    void RadiusUpdated() override { Real()->m_flRadius.NetworkStateChanged(); }
    CInfoChoreoLocatorShapeType_t& ShapeType() override { return Real()->m_nShapeType(); }
    void ShapeTypeUpdated() override { Real()->m_nShapeType.NetworkStateChanged(); }
};

inline IInfoChoreoAnchorPosition* CInfoChoreoAnchorPosition::ToInterface() { return new CInfoChoreoAnchorPositionImpl(this); }
inline IInfoChoreoAnchorPosition* IInfoChoreoAnchorPosition::FromOriginal(CInfoChoreoAnchorPosition* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CINFOCHOREOANCHORPOSITIONIMPL_H
