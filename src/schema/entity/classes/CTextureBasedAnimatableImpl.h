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

#ifndef _INCLUDE_CTEXTUREBASEDANIMATABLEIMPL_H
#define _INCLUDE_CTEXTUREBASEDANIMATABLEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/ITextureBasedAnimatable.h"
#include "schema/entity/classes/CTextureBasedAnimatable.h"
#include "CBaseModelEntityImpl.h"

class CTextureBasedAnimatableImpl : public CBaseModelEntityImpl, public virtual ITextureBasedAnimatable
{

public:
    explicit CTextureBasedAnimatableImpl(CTextureBasedAnimatable* p) : CBaseModelEntityImpl(p) {}

private:
    CTextureBasedAnimatable* Real() { return static_cast<CTextureBasedAnimatable*>(m_pReal); }
    CTextureBasedAnimatable* Real() const { return static_cast<CTextureBasedAnimatable*>(m_pReal); }

public:
    CTextureBasedAnimatable* GetOriginal() const override { return Real(); }
    bool& Loop() override { return Real()->m_bLoop(); }
    void LoopUpdated() override { Real()->m_bLoop.NetworkStateChanged(); }
    float& FPS() override { return Real()->m_flFPS(); }
    void FPSUpdated() override { Real()->m_flFPS.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& PositionKeys() override { return Real()->m_hPositionKeys(); }
    void PositionKeysUpdated() override { Real()->m_hPositionKeys.NetworkStateChanged(); }
    CStrongHandle<InfoForResourceTypeCTextureBase>& RotationKeys() override { return Real()->m_hRotationKeys(); }
    void RotationKeysUpdated() override { Real()->m_hRotationKeys.NetworkStateChanged(); }
    Vector& AnimationBoundsMin() override { return Real()->m_vAnimationBoundsMin(); }
    void AnimationBoundsMinUpdated() override { Real()->m_vAnimationBoundsMin.NetworkStateChanged(); }
    Vector& AnimationBoundsMax() override { return Real()->m_vAnimationBoundsMax(); }
    void AnimationBoundsMaxUpdated() override { Real()->m_vAnimationBoundsMax.NetworkStateChanged(); }
    float& StartTime() override { return Real()->m_flStartTime(); }
    void StartTimeUpdated() override { Real()->m_flStartTime.NetworkStateChanged(); }
    float& StartFrame() override { return Real()->m_flStartFrame(); }
    void StartFrameUpdated() override { Real()->m_flStartFrame.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline ITextureBasedAnimatable* CTextureBasedAnimatable::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<ITextureBasedAnimatable*>(tagIt->second.ptr_for_return);
    auto* impl = new CTextureBasedAnimatableImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<ITextureBasedAnimatable*>(impl));
    return impl;
}
inline ITextureBasedAnimatable* ITextureBasedAnimatable::FromRaw(CEntityInstance* p) { return p ? static_cast<CTextureBasedAnimatable*>(p)->ToInterface() : nullptr; }
inline ITextureBasedAnimatable* ITextureBasedAnimatable::FromOriginal(CTextureBasedAnimatable* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CTEXTUREBASEDANIMATABLEIMPL_H
