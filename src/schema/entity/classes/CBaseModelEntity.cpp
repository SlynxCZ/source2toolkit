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

#include "schema/entity/classes/CBaseModelEntityImpl.h"

#include "schema/entity/classes/CBodyComponent.h"
#include "schema/entity/classes/CSkeletonInstance.h"

#include "core/addresses.h"
#include "core/virtualhooks.h"

CUtlSymbolLarge CBaseModelEntity::GetModelName()
{
    if(m_CBodyComponent == nullptr) return CUtlSymbolLarge();
    if(m_CBodyComponent->m_pSceneNode == nullptr) return CUtlSymbolLarge();
    if(((CSkeletonInstance*)m_CBodyComponent->m_pSceneNode.Get()) == nullptr) return CUtlSymbolLarge();
    return ((CSkeletonInstance*)m_CBodyComponent->m_pSceneNode.Get())->m_modelState().m_ModelName.Get();
}

Vector CBaseModelEntity::GetEyePosition()
{
    Vector x = Vector(m_vecViewOffset().m_vecX, m_vecViewOffset().m_vecY, m_vecViewOffset().m_vecZ);
    Vector m_vecOrigin = GetAbsOrigin();
    return {
        m_vecOrigin.x + x.x,
        m_vecOrigin.y + x.y,
        m_vecOrigin.z + x.z
    };
}

void CBaseModelEntity::SetModel(const char* pszModel) {
    addresses::toolkitAddresses.SetModel(this, pszModel);
}
IBaseModelEntity* CBaseModelEntity::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IBaseModelEntity*>(tagIt->second.ptr_for_return);
    auto* impl = new CBaseModelEntityImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IBaseModelEntity*>(impl));
    return impl;
}

IBaseModelEntity* IBaseModelEntity::FromRaw(CEntityInstance* p)
{
    return p ? static_cast<CBaseModelEntity*>(p)->ToInterface() : nullptr;
}

IBaseModelEntity* IBaseModelEntity::FromOriginal(CBaseModelEntity* p)
{ return CBaseModelEntity::FromOriginal(p); }
