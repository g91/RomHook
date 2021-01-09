#include "StdAfx.h"

#define CURL_STATICLIB
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

#ifndef LOGINCHECK_H
#define LOGINCHECK_H

namespace Nexus
{
	class LoginCheck
	{
	public:
		static size_t ReceivedData(void *ptr, size_t size, size_t nmemb, void *data);
		static void Login(char* username, char* password);
	};
}

#endif