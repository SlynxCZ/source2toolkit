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
