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

#ifndef _INCLUDE_EXTERNALANIMGRAPH_TIMPL_H
#define _INCLUDE_EXTERNALANIMGRAPH_TIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IExternalAnimGraph_t.h"
#include "schema/entity/classes/ExternalAnimGraph_t.h"

class ExternalAnimGraph_tImpl : public virtual IExternalAnimGraph_t
{

protected:
    void* m_pReal;

public:
    explicit ExternalAnimGraph_tImpl(void* p) : m_pReal(p) {}

private:
    ExternalAnimGraph_t* Real() { return static_cast<ExternalAnimGraph_t*>(m_pReal); }
    ExternalAnimGraph_t* Real() const { return static_cast<ExternalAnimGraph_t*>(m_pReal); }

public:
    ExternalAnimGraph_t* GetOriginal() const override { return Real(); }
    ExternalAnimGraphHandle_t& ExtGraphHandle() override { return Real()->m_hExtGraphHandle(); }
    void ExtGraphHandleUpdated() override { Real()->m_hExtGraphHandle.NetworkStateChanged(); }
    CGlobalSymbol& ExternalGraphSlotID() override { return Real()->m_sExternalGraphSlotID(); }
    void ExternalGraphSlotIDUpdated() override { Real()->m_sExternalGraphSlotID.NetworkStateChanged(); }
    CStrongHandleCopyable<InfoForResourceTypeCNmGraphDefinition>& GraphDefinition() override { return Real()->m_hGraphDefinition(); }
    void GraphDefinitionUpdated() override { Real()->m_hGraphDefinition.NetworkStateChanged(); }
    CHandle<CBaseAnimGraph>& ExternalGraphOwner() override { return Real()->m_hExternalGraphOwner(); }
    void ExternalGraphOwnerUpdated() override { Real()->m_hExternalGraphOwner.NetworkStateChanged(); }
    ExternalAnimGraphInactiveBehavior_t& InactiveBehavior() override { return Real()->m_nInactiveBehavior(); }
    void InactiveBehaviorUpdated() override { Real()->m_nInactiveBehavior.NetworkStateChanged(); }
};

inline IExternalAnimGraph_t* ExternalAnimGraph_t::ToInterface() { return new ExternalAnimGraph_tImpl(this); }
inline IExternalAnimGraph_t* IExternalAnimGraph_t::FromOriginal(ExternalAnimGraph_t* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_EXTERNALANIMGRAPH_TIMPL_H
