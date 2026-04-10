//
// Created by Michal Přikryl on 20.06.2025.
// Copyright (c) 2025 slynxcz. All rights reserved.
//
#pragma once
#include "nlohmann/json.hpp"
#include "KeyValues.h"

#include "source2toolkit/IToolkitGameConfig.h"

#include <string>
#include <unordered_map>

#undef snprintf

class CGameConfig : public IToolkitGameConfig
{
public:
    using json = nlohmann::json;
    CGameConfig(const std::string& path);
    ~CGameConfig();

    bool Init(char* conf_error, int conf_error_size);
    const std::string GetPath();
    const char* GetLibrary(const char* pchName) override;
    const char* GetSignature(const char* pchName) override;
    const char* GetSymbol(const char* pchName) override;
    const char* GetPatch(const char* pchName) override;
    int GetOffset(const char* pchName) override;

private:
    std::string m_sPath;
    // use Valve KeyValues in the future.
    // since we'd better make '\' easier.
    json m_json;
    std::unordered_map<std::string, int> m_umOffsets;
    std::unordered_map<std::string, std::string> m_umSignatures;
    std::unordered_map<std::string, void*> m_umAddresses;
    std::unordered_map<std::string, std::string> m_umLibraries;
    std::unordered_map<std::string, std::string> m_umPatches;
};
