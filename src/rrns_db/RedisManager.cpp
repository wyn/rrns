#include "RedisManager.h"
#include "ICredisConsumer.h"
#include "glog/logging.h"

using namespace rrns_db;

RedisManager::RedisManager(ICredisConsumer *consumer)
    : cons(CHECK_NOTNULL(consumer))
{
    DLOG(INFO) << "RedisManager(), reset to initial";
    cons->Init();
}

void RedisManager::Connect(const std::string &host, int port, int timeout)
{
    DLOG(INFO) << "Trying to get REDIS handle on " << host << ", " << port;
    dbHandle = cons->GetHandle(host, port, timeout);

    CHECK_NOTNULL(dbHandle);
}

void RedisManager::Disconnect()
{
    DLOG(INFO) << "Disconnecting";
    cons->Close(dbHandle);
}

//Register/unregister with a RN data stream
void RedisManager::Register(const std::string &major, const std::string &minor)
{
    DLOG(INFO) << "Registering, reset to " << major << ", " << minor;

    CHECK(cons->IsValidHandle(dbHandle)) << "Invalid REDIS handle";

    CHECK(cons->StreamExists(dbHandle, major, minor)) << "Unknown stream " << major << ", " << minor;

    majorType = major;
    minorType = minor;
    id = cons->GetStreamId(dbHandle, major, minor);

    DLOG(INFO) << "Set manager state " << major << ", " << minor << ", " << id;
}

void RedisManager::Unregister()
{
    DLOG(INFO) << "Unregistering, reset to initial";
    cons->Init();
}

//consuming data
bool RedisManager::CanConsume() const
{
    return false;
}

bool RedisManager::ValidHandle() const
{
    return false;
}
