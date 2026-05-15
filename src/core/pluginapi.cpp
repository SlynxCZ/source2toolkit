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
#include "pluginapi.h"
#include <cstring>
#include <stdarg.h>

#include "commands.h"
#include "convars.h"
#include "entities.h"
#include "events.h"
#include "menus.h"
#include "mysql.h"
#include "plugin.h"
#include "source2toolkit/IToolkitPlugin.h"

#include "plugin.h"
#include "pluginmanager.h"
#include "raytrace.h"
#include "utils/scheduler.h"

PluginApi pluginApi;

void PluginApi::Log(IToolkitPlugin *plugin, const char* msg, ...)
{
    va_list ap;
    char buffer[2048];

    va_start(ap, msg);
    FormatArgs(buffer, sizeof(buffer), msg, ap);
    va_end(ap);

    ConPrintf("[%s] %s", plugin->GetName(), buffer);
}

void PluginApi::ConPrint(const char* msg)
{
    g_SMAPI->ConPrint(msg);
}

void PluginApi::ConPrintf(const char* fmt, ...)
{
    va_list ap;
    char buffer[2048];

    va_start(ap, fmt);
    FormatArgs(buffer, sizeof(buffer), fmt, ap);
    va_end(ap);

    g_SMAPI->ConPrint(buffer);
}

void PluginApi::AddListener(IToolkitPlugin *plugin, IToolkitListener *pListener)
{
    pluginManager.AddListener(plugin, pListener);
}

void* PluginApi::QueryInterface(CreateInterfaceFn fn, const char *iface, int min)
{
    char buffer[256];	/* assume no interface will go beyond this */
    size_t len = strlen(iface);
    int ret;			/* just in case something doesn't handle NULL properly */

    if (len > sizeof(buffer) - 4)
    {
        return NULL;
    }

    strcpy(buffer, iface);

    if (min != -1)
    {
        char *ptr = &buffer[len - 1];
        int digits = 0;
        while (isdigit(*ptr) && digits <=3)
        {
            *ptr = '\0';
            digits++;
            ptr--;
        }
        if (digits != 3)
        {
            /* for now, assume this is an error */
            strcpy(buffer, iface);
        }
        else
        {
            char num[4];
            min = (min == 0) ? 1 : min;
            snprintf(num, sizeof(num), "%03d", min);
            strcat(buffer, num);
        }
    }

    return InterfaceSearch(fn, buffer, IFACE_MAXNUM, &ret);
}

void* PluginApi::InterfaceSearch(CreateInterfaceFn fn, const char* iface, int max, int* ret)
{
    char _if[256];	/* assume no interface goes beyond this */
    size_t len = strlen(iface);
    int num = 0;
    void *pf = NULL;

    if (max > 999)
    {
        max = 999;
    }

    if (len + 4 > sizeof(_if))
    {
        if (ret)
        {
            *ret = META_IFACE_FAILED;
        }
        return NULL;
    }

    strcpy(_if, iface);

    do
    {
        if ((pf = (fn)(_if, ret)) != NULL)
        {
            break;
        }
        if (num > max)
        {
            break;
        }
    } while ((num = FormatIface(_if, len+1)));

    return pf;
}

int PluginApi::FormatIface(char iface[], size_t maxlength)
{
    size_t length = strlen(iface);
    size_t i;
    int num = 0;

    for (i = length - 1; i + 1 > 0; i--)
    {
        if (!isdigit(iface[i]))
        {
            if (i != length - 1)
            {
                num = 1;
            }
            break;
        }
    }

    if ( (num && (maxlength <= length)) || (!num && (maxlength <= length + 3)) )
    {
        return -1;
    }

    if (i != length - 1)
    {
        num = atoi(&(iface[++i]));
    }

    num++;

    snprintf(&(iface[i]), 4, "%03d", num);

    return num;
}

CreateInterfaceFn PluginApi::GetEngineFactory(bool syn/* =true */)
{
    return g_SMAPI->GetEngineFactory(syn);
}

CreateInterfaceFn PluginApi::GetPhysicsFactory(bool syn/* =true */)
{
    return g_SMAPI->GetPhysicsFactory(syn);
}

CreateInterfaceFn PluginApi::GetFileSystemFactory(bool syn/* =true */)
{
    return g_SMAPI->GetFileSystemFactory(syn);
}

CreateInterfaceFn PluginApi::GetServerFactory(bool syn/* =true */)
{
    return g_SMAPI->GetServerFactory(syn);
}

void* PluginApi::ToolkitFactory(const char *iface, int *ret, PluginId *id)
{
    for (auto& p : pluginManager.m_plugins)
    {
        for (auto* l : p->listeners)
        {
            if (auto res = l->OnToolkitQuery(iface, ret))
            {
                if (id) *id = p->id;
                return res;
            }
        }
    }

    if (ret) *ret = TOOLKIT_IFACE_FAILED;
    return nullptr;
}

void* PluginApi::MetaFactory(const char *iface, int *ret, PluginId *id)
{
    return g_SMAPI->MetaFactory(iface, ret, id);
}

IToolkitAddresses* PluginApi::Addresses()
{
    return &addresses::toolkitAddresses;
}

IToolkitCommands* PluginApi::Commands()
{
    return &commands::commandsManager;
}

IToolkitConVars* PluginApi::ConVars()
{
    return &convars::convarsManager;
}

IToolkitEntities* PluginApi::Entities()
{
    return &entities::entitiesManager;
}

IToolkitEvents* PluginApi::Events()
{
    return &events::eventManager;
}

IToolkitGameConfig* PluginApi::GameConfig()
{
    return shared::g_pGameConfig;
}

IToolkitMenus* PluginApi::Menus()
{
    return &menus::menuManager;
}

IToolkitMySQL* PluginApi::MySQL()
{
    return &mysql::mysqlManager;
}

IToolkitScheduler* PluginApi::Scheduler()
{
    return &toolkitScheduler;
}

IToolkitTrace* PluginApi::Trace()
{
    return &raytrace::rayTrace;
}

IGameEventManager2* PluginApi::GetGameEventManager()
{
    return shared::g_pGameEventManager;
}

CGlobalVars* PluginApi::GetGlobalVars()
{
    return shared::getGlobalVars();
}

ICvar* PluginApi::GetCVar()
{
    return shared::g_pCVar;
}

ISource2Server* PluginApi::GetSource2Server()
{
    return shared::g_pServer;
}

IVEngineServer* PluginApi::GetEngineServer()
{
    return shared::g_pEngine;
}

IGameEventSystem* PluginApi::GetGameEventSystem()
{
    return shared::g_pGameEventSystem;
}

INetworkMessages* PluginApi::GetNetworkMessages()
{
    return shared::g_pNetworkMessages;
}

INetworkServerService* PluginApi::GetNetworkServerService()
{
    return shared::g_pNetworkServerService;
}

CGameEntitySystem* PluginApi::GetEntitySystem()
{
    return shared::g_pEntitySystem;
}

CSchemaSystem* PluginApi::GetSchemaSystem()
{
    return shared::g_pSchemaSystem;
}

const char* PluginApi::GetBaseDir()
{
    return g_SMAPI->GetBaseDir();
}

size_t PluginApi::Format(char *buffer, size_t maxlength, const char *format, ...)
{
    va_list ap;
    size_t result;

    va_start(ap, format);
    result = FormatArgs(buffer, maxlength, format, ap);
    va_end(ap);

    return result;
}

size_t PluginApi::FormatArgs(char *buffer, size_t maxlength, const char *format, va_list ap)
{
    return g_SMAPI->FormatArgs(buffer, maxlength, format, ap);
}