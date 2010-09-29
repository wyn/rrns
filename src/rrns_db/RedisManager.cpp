#include "RedisManager.h"
#include "ICredisConsumer.h"
#include "ICredisConnector.h"
#include "glog/logging.h"

using namespace rrns_db;

RedisManager::RedisManager(ICredisConsumer *consumer, ICredisConnector *connector)
    : cons(CHECK_NOTNULL(consumer))
    , conn(CHECK_NOTNULL(connector))
{
    DLOG(INFO) << "RedisManager(), reset to initial";
    this->Reset();
}

RedisManager::~RedisManager()
{
}

void RedisManager::Connect(const std::string &host, int port, int timeout)
{
    DLOG(INFO) << "Trying to get REDIS handle on " << host << ", " << port;

    conn->Connect(host, port, timeout);
    CHECK(this->ValidHandle()) << "Invalid REDIS handle";

    cons->RegisterConnection(conn);

}

void RedisManager::Disconnect()
{
    DLOG(INFO) << "Disconnecting";
    this->Reset();
    conn->Disconnect();

}

//Register/unregister with a RN data stream
void RedisManager::Register(const std::string &major, const std::string &minor)
{
    DLOG(INFO) << "Registering " << major << ", " << minor;

    CHECK(this->ValidHandle()) << "Invalid REDIS handle";
    CHECK(cons->StreamExists(major, minor)) << "Unknown stream " << major << ", " << minor;
    cons->RegisterStream(major, minor);
    CHECK(this->CanConsume()) << "Cannot consume random data from " << major << ", " << minor;

    DLOG(INFO) << "Set manager state " << major << ", " << minor;
}

void RedisManager::Unregister()
{
    DLOG(INFO) << "Unregistering, reset to initial";
    this->Reset();
}

//consuming data
std::string RedisManager::MajorType() const
{
    return cons->MajorType();
}

std::string RedisManager::MinorType() const
{
    return cons->MinorType();
}

bool RedisManager::CanConsume() const
{
    return cons->CanConsume();
}

bool RedisManager::ValidHandle() const
{
    return conn->IsValidHandle();
}

std::list<double> RedisManager::GetRandoms(int howMany) const
{
    CHECK(this->CanConsume()) << "Cannot consume random data";
    return cons->GetRandoms(howMany);
}

void RedisManager::Reset()
{
    cons->Reset();
}
