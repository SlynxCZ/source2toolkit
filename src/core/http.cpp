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
#include "http.h"

#include "utils/log.h"

namespace http
{
    HTTPManager httpManager;

    namespace
    {
        /// Steam's HTTP client, or nullptr until the API activates.
        ISteamHTTP* s_pSteamHTTP = nullptr;

        EHTTPMethod ToSteamMethod(EToolkitHTTPMethod method)
        {
            switch (method)
            {
                case EToolkitHTTPMethod::Post:   return k_EHTTPMethodPOST;
                case EToolkitHTTPMethod::Put:    return k_EHTTPMethodPUT;
                case EToolkitHTTPMethod::Patch:  return k_EHTTPMethodPATCH;
                case EToolkitHTTPMethod::Delete: return k_EHTTPMethodDELETE;
                case EToolkitHTTPMethod::Head:   return k_EHTTPMethodHEAD;
                case EToolkitHTTPMethod::Get:
                default:                         return k_EHTTPMethodGET;
            }
        }
    }

    /* =========================
    TrackedRequest
    ========================= */

    HTTPManager::TrackedRequest::TrackedRequest(HTTPRequestHandle hRequest, SteamAPICall_t hCall,
                                                ToolkitHTTPCallback callback)
        : m_hRequest(hRequest), m_Callback(std::move(callback))
    {
        m_CallResult.Set(hCall, this, &TrackedRequest::OnCompleted);
    }

    void HTTPManager::TrackedRequest::OnCompleted(HTTPRequestCompleted_t* pResult, bool bIOFailure)
    {
        ToolkitHTTPResponse response;
        response.m_bSuccess = !bIOFailure && pResult && pResult->m_bRequestSuccessful;

        if (pResult)
            response.m_nStatusCode = static_cast<int>(pResult->m_eStatusCode);

        if (response.m_bSuccess && s_pSteamHTTP)
        {
            uint32 nSize = 0;
            s_pSteamHTTP->GetHTTPResponseBodySize(m_hRequest, &nSize);

            if (nSize > 0)
            {
                response.m_sBody.resize(nSize);
                s_pSteamHTTP->GetHTTPResponseBodyData(
                    m_hRequest, reinterpret_cast<uint8*>(response.m_sBody.data()), nSize);
            }
        }

        if (m_Callback)
            m_Callback(response);

        if (s_pSteamHTTP)
            s_pSteamHTTP->ReleaseHTTPRequest(m_hRequest);

        // Ran to completion; nothing else refers to this.
        delete this;
    }

    /* =========================
    Sending
    ========================= */

    void HTTPManager::Send(EToolkitHTTPMethod method, const char* pszUrl, const char* pszBody,
                           bool bHasBody, ToolkitHTTPCallback callback,
                           const std::vector<ToolkitHTTPHeader>* pHeaders)
    {
        HTTPRequestHandle hRequest = s_pSteamHTTP->CreateHTTPRequest(ToSteamMethod(method), pszUrl);

        if (hRequest == INVALID_HTTPREQUEST_HANDLE)
        {
            FP_ERROR("Failed to create an HTTP request for '{}'", pszUrl);

            if (callback)
                callback(ToolkitHTTPResponse{});

            return;
        }

        if (pHeaders)
        {
            for (const auto& header : *pHeaders)
                s_pSteamHTTP->SetHTTPRequestHeaderValue(hRequest, header.m_sName.c_str(), header.m_sValue.c_str());
        }

        if (bHasBody && pszBody)
        {
            s_pSteamHTTP->SetHTTPRequestRawPostBody(
                hRequest, "application/json",
                reinterpret_cast<uint8*>(const_cast<char*>(pszBody)),
                static_cast<uint32>(strlen(pszBody)));
        }

        SteamAPICall_t hCall = k_uAPICallInvalid;

        if (!s_pSteamHTTP->SendHTTPRequest(hRequest, &hCall))
        {
            FP_ERROR("Failed to send an HTTP request to '{}'", pszUrl);
            s_pSteamHTTP->ReleaseHTTPRequest(hRequest);

            if (callback)
                callback(ToolkitHTTPResponse{});

            return;
        }

        // Deletes itself once the call lands.
        new TrackedRequest(hRequest, hCall, std::move(callback));
    }

    void HTTPManager::Request(EToolkitHTTPMethod method, const char* pszUrl, const char* pszBody,
                              ToolkitHTTPCallback callback,
                              const std::vector<ToolkitHTTPHeader>* pHeaders)
    {
        if (!pszUrl)
            return;

        if (!s_pSteamHTTP)
        {
            // Steam has not handed its client over yet -- hold on to this and
            // send it from OnSteamAPIActivated().
            QueuedRequest queued;
            queued.method = method;
            queued.url = pszUrl;
            queued.hasBody = pszBody != nullptr;
            queued.body = pszBody ? pszBody : "";
            queued.callback = std::move(callback);

            if (pHeaders)
                queued.headers = *pHeaders;

            m_QueuedRequests.push_back(std::move(queued));
            return;
        }

        Send(method, pszUrl, pszBody, pszBody != nullptr, std::move(callback), pHeaders);
    }

    void HTTPManager::Get(const char* pszUrl, ToolkitHTTPCallback callback,
                          const std::vector<ToolkitHTTPHeader>* pHeaders)
    {
        Request(EToolkitHTTPMethod::Get, pszUrl, nullptr, std::move(callback), pHeaders);
    }

    void HTTPManager::Post(const char* pszUrl, const char* pszBody, ToolkitHTTPCallback callback,
                           const std::vector<ToolkitHTTPHeader>* pHeaders)
    {
        Request(EToolkitHTTPMethod::Post, pszUrl, pszBody, std::move(callback), pHeaders);
    }

    void HTTPManager::Put(const char* pszUrl, const char* pszBody, ToolkitHTTPCallback callback,
                          const std::vector<ToolkitHTTPHeader>* pHeaders)
    {
        Request(EToolkitHTTPMethod::Put, pszUrl, pszBody, std::move(callback), pHeaders);
    }

    void HTTPManager::Patch(const char* pszUrl, const char* pszBody, ToolkitHTTPCallback callback,
                            const std::vector<ToolkitHTTPHeader>* pHeaders)
    {
        Request(EToolkitHTTPMethod::Patch, pszUrl, pszBody, std::move(callback), pHeaders);
    }

    void HTTPManager::Delete(const char* pszUrl, const char* pszBody, ToolkitHTTPCallback callback,
                             const std::vector<ToolkitHTTPHeader>* pHeaders)
    {
        Request(EToolkitHTTPMethod::Delete, pszUrl, pszBody, std::move(callback), pHeaders);
    }

    /* =========================
    Lifecycle
    ========================= */

    bool HTTPManager::IsAvailable() const { return s_pSteamHTTP != nullptr; }

    int HTTPManager::PendingCount() const { return static_cast<int>(m_QueuedRequests.size()); }

    void HTTPManager::OnSteamAPIActivated()
    {
        s_pSteamHTTP = SteamGameServerHTTP();

        if (!s_pSteamHTTP)
        {
            FP_ERROR("Steam API activated but its HTTP client is unavailable.");
            return;
        }

        if (m_QueuedRequests.empty())
            return;

        FP_INFO("Steam HTTP available, sending {} queued request(s).", m_QueuedRequests.size());

        // Moved out first: a callback firing synchronously on a send failure is
        // free to queue another request.
        std::vector<QueuedRequest> queued;
        queued.swap(m_QueuedRequests);

        for (auto& request : queued)
        {
            Send(request.method, request.url.c_str(),
                 request.hasBody ? request.body.c_str() : nullptr, request.hasBody,
                 std::move(request.callback), &request.headers);
        }
    }

    void HTTPManager::OnSteamAPIDeactivated()
    {
        s_pSteamHTTP = nullptr;
    }

    void HTTPManager::Shutdown()
    {
        m_QueuedRequests.clear();
        s_pSteamHTTP = nullptr;
    }
}
