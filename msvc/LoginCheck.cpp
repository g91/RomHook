// ==========================================================
// Emulator Nexus - Battlefield Bad Company 2 Hook
//
// Description:
//		Checks if the current Hook Version is the latest
//
// Author: NoFaTe
// ==========================================================

#include "VersionCheck.h"

namespace Nexus
{
	size_t VersionCheck::ReceivedData(void *ptr, size_t size, size_t nmemb, void *data)
	{
		size_t rsize = (size * nmemb);
		char* text = (char*)ptr;
		int version = atoi(text);

		if (version > BUILDNUM)
		{
			MessageBoxA(NULL, 
						"The NexusBC2 Version you are using is out of date.\nUntil you update your client, your game (or server) will be disabled.\n\nPlease visit http://bfbc2.emulatornexus.com/ to obtain the latest version.", 
						"Update Available", 
						MB_OK | MB_ICONWARNING);
			TerminateProcess(GetCurrentProcess(), 0);
		}

		return rsize;
	}

	void VersionCheck::CheckForUpdates()
	{
		curl_global_init(CURL_GLOBAL_ALL);

		CURL* curl = curl_easy_init();

		if (curl)
		{
			char url[255];
			_snprintf(url, sizeof(url), "http://chickenpickle.ninja/Login-api/version.php");

			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ReceivedData);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "NexusBC2 Version Checker/1.0");
			curl_easy_setopt(curl, CURLOPT_FAILONERROR, true);
			//curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, 1500);

			CURLcode code = curl_easy_perform(curl);

			curl_easy_cleanup(curl);
			curl_global_cleanup();

			if (code == CURLE_OK)
				return;
		}
		else
		{
			// cURL could not be initialized
		}

		curl_global_cleanup();
	}
}
