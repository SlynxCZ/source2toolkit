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

#ifndef _INCLUDE_CENVCUBEMAPIMPL_H
#define _INCLUDE_CENVCUBEMAPIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvCubemap.h"
#include "schema/entity/classes/CEnvCubemap.h"
#include "CBaseEntityImpl.h"

class CEnvCubemapImpl : public CBaseEntityImpl, public virtual IEnvCubemap
{

public:
    explicit CEnvCubemapImpl(CEnvCubemap* p) : CBaseEntityImpl(p) {}

private:
    CEnvCubemap* Real() { return static_cast<CEnvCubemap*>(m_pReal); }
    CEnvCubemap* Real() const { return static_cast<CEnvCubemap*>(m_pReal); }

public:
    CEnvCubemap* GetOriginal() const override { return Real(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& Entity_hCubemapTexture() override { return Real()->m_Entity_hCubemapTexture(); }
    void Entity_hCubemapTextureUpdated() override { Real()->m_Entity_hCubemapTexture.NetworkStateChanged(); }
    bool& Entity_bCustomCubemapTexture() override { return Real()->m_Entity_bCustomCubemapTexture(); }
    void Entity_bCustomCubemapTextureUpdated() override { Real()->m_Entity_bCustomCubemapTexture.NetworkStateChanged(); }
    float& Entity_flInfluenceRadius() override { return Real()->m_Entity_flInfluenceRadius(); }
    void Entity_flInfluenceRadiusUpdated() override { Real()->m_Entity_flInfluenceRadius.NetworkStateChanged(); }
    Vector& Entity_vBoxProjectMins() override { return Real()->m_Entity_vBoxProjectMins(); }
    void Entity_vBoxProjectMinsUpdated() override { Real()->m_Entity_vBoxProjectMins.NetworkStateChanged(); }
    Vector& Entity_vBoxProjectMaxs() override { return Real()->m_Entity_vBoxProjectMaxs(); }
    void Entity_vBoxProjectMaxsUpdated() override { Real()->m_Entity_vBoxProjectMaxs.NetworkStateChanged(); }
    bool& Entity_bMoveable() override { return Real()->m_Entity_bMoveable(); }
    void Entity_bMoveableUpdated() override { Real()->m_Entity_bMoveable.NetworkStateChanged(); }
    int32_t& Entity_nHandshake() override { return Real()->m_Entity_nHandshake(); }
    void Entity_nHandshakeUpdated() override { Real()->m_Entity_nHandshake.NetworkStateChanged(); }
    int32_t& Entity_nEnvCubeMapArrayIndex() override { return Real()->m_Entity_nEnvCubeMapArrayIndex(); }
    void Entity_nEnvCubeMapArrayIndexUpdated() override { Real()->m_Entity_nEnvCubeMapArrayIndex.NetworkStateChanged(); }
    int32_t& Entity_nPriority() override { return Real()->m_Entity_nPriority(); }
    void Entity_nPriorityUpdated() override { Real()->m_Entity_nPriority.NetworkStateChanged(); }
    float& Entity_flEdgeFadeDist() override { return Real()->m_Entity_flEdgeFadeDist(); }
    void Entity_flEdgeFadeDistUpdated() override { Real()->m_Entity_flEdgeFadeDist.NetworkStateChanged(); }
    Vector& Entity_vEdgeFadeDists() override { return Real()->m_Entity_vEdgeFadeDists(); }
    void Entity_vEdgeFadeDistsUpdated() override { Real()->m_Entity_vEdgeFadeDists.NetworkStateChanged(); }
    float& Entity_flDiffuseScale() override { return Real()->m_Entity_flDiffuseScale(); }
    void Entity_flDiffuseScaleUpdated() override { Real()->m_Entity_flDiffuseScale.NetworkStateChanged(); }
    bool& Entity_bStartDisabled() override { return Real()->m_Entity_bStartDisabled(); }
    void Entity_bStartDisabledUpdated() override { Real()->m_Entity_bStartDisabled.NetworkStateChanged(); }
    bool& Entity_bDefaultEnvMap() override { return Real()->m_Entity_bDefaultEnvMap(); }
    void Entity_bDefaultEnvMapUpdated() override { Real()->m_Entity_bDefaultEnvMap.NetworkStateChanged(); }
    bool& Entity_bDefaultSpecEnvMap() override { return Real()->m_Entity_bDefaultSpecEnvMap(); }
    void Entity_bDefaultSpecEnvMapUpdated() override { Real()->m_Entity_bDefaultSpecEnvMap.NetworkStateChanged(); }
    bool& Entity_bIndoorCubeMap() override { return Real()->m_Entity_bIndoorCubeMap(); }
    void Entity_bIndoorCubeMapUpdated() override { Real()->m_Entity_bIndoorCubeMap.NetworkStateChanged(); }
    bool& Entity_bCopyDiffuseFromDefaultCubemap() override { return Real()->m_Entity_bCopyDiffuseFromDefaultCubemap(); }
    void Entity_bCopyDiffuseFromDefaultCubemapUpdated() override { Real()->m_Entity_bCopyDiffuseFromDefaultCubemap.NetworkStateChanged(); }
    bool& Entity_bEnabled() override { return Real()->m_Entity_bEnabled(); }
    void Entity_bEnabledUpdated() override { Real()->m_Entity_bEnabled.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IEnvCubemap* CEnvCubemap::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IEnvCubemap*>(tagIt->second.ptr_for_return);
    auto* impl = new CEnvCubemapImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IEnvCubemap*>(impl));
    return impl;
}
inline IEnvCubemap* IEnvCubemap::FromRaw(CEntityInstance* p) { return p ? static_cast<CEnvCubemap*>(p)->ToInterface() : nullptr; }
inline IEnvCubemap* IEnvCubemap::FromOriginal(CEnvCubemap* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CENVCUBEMAPIMPL_H
