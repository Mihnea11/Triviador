#pragma once
#include <string>

struct Server
{
	static std::string IP;

	static void SetIp(const std::string ip);
	static std::string GetUrl();
};
