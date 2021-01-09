#include "StdAfx.h"

#define CURL_STATICLIB
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

#ifndef VERCHECK_H
#define VERCHECK_H

namespace Nexus
{
	class VersionCheck
	{
	public:
		static size_t ReceivedData(void *ptr, size_t size, size_t nmemb, void *data);
		static void CheckForUpdates();
	};
}

#endif