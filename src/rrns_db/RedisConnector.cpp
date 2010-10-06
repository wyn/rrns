#include "RedisConnector.h"

using namespace rrns_db;

RedisConnector::RedisConnector()
{
}

void RedisConnector::Connect(const std::string &hostname, int port, int timeout)
{
    rh_ = credis_connect(hostname.c_str(), port, timeout);
}

bool RedisConnector::IsValidHandle() const
{
    return (0 == credis_ping(rh_));
}

REDIS RedisConnector::Handle() const
{
    return rh_;
}

void RedisConnector::Disconnect()
{
    credis_close(rh_);
}

