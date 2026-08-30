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
#pragma once
#include "source2toolkit/IToolkitHTTP.h"

#include "steam/steam_gameserver.h"

#include <vector>

namespace http {
    class HTTPManager final : public IToolkitHTTP {
    public:
        bool IsAvailable() const override;
        int PendingCount() const override;

        void Request(EToolkitHTTPMethod method, const char* pszUrl, const char* pszBody,
                     ToolkitHTTPCallback callback,
                     const std::vector<ToolkitHTTPHeader>* pHeaders) override;

        void Get(const char* pszUrl, ToolkitHTTPCallback callback,
                 const std::vector<ToolkitHTTPHeader>* pHeaders) override;
        void Post(const char* pszUrl, const char* pszBody, ToolkitHTTPCallback callback,
                  const std::vector<ToolkitHTTPHeader>* pHeaders) override;
        void Put(const char* pszUrl, const char* pszBody, ToolkitHTTPCallback callback,
                 const std::vector<ToolkitHTTPHeader>* pHeaders) override;
        void Patch(const char* pszUrl, const char* pszBody, ToolkitHTTPCallback callback,
                   const std::vector<ToolkitHTTPHeader>* pHeaders) override;
        void Delete(const char* pszUrl, const char* pszBody, ToolkitHTTPCallback callback,
                    const std::vector<ToolkitHTTPHeader>* pHeaders) override;

    public:
        /// Steam handed its HTTP client over -- sends whatever was queued while
        /// it was not there yet. Driven by the ISource2Server vtable hook.
        void OnSteamAPIActivated();

        /// Steam took it away again; queue from here on.
        void OnSteamAPIDeactivated();

        /// Drops every in-flight and queued request. Called on unload -- a
        /// callback is a std::function holding code inside a plugin's library.
        void Shutdown();

    private:
        /// One request Steam is already working on. Owns its own call result,
        /// so it has to outlive the call and delete itself when it lands.
        class TrackedRequest {
        public:
            TrackedRequest(HTTPRequestHandle hRequest, SteamAPICall_t hCall, ToolkitHTTPCallback callback);
            TrackedRequest(const TrackedRequest&) = delete;
            TrackedRequest& operator=(const TrackedRequest&) = delete;

        private:
            void OnCompleted(HTTPRequestCompleted_t* pResult, bool bIOFailure);

            HTTPRequestHandle m_hRequest;
            CCallResult<TrackedRequest, HTTPRequestCompleted_t> m_CallResult;
            ToolkitHTTPCallback m_Callback;
        };

        struct QueuedRequest {
            EToolkitHTTPMethod method;
            std::string url;
            std::string body;
            bool hasBody = false;
            ToolkitHTTPCallback callback;
            std::vector<ToolkitHTTPHeader> headers;
        };

        void Send(EToolkitHTTPMethod method, const char* pszUrl, const char* pszBody, bool bHasBody,
                  ToolkitHTTPCallback callback, const std::vector<ToolkitHTTPHeader>* pHeaders);

        std::vector<QueuedRequest> m_QueuedRequests;
    };

    extern HTTPManager httpManager;
}
