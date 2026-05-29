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

#ifndef _INCLUDE_CSPRITEIMPL_H
#define _INCLUDE_CSPRITEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ISprite.h"
#include "schema/entity/classes/CSprite.h"
#include "CBaseModelEntityImpl.h"

class CSpriteImpl : public CBaseModelEntityImpl, public virtual ISprite
{

public:
    explicit CSpriteImpl(CSprite* p) : CBaseModelEntityImpl(p) {}

private:
    CSprite* Real() { return static_cast<CSprite*>(m_pReal); }
    CSprite* Real() const { return static_cast<CSprite*>(m_pReal); }

public:
    CSprite* GetOriginal() const override { return Real(); }
    CStrongHandle<InfoForResourceTypeIMaterial2>& SpriteMaterial() override { return Real()->m_hSpriteMaterial(); }
    void SpriteMaterialUpdated() override { Real()->m_hSpriteMaterial.NetworkStateChanged(); }
    CHandle<CBaseEntity>& AttachedToEntity() override { return Real()->m_hAttachedToEntity(); }
    void AttachedToEntityUpdated() override { Real()->m_hAttachedToEntity.NetworkStateChanged(); }
    float& SpriteFramerate() override { return Real()->m_flSpriteFramerate(); }
    void SpriteFramerateUpdated() override { Real()->m_flSpriteFramerate.NetworkStateChanged(); }
    float& Frame() override { return Real()->m_flFrame(); }
    void FrameUpdated() override { Real()->m_flFrame.NetworkStateChanged(); }
    float& DieTime() override { return Real()->m_flDieTime(); }
    void DieTimeUpdated() override { Real()->m_flDieTime.NetworkStateChanged(); }
    uint32_t& Brightness() override { return Real()->m_nBrightness(); }
    void BrightnessUpdated() override { Real()->m_nBrightness.NetworkStateChanged(); }
    float& BrightnessDuration() override { return Real()->m_flBrightnessDuration(); }
    void BrightnessDurationUpdated() override { Real()->m_flBrightnessDuration.NetworkStateChanged(); }
    float& SpriteScale() override { return Real()->m_flSpriteScale(); }
    void SpriteScaleUpdated() override { Real()->m_flSpriteScale.NetworkStateChanged(); }
    float& ScaleDuration() override { return Real()->m_flScaleDuration(); }
    void ScaleDurationUpdated() override { Real()->m_flScaleDuration.NetworkStateChanged(); }
    bool& WorldSpaceScale() override { return Real()->m_bWorldSpaceScale(); }
    void WorldSpaceScaleUpdated() override { Real()->m_bWorldSpaceScale.NetworkStateChanged(); }
    float& GlowProxySize() override { return Real()->m_flGlowProxySize(); }
    void GlowProxySizeUpdated() override { Real()->m_flGlowProxySize.NetworkStateChanged(); }
    float& HDRColorScale() override { return Real()->m_flHDRColorScale(); }
    void HDRColorScaleUpdated() override { Real()->m_flHDRColorScale.NetworkStateChanged(); }
    float& LastTime() override { return Real()->m_flLastTime(); }
    void LastTimeUpdated() override { Real()->m_flLastTime.NetworkStateChanged(); }
    float& MaxFrame() override { return Real()->m_flMaxFrame(); }
    void MaxFrameUpdated() override { Real()->m_flMaxFrame.NetworkStateChanged(); }
    float& StartScale() override { return Real()->m_flStartScale(); }
    void StartScaleUpdated() override { Real()->m_flStartScale.NetworkStateChanged(); }
    float& DestScale() override { return Real()->m_flDestScale(); }
    void DestScaleUpdated() override { Real()->m_flDestScale.NetworkStateChanged(); }
    float& ScaleTimeStart() override { return Real()->m_flScaleTimeStart(); }
    void ScaleTimeStartUpdated() override { Real()->m_flScaleTimeStart.NetworkStateChanged(); }
    int32_t& StartBrightness() override { return Real()->m_nStartBrightness(); }
    void StartBrightnessUpdated() override { Real()->m_nStartBrightness.NetworkStateChanged(); }
    int32_t& DestBrightness() override { return Real()->m_nDestBrightness(); }
    void DestBrightnessUpdated() override { Real()->m_nDestBrightness.NetworkStateChanged(); }
    float& BrightnessTimeStart() override { return Real()->m_flBrightnessTimeStart(); }
    void BrightnessTimeStartUpdated() override { Real()->m_flBrightnessTimeStart.NetworkStateChanged(); }
    int32_t& SpriteWidth() override { return Real()->m_nSpriteWidth(); }
    void SpriteWidthUpdated() override { Real()->m_nSpriteWidth.NetworkStateChanged(); }
    int32_t& SpriteHeight() override { return Real()->m_nSpriteHeight(); }
    void SpriteHeightUpdated() override { Real()->m_nSpriteHeight.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ISprite* CSprite::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ISprite*>(tagIt->second.ptr_for_return);
    auto* impl = new CSpriteImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ISprite*>(impl));
    return impl;
}
inline ISprite* ISprite::FromRaw(CEntityInstance* p) { return p ? static_cast<CSprite*>(p)->ToInterface() : nullptr; }
inline ISprite* ISprite::FromOriginal(CSprite* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CSPRITEIMPL_H
