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

#ifndef _INCLUDE_CPOINTCLIENTUIDIALOGIMPL_H
#define _INCLUDE_CPOINTCLIENTUIDIALOGIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IPointClientUIDialog.h"
#include "schema/entity/classes/CPointClientUIDialog.h"
#include "CBaseClientUIEntityImpl.h"

class CPointClientUIDialogImpl : public CBaseClientUIEntityImpl, public virtual IPointClientUIDialog
{

public:
    explicit CPointClientUIDialogImpl(CPointClientUIDialog* p) : CBaseClientUIEntityImpl(p) {}

private:
    CPointClientUIDialog* Real() { return static_cast<CPointClientUIDialog*>(m_pReal); }
    CPointClientUIDialog* Real() const { return static_cast<CPointClientUIDialog*>(m_pReal); }

public:
    CPointClientUIDialog* GetOriginal() const override { return Real(); }
    CHandle<CBaseEntity>& Activator() override { return Real()->m_hActivator(); }
    void ActivatorUpdated() override { Real()->m_hActivator.NetworkStateChanged(); }
    bool& StartEnabled() override { return Real()->m_bStartEnabled(); }
    void StartEnabledUpdated() override { Real()->m_bStartEnabled.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IPointClientUIDialog* CPointClientUIDialog::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IPointClientUIDialog*>(tagIt->second.ptr_for_return);
    auto* impl = new CPointClientUIDialogImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IPointClientUIDialog*>(impl));
    return impl;
}
inline IPointClientUIDialog* IPointClientUIDialog::FromRaw(CEntityInstance* p) { return p ? static_cast<CPointClientUIDialog*>(p)->ToInterface() : nullptr; }
inline IPointClientUIDialog* IPointClientUIDialog::FromOriginal(CPointClientUIDialog* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CPOINTCLIENTUIDIALOGIMPL_H
