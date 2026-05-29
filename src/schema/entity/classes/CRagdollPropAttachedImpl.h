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

#ifndef _INCLUDE_CRAGDOLLPROPATTACHEDIMPL_H
#define _INCLUDE_CRAGDOLLPROPATTACHEDIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IRagdollPropAttached.h"
#include "schema/entity/classes/CRagdollPropAttached.h"
#include "CRagdollPropImpl.h"

class CRagdollPropAttachedImpl : public CRagdollPropImpl, public virtual IRagdollPropAttached
{

public:
    explicit CRagdollPropAttachedImpl(CRagdollPropAttached* p) : CRagdollPropImpl(p) {}

private:
    CRagdollPropAttached* Real() { return static_cast<CRagdollPropAttached*>(m_pReal); }
    CRagdollPropAttached* Real() const { return static_cast<CRagdollPropAttached*>(m_pReal); }

public:
    CRagdollPropAttached* GetOriginal() const override { return Real(); }
    uint32_t& BoneIndexAttached() override { return Real()->m_boneIndexAttached(); }
    void BoneIndexAttachedUpdated() override { Real()->m_boneIndexAttached.NetworkStateChanged(); }
    uint32_t& RagdollAttachedObjectIndex() override { return Real()->m_ragdollAttachedObjectIndex(); }
    void RagdollAttachedObjectIndexUpdated() override { Real()->m_ragdollAttachedObjectIndex.NetworkStateChanged(); }
    Vector& AttachmentPointBoneSpace() override { return Real()->m_attachmentPointBoneSpace(); }
    void AttachmentPointBoneSpaceUpdated() override { Real()->m_attachmentPointBoneSpace.NetworkStateChanged(); }
    Vector& AttachmentPointRagdollSpace() override { return Real()->m_attachmentPointRagdollSpace(); }
    void AttachmentPointRagdollSpaceUpdated() override { Real()->m_attachmentPointRagdollSpace.NetworkStateChanged(); }
    bool& ShouldDetach() override { return Real()->m_bShouldDetach(); }
    void ShouldDetachUpdated() override { Real()->m_bShouldDetach.NetworkStateChanged(); }
    bool& ShouldDeleteAttachedActivationRecord() override { return Real()->m_bShouldDeleteAttachedActivationRecord(); }
    void ShouldDeleteAttachedActivationRecordUpdated() override { Real()->m_bShouldDeleteAttachedActivationRecord.NetworkStateChanged(); }
};

#include "core/virtualhooks.h"

inline IRagdollPropAttached* CRagdollPropAttached::ToInterface()
{
    static const char s_tag = 0;
    auto& byTag = virtualhooks::entityInterfaces[this];
    auto tagIt = byTag.find(&s_tag);
    if (tagIt != byTag.end())
        return static_cast<IRagdollPropAttached*>(tagIt->second.ptr_for_return);
    auto* impl = new CRagdollPropAttachedImpl(this);
    byTag[&s_tag] = virtualhooks::EntityImplEntry(static_cast<IEntityInstance*>(impl), static_cast<IRagdollPropAttached*>(impl));
    return impl;
}
inline IRagdollPropAttached* IRagdollPropAttached::FromRaw(CEntityInstance* p) { return p ? static_cast<CRagdollPropAttached*>(p)->ToInterface() : nullptr; }
inline IRagdollPropAttached* IRagdollPropAttached::FromOriginal(CRagdollPropAttached* p) { return p ? p->ToInterface() : nullptr; }

#endif // _INCLUDE_CRAGDOLLPROPATTACHEDIMPL_H
