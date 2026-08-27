/**
* vim: set ts=4 sw=4 tw=99 noet:
 * =============================================================================
 * Source2Toolkit
 * Copyright (C) 2025-2026 Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl,
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
 * As a special exception, Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl and
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
 *   - Michal "Slynx (˙·٠● S l y n x ●٠·˙)" Přikryl
 *   - AlliedModders LLC
 *
 * Project: Source2Toolkit
 */
#pragma once
#include "source2toolkit/schema/entityio.h"

// SH_DECL_INLINEHOOK*/SH_ADD_INLINEHOOK and the RETURN_SH/SH_IFACEPTR
// auto-detection that lets one handler body serve either hook style.
#include "sourcehook/sourcehook_inline.h"
#include "eiface.h"
#include "entitysystem.h"

#include "dynlibutils/memaddr.hpp"

namespace inlinehooks {
    class Inlines {
    public:
        void InitListeners();
        void DestructListeners();
    public:
        bool Hook_FilterMessage(const CNetMessage* pData, INetChannel* pChannel);
        void Hook_FireOutputInternal(CEntityInstance* pActivator, CEntityInstance* pCaller, void* variantValue, float delay, void* unk01, void* unk02);
    protected:
        int m_iFilterMessageHookID = 0;
        int m_iFireOutputInternalHookID = 0;
    };

    extern Inlines inlines;
    extern std::unordered_map<OutputKey, EntityIOCallbackPair, OutputKeyHash> entityIOListenerStack;
}
