//
// Created by Michal Přikryl on 10.04.2026.
// Copyright (c) 2026 slynxcz. All rights reserved.
//
#include "pluginapi.h"
#include <cstring>
#include <stdarg.h>

#include "source2toolkit/IToolkitPlugin.h"

#include "plugin.h"
#include "pluginmanager.h"

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