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

#ifndef _INCLUDE_DYNAMICVOLUMEDEF_TIMPL_H
#define _INCLUDE_DYNAMICVOLUMEDEF_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IDynamicVolumeDef_t.h"
#include "schema/entity/classes/DynamicVolumeDef_t.h"

class DynamicVolumeDef_tImpl : public virtual IDynamicVolumeDef_t
{

protected:
    void* m_pReal;

public:
    explicit DynamicVolumeDef_tImpl(void* p) : m_pReal(p) {}

private:
    DynamicVolumeDef_t* Real() { return static_cast<DynamicVolumeDef_t*>(m_pReal); }
    DynamicVolumeDef_t* Real() const { return static_cast<DynamicVolumeDef_t*>(m_pReal); }

public:
    DynamicVolumeDef_t* GetOriginal() const override { return Real(); }
    CHandle<CBaseEntity>& Source() override { return Real()->m_source(); }
    void SourceUpdated() override { Real()->m_source.NetworkStateChanged(); }
    CHandle<CBaseEntity>& Target() override { return Real()->m_target(); }
    void TargetUpdated() override { Real()->m_target.NetworkStateChanged(); }
    int32_t& HullIdx() override { return Real()->m_nHullIdx(); }
    void HullIdxUpdated() override { Real()->m_nHullIdx.NetworkStateChanged(); }
    Vector& SourceAnchorPos() override { return Real()->m_vSourceAnchorPos(); }
    void SourceAnchorPosUpdated() override { Real()->m_vSourceAnchorPos.NetworkStateChanged(); }
    Vector& TargetAnchorPos() override { return Real()->m_vTargetAnchorPos(); }
    void TargetAnchorPosUpdated() override { Real()->m_vTargetAnchorPos.NetworkStateChanged(); }
    uint32_t& AreaSrc() override { return Real()->m_nAreaSrc(); }
    void AreaSrcUpdated() override { Real()->m_nAreaSrc.NetworkStateChanged(); }
    uint32_t& AreaDst() override { return Real()->m_nAreaDst(); }
    void AreaDstUpdated() override { Real()->m_nAreaDst.NetworkStateChanged(); }
    bool& Attached() override { return Real()->m_bAttached(); }
    void AttachedUpdated() override { Real()->m_bAttached.NetworkStateChanged(); }
};

inline IDynamicVolumeDef_t* DynamicVolumeDef_t::ToInterface() { return new DynamicVolumeDef_tImpl(this); }
inline IDynamicVolumeDef_t* IDynamicVolumeDef_t::FromOriginal(DynamicVolumeDef_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_DYNAMICVOLUMEDEF_TIMPL_H
