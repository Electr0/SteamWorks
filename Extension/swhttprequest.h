/*
    This file is part of SourcePawn SteamWorks.

    SourcePawn SteamWorks is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, as per version 3 of the License.

    SourcePawn SteamWorks is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SourcePawn SteamWorks.  If not, see <http://www.gnu.org/licenses/>.
	
	Author: Kyle Sanderson (KyleS).
*/

#pragma once
#include "isteamgameserver.h"
#include "steam_gameserver.h"
#include "smsdk_ext.h"

#if STEAMHTTP_INTERFACE_VERSION == "STEAMHTTP_INTERFACE_VERSION001"
struct HTTPRequestHeadersReceived_t
{
	enum { k_iCallback = k_iSteamHTTPCallbacks + 2 };

	// Handle value for the request that has received headers.
	HTTPRequestHandle m_hRequest;

	// Context value that the user defined on the request that this callback is associated with, 0 if
	// no context value was set.
	uint64 m_ulContextValue;
};

struct HTTPRequestDataReceived_t
{
	enum { k_iCallback = k_iSteamHTTPCallbacks + 3 };

	// Handle value for the request that has received data.
	HTTPRequestHandle m_hRequest;

	// Context value that the user defined on the request that this callback is associated with, 0 if
	// no context value was set.
	uint64 m_ulContextValue;


	// Offset to provide to GetHTTPStreamingResponseBodyData to get this chunk of data
	uint32 m_cOffset;

	// Size to provide to GetHTTPStreamingResponseBodyData to get this chunk of data
	uint32 m_cBytesReceived;
};
#endif

class SteamWorksHTTPRequest
{
	public:
		SteamWorksHTTPRequest();
		~SteamWorksHTTPRequest();

	public:
		HTTPRequestHandle request;
		Handle_t handle;

	public:
		void OnHTTPRequestCompleted(HTTPRequestCompleted_t *pRequest, bool bFailed);
		void OnHTTPHeadersReceived(HTTPRequestHeadersReceived_t *pRequest, bool bFailed);
		void OnHTTPDataReceived(HTTPRequestDataReceived_t *pRequest, bool bFailed);

	public:
		CCallResult<SteamWorksHTTPRequest, HTTPRequestCompleted_t> CompletedCallResult;
		CCallResult<SteamWorksHTTPRequest, HTTPRequestHeadersReceived_t> HeadersCallResult;
		CCallResult<SteamWorksHTTPRequest, HTTPRequestDataReceived_t> DataCallResult;

	public:
		IChangeableForward *pCompletedForward;
		IChangeableForward *pHeadersReceivedForward;
		IChangeableForward *pDataReceivedForward;
};

class SteamWorksHTTPNatives
{
	public:
		SteamWorksHTTPNatives();
		~SteamWorksHTTPNatives();
};

#include "extension.h"