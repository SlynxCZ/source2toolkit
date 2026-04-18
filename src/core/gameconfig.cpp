//
// Created by Michal Přikryl on 20.06.2025.
// Copyright (c) 2025 slynxcz. All rights reserved.
//
#include "plugin.h"
#include "gameconfig.h"
#include <fstream>

CGameConfig::CGameConfig(const std::string& path) { m_sPath = path; }

CGameConfig::~CGameConfig() = default;

bool CGameConfig::LoadSingle(const std::string& path, char* conf_error, int conf_error_size)
{
    std::ifstream ifs(path);
    if (!ifs)
    {
        V_snprintf(conf_error, conf_error_size, "Failed to open: %s", path.c_str());
        return false;
    }

    json j = json::parse(ifs);

#if _WIN32
    constexpr auto platform = "windows";
#else
    constexpr auto platform = "linux";
#endif

    try
    {
        for (auto& [k, v] : j.items())
        {
            if (v.contains("signatures"))
            {
                if (auto library = v["signatures"]["library"]; library.is_string())
                {
                    m_umLibraries.try_emplace(k, library.get<std::string>());
                }

                if (auto signature = v["signatures"][platform]; signature.is_string())
                {
                    m_umSignatures.try_emplace(k, signature.get<std::string>());
                }
            }

            if (v.contains("offsets"))
            {
                if (auto offset = v["offsets"][platform]; offset.is_number_integer())
                {
                    m_umOffsets.try_emplace(k, offset.get<std::int64_t>());
                }
            }

            if (v.contains("patches"))
            {
                if (auto patch = v["patches"][platform]; patch.is_string())
                {
                    m_umPatches.try_emplace(k, patch.get<std::string>());
                }
            }
        }
    }
    catch (const std::exception& ex)
    {
        V_snprintf(conf_error, conf_error_size, "Parse error in %s: %s", path.c_str(), ex.what());
        return false;
    }

    return true;
}

bool CGameConfig::InitAll(const std::string& folder, char* conf_error, int conf_error_size)
{
    namespace fs = std::filesystem;

    std::vector<fs::path> files;

    for (const auto& entry : fs::directory_iterator(folder))
    {
        if (entry.path().extension() == ".json")
        {
            files.push_back(entry.path());
        }
    }

    std::sort(files.begin(), files.end(), [](const fs::path& a, const fs::path& b)
    {
        if (a.filename() == "gamedata.json") return true;
        if (b.filename() == "gamedata.json") return false;
        return a.filename() < b.filename();
    });

    for (const auto& file : files)
    {
        if (!LoadSingle(file.string(), conf_error, conf_error_size))
        {
            return false;
        }
    }

    return true;
}

const std::string CGameConfig::GetPath() { return m_sPath; }

const char* CGameConfig::GetLibrary(const char* pchName)
{
    auto it = m_umLibraries.find(pchName);
    if (it == m_umLibraries.end())
    {
        return nullptr;
    }
    return it->second.c_str();
}

const char* CGameConfig::GetSignature(const char* pchName)
{
    auto it = m_umSignatures.find(pchName);
    if (it == m_umSignatures.end())
    {
        return nullptr;
    }
    return it->second.c_str();
}

const char* CGameConfig::GetSymbol(const char* pchName)
{
    return nullptr;
}

const char* CGameConfig::GetPatch(const char* pchName)
{
    auto it = m_umPatches.find(pchName);
    if (it == m_umPatches.end())
    {
        return nullptr;
    }
    return it->second.c_str();
}

int CGameConfig::GetOffset(const char* pchName)
{
    auto it = m_umOffsets.find(pchName);
    if (it == m_umOffsets.end())
    {
        return -1;
    }
    return it->second;
}
