#include "RedisManager.h"
#include "ICredis.h"
#include "IRedisConsumer.h"
#include "IRedisConnector.h"
#include "IKeyParser.h"
#include "IKey.h"
#include "IKeyGenerator.h"
#include "ScopedTemporaryKey.h"

#include "glog/logging.h"

using namespace rrns_db;

static std::string MakeTemporaryKeyString(const std::string &major, const std::string &minor)
{
    //timestamp the key too to make unique
    return ("tmp:" + major + ":intersect:" + minor);
}

const std::string RedisManager::unknown_id("unknown");

RedisManager::RedisManager(ICredis *credis,
                           IRedisConnector *connector,
                           const IRedisConsumer *consumer,
                           const IKeyParser *parser,
                           const IKeyGenerator *dataKeyGenerator)
    : id_(unknown_id)
    , credis_(CHECK_NOTNULL(credis))
    , connector_(CHECK_NOTNULL(connector))
    , consumer_(CHECK_NOTNULL(consumer))
    , parser_(CHECK_NOTNULL(parser))
    , dataKeyGenerator_(CHECK_NOTNULL(dataKeyGenerator))
{
    DLOG(INFO) << "RedisManager(), reset to initial";
}

void RedisManager::Connect(const std::string &host, int port, int timeout)
{
    DLOG(INFO) << "Trying to get REDIS handle on " << host << ", " << port;
    connector_->Connect(host, port, timeout);
    credis_->SetConnector(connector_);
}

void RedisManager::Disconnect()
{
    DLOG(INFO) << "Disconnecting";
    credis_->ClearConnector();
    connector_->Disconnect();
}

//Register/unregister with a RN data stream
void RedisManager::Register(const std::string &majorKey, const std::string &minorKey)
{
    DLOG(INFO) << "Registering " << majorKey << ", " << minorKey;

    if (!connector_->IsValidHandle())
    {
        DLOG(ERROR) << "Cannot get REDIS handle, quitting registration";
        return;
    }

    //make temporary key for storage of intersection op, will delete when out of scope
    ScopedTemporaryKey k(MakeTemporaryKeyString(majorKey, minorKey).c_str(), credis_);
    if (!k.Exists())
    {
        DLOG(ERROR) << "Cannot create temporary key";
        return;
    }

    //do intersection op
    const char* keys[] = { majorKey.c_str(), minorKey.c_str() };
    if (0 >= credis_->sinterstore(k.Key(), 2, keys)) //think it returns the number of elements found in intersect
    {
        DLOG(ERROR) << "Intersection is empty";
        return;
    }

    //pop off a random id key
    char *c;
    if (0 != credis_->spop(k.Key(), &c))
    {
        DLOG(ERROR) << "Could not aquire id for " << k.Key();
        return;
    }

    //create the id key
    boost::shared_ptr<IKey> idKey(dataKeyGenerator_->ScalarKey(std::string(c)));
    if (!idKey)
    {
        DLOG(ERROR) << "Could not create ID key for " << c;
        return;
    }

    //serialise to full id/data key string and store in id_
    if (!parser_->Serialise(idKey.get(), id_))
    {
        DLOG(ERROR) << "Unable to serialise key: " << idKey->Family() << ", " << idKey->Member() << ", " << idKey->Entity();
        this->Unregister();
        return;
    }
}

void RedisManager::Unregister()
{
    DLOG(INFO) << "Unregistering, reset to initial";
    id_ = unknown_id;
}

bool RedisManager::CanConsume() const
{    
    return consumer_->CanConsume(credis_, id_);
}

std::vector<double> RedisManager::GetRandoms(int howMany) const
{
    return consumer_->GetRandoms(credis_, id_, howMany);
}
