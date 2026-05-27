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

#ifndef _INCLUDE_CENVSOUNDSCAPETRIGGERABLEALIAS_SND_SOUNDSCAPE_TRIGGERABLEIMPL_H
#define _INCLUDE_CENVSOUNDSCAPETRIGGERABLEALIAS_SND_SOUNDSCAPE_TRIGGERABLEIMPL_H

#pragma once

#include "source2toolkit/schema/entity/classes/IEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable.h"
#include "schema/entity/classes/CEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable.h"
#include "CEnvSoundscapeTriggerableImpl.h"

class CEnvSoundscapeTriggerableAlias_snd_soundscape_triggerableImpl : public CEnvSoundscapeTriggerableImpl, public IEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable
{

public:
    explicit CEnvSoundscapeTriggerableAlias_snd_soundscape_triggerableImpl(CEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable* p) : CEnvSoundscapeTriggerableImpl(p) {}

private:
    CEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable* Real() { return static_cast<CEnvSoundscapeTriggerableAlias_snd_soundscape_triggerable*>(m_pReal); }

public:
};

#endif // _INCLUDE_CENVSOUNDSCAPETRIGGERABLEALIAS_SND_SOUNDSCAPE_TRIGGERABLEIMPL_H
