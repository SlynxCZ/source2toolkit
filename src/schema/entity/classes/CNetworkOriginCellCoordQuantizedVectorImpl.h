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

#ifndef _INCLUDE_CNETWORKORIGINCELLCOORDQUANTIZEDVECTORIMPL_H
#define _INCLUDE_CNETWORKORIGINCELLCOORDQUANTIZEDVECTORIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/INetworkOriginCellCoordQuantizedVector.h"
#include "schema/entity/classes/CNetworkOriginCellCoordQuantizedVector.h"

class CNetworkOriginCellCoordQuantizedVectorImpl : public virtual INetworkOriginCellCoordQuantizedVector
{

protected:
    void* m_pReal;

public:
    explicit CNetworkOriginCellCoordQuantizedVectorImpl(void* p) : m_pReal(p) {}

private:
    CNetworkOriginCellCoordQuantizedVector* Real() { return static_cast<CNetworkOriginCellCoordQuantizedVector*>(m_pReal); }
    CNetworkOriginCellCoordQuantizedVector* Real() const { return static_cast<CNetworkOriginCellCoordQuantizedVector*>(m_pReal); }

public:
    CNetworkOriginCellCoordQuantizedVector* GetOriginal() const override { return Real(); }
    uint16_t& CellX() override { return Real()->m_cellX(); }
    void CellXUpdated() override { Real()->m_cellX.NetworkStateChanged(); }
    uint16_t& CellY() override { return Real()->m_cellY(); }
    void CellYUpdated() override { Real()->m_cellY.NetworkStateChanged(); }
    uint16_t& CellZ() override { return Real()->m_cellZ(); }
    void CellZUpdated() override { Real()->m_cellZ.NetworkStateChanged(); }
    uint16_t& OutsideWorld() override { return Real()->m_nOutsideWorld(); }
    void OutsideWorldUpdated() override { Real()->m_nOutsideWorld.NetworkStateChanged(); }
    float& X() override { return Real()->m_vecX(); }
    void XUpdated() override { Real()->m_vecX.NetworkStateChanged(); }
    float& Y() override { return Real()->m_vecY(); }
    void YUpdated() override { Real()->m_vecY.NetworkStateChanged(); }
    float& Z() override { return Real()->m_vecZ(); }
    void ZUpdated() override { Real()->m_vecZ.NetworkStateChanged(); }
};

inline INetworkOriginCellCoordQuantizedVector* CNetworkOriginCellCoordQuantizedVector::ToInterface() { return new CNetworkOriginCellCoordQuantizedVectorImpl(this); }
inline INetworkOriginCellCoordQuantizedVector* INetworkOriginCellCoordQuantizedVector::FromOriginal(CNetworkOriginCellCoordQuantizedVector* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CNETWORKORIGINCELLCOORDQUANTIZEDVECTORIMPL_H
