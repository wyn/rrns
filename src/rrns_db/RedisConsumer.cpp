#include "RedisConsumer.h"

using namespace rrns_db;

struct RedisConnection {

    RedisConnection(const char *h, const int p, const int t)
        : host(h)
        , port(p)
        , timeout(t)
    {}

    const char *host;
    const int port;
    const int timeout;
};

static const RedisConnection defaults("localhost", 6379, 2000);

RedisConsumer::RedisConsumer()
    : dbHandle(credis_connect(defaults.host, defaults.port, defaults.timeout))
    , majorType("")
    , minorType("")
    , seed(0)
    , id(0)
{}

RedisConsumer::RedisConsumer(const QString &hostname, int port, int timeout)
    : dbHandle(credis_connect(hostname.toStdString().c_str(), port, timeout))
    , majorType("")
    , minorType("")
    , seed(0)
    , id(0)
{}

RedisConsumer::~RedisConsumer()
{
    if (dbHandle)
        credis_close(dbHandle);
}

bool RedisConsumer::Register(const QString &major, const QString &minor)
{
    if (!ValidHandle())
    {
        qDebug("No Redis connection");
        return false;
    }

    //check major and minor modes are in db
    //retrieve an id for a data stream and its seed
    majorType = major;
    minorType = minor;
    seed = 1;
    id = 1;

    return true;
}

bool RedisConsumer::Unregister()
{
    if (!ValidHandle())
    {
        qDebug("No Redis connection");
        return false;
    }

    majorType = "";
    minorType = "";
    seed = 0;
    id = 0;

    return true;
}

bool RedisConsumer::CanConsume() const
{
    //check not in unregistered state and that the db connection is still ok
    return (
            majorType.compare("") != 0 &&
            minorType.compare("") != 0 &&
            seed > 0 &&
            id > 0 &&
            ValidHandle()
            );
}

bool RedisConsumer::ValidHandle() const
{
    if (dbHandle)
        return (0 == credis_ping(dbHandle));

    return false;
}
