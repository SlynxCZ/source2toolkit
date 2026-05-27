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

#ifndef _INCLUDE_CCSPLAYERCONTROLLER_INGAMEMONEYSERVICESIMPL_H
#define _INCLUDE_CCSPLAYERCONTROLLER_INGAMEMONEYSERVICESIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ICSPlayerController_InGameMoneyServices.h"
#include "schema/entity/classes/CCSPlayerController_InGameMoneyServices.h"
#include "CPlayerControllerComponentImpl.h"

class CCSPlayerController_InGameMoneyServicesImpl : public CPlayerControllerComponentImpl, public ICSPlayerController_InGameMoneyServices
{

public:
    explicit CCSPlayerController_InGameMoneyServicesImpl(CCSPlayerController_InGameMoneyServices* p) : CPlayerControllerComponentImpl(p) {}

private:
    CCSPlayerController_InGameMoneyServices* Real() { return static_cast<CCSPlayerController_InGameMoneyServices*>(m_pReal); }

public:
    bool& ReceivesMoneyNextRound() override { return Real()->m_bReceivesMoneyNextRound(); }
    void ReceivesMoneyNextRoundUpdated() override { Real()->m_bReceivesMoneyNextRound.NetworkStateChanged(); }
    int32_t& MoneyEarnedForNextRound() override { return Real()->m_iMoneyEarnedForNextRound(); }
    void MoneyEarnedForNextRoundUpdated() override { Real()->m_iMoneyEarnedForNextRound.NetworkStateChanged(); }
    int32_t& Account() override { return Real()->m_iAccount(); }
    void AccountUpdated() override { Real()->m_iAccount.NetworkStateChanged(); }
    int32_t& StartAccount() override { return Real()->m_iStartAccount(); }
    void StartAccountUpdated() override { Real()->m_iStartAccount.NetworkStateChanged(); }
    int32_t& TotalCashSpent() override { return Real()->m_iTotalCashSpent(); }
    void TotalCashSpentUpdated() override { Real()->m_iTotalCashSpent.NetworkStateChanged(); }
    int32_t& CashSpentThisRound() override { return Real()->m_iCashSpentThisRound(); }
    void CashSpentThisRoundUpdated() override { Real()->m_iCashSpentThisRound.NetworkStateChanged(); }
};

#endif // _INCLUDE_CCSPLAYERCONTROLLER_INGAMEMONEYSERVICESIMPL_H
