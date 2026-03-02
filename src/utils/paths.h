//
// Created by Michal Přikryl on 02.03.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#pragma once

#include "core/shared.h"
#include <eiface.h>
#include <string>

namespace paths {
    static std::string gameDirectory;

    inline std::string GameDirectory() {
        if (gameDirectory.empty()) {
            CBufferStringGrowable<255> gamePath;
            shared::g_pEngine->GetGameDir(gamePath);
            gameDirectory = std::string(gamePath.Get());
        }
        return gameDirectory;
    }

    inline std::string GetRootDirectory() { return GameDirectory() + "/addons/source2toolkit"; }
    inline std::string EnginePath() { return GameDirectory() + "../bin/linuxsteamrt64/libengine2.so"; }
    inline std::string Tier0Path() { return GameDirectory() + "../bin/linuxsteamrt64/libtier0.so"; }
    inline std::string ServerPath() { return GameDirectory() + "/bin/linuxsteamrt64/libserver.so"; }
    inline std::string SchemaSystemPath() { return GameDirectory() + "../bin/linuxsteamrt64/libschemasystem.so"; }
    inline std::string VScriptPath() { return GameDirectory() + "../bin/linuxsteamrt64/libvscript.so"; }
} // namespace paths