// ==========================================================
// Emulator Nexus - Battlefield Bad Company 2 Hook
//
// Description:
//		Checks if the current Hook Version is the latest
//
// Author: NoFaTe
// ==========================================================

#include "LoginCheck.h"

namespace Nexus
{
	size_t LoginCheck::ReceivedData(void *ptr, size_t size, size_t nmemb, void *data)
	{
		size_t rsize = (size * nmemb);
		char* text = (char*)ptr;
		int version = atoi(text);

		if (version != 100){
			MessageBoxA(NULL, 
						"wrong user/password", 
						"wrong", 
						MB_OK | MB_ICONWARNING);
			TerminateProcess(GetCurrentProcess(), 0);
		}

		return rsize;
	}

	void LoginCheck::Login(char* username, char* password)
	{
		curl_global_init(CURL_GLOBAL_ALL);

		CURL* curl = curl_easy_init();

		if (curl)
		{
			char url[255];
			_snprintf(url, sizeof(url), "http://chickenpickle.ninja/Login-api/login.php?username=%s&password=%s", username, password);

			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ReceivedData);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "NexusBC2 Version Checker/1.0");
			curl_easy_setopt(curl, CURLOPT_FAILONERROR, true);

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
