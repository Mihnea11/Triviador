#include "Utils.h"

std::string Server::IP = "localhost";

void Server::SetIp(const std::string ip)
{
    IP = ip;
}

std::string Server::GetUrl()
{
    return "http://" + IP + ":18080";
}
