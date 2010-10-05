#include "RedisManager.h"
#include "ICredis.h"
#include "ICredisConsumer.h"
#include "ICredisConnector.h"
#include "IKeyParser.h"
#include "IKey.h"

#include "glog/logging.h"

using namespace rrns_db;

static const std::string unknown_id("unknown");

static std::string MakeTemporaryKeyString(const std::string &major, const std::string &minor)
{
    //timestamp the key too to make unique
    return ("tmp:" + major + ":intersect:" + minor);
}

class ScopedTemporaryKey
{

public:

    ScopedTemporaryKey(const char *key, ICredis *credis)
        : key_(CHECK_NOTNULL(key))
        , credis_(CHECK_NOTNULL(credis))
    {
        DLOG(INFO) << "Scoping the key " << key_ << " for a set type";
        if (0 != credis_->sadd(key_, NULL))
            DLOG(ERROR) << "Could not create temp key " << key_;
    }

    virtual ~ScopedTemporaryKey()
    {
        //no throw here
        if (0 != credis_->del(key_))
            DLOG(ERROR) << "Could not delete temp key " << key_;
    }

    const char* Key() const { return key_; }

    bool Exists() const { return credis_->exists(key_); }

private:
    const char *key_;
    ICredis *credis_;

};

RedisManager::RedisManager(ICredis *credis, ICredisConsumer *consumer, ICredisConnector *connector, IKeyParser *parser)
    : cred(CHECK_NOTNULL(credis))
    , cons(CHECK_NOTNULL(consumer))
    , conn(CHECK_NOTNULL(connector))
    , pars(CHECK_NOTNULL(parser))
    , id(unknown_id)
{
    DLOG(INFO) << "RedisManager(), reset to initial";
}

void RedisManager::Connect(const std::string &host, int port, int timeout)
{
    DLOG(INFO) << "Trying to get REDIS handle on " << host << ", " << port;
    conn->Connect(host, port, timeout);
    cred->SetConnector(conn);
}

void RedisManager::Disconnect()
{
    DLOG(INFO) << "Disconnecting";
    cred->ClearConnector();
    conn->Disconnect();
}

//Register/unregister with a RN data stream
void RedisManager::Register(const std::string &majorKey, const std::string &minorKey)
{
    DLOG(INFO) << "Registering " << majorKey << ", " << minorKey;

    if (!conn->IsValidHandle())
    {
        DLOG(ERROR) << "Cannot get REDIS handle, quitting registration";
        return;
    }

    //make temporary key for storage of intersection op, will delete when out of scope
    ScopedTemporaryKey k(MakeTemporaryKeyString(majorKey, minorKey).c_str(), cred);
    if (!k.Exists())
    {
        DLOG(ERROR) << "Cannot create temporary key";
        return;
    }

    //do intersection op
    const char* keys[] = { majorKey.c_str(), minorKey.c_str() };
    if (0 >= cred->sinterstore(k.Key(), 2, keys)) //think it returns the number of elements found in intersect
    {
        DLOG(ERROR) << "Intersection is empty";
        return;
    }

    //pop off a random id key
    char *c;
    if (0 != cred->spop(k.Key(), &c))
    {
        DLOG(ERROR) << "Could not aquire id for " << k.Key();
        return;
    }

    //serialise to full id/data key string and store in id
    RedisKey idKey;
    idKey.SetFamily(std::string(c));
    if (!pars->Serialise(&idKey, id))
    {
        DLOG(ERROR) << "Unable to serialise key: " << idKey.Family() << ", " << idKey.Member() << ", " << idKey.Entity();
        return;
    }
}

void RedisManager::Unregister()
{
    DLOG(INFO) << "Unregistering, reset to initial";
    id = unknown_id;
}

bool RedisManager::CanConsume() const
{    
    return cons->CanConsume(cred, id);
}

std::list<double> RedisManager::GetRandoms(int howMany) const
{
    return cons->GetRandoms(cred, id, howMany);
}
