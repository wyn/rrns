#ifndef REDISMANAGER_H
#define REDISMANAGER_H

#include "IRedisManager.h"

namespace rrns_db {

    //forwards
    class ICredis;
    class ICredisConsumer;
    class ICredisConnector;
    class IKeyParser;

    class RedisManager : public IRedisManager
    {

    public:

        //construct/destruct
        RedisManager(ICredis *credis, ICredisConsumer *consumer, ICredisConnector *connector, IKeyParser *parser);

        //Connect/disconnect with db
        virtual void Connect(const std::string &host, int port, int timeout);
        virtual void Disconnect();

        //Register/unregister with a RN data stream
        virtual void Register(const std::string &majorKey, const std::string &minorKey);
        virtual void Unregister();

        //consuming data
        virtual bool CanConsume() const;
        virtual std::list<double> GetRandoms(int howMany) const;

    private:

        //Redis stuff
        ICredis             *cred;
        ICredisConsumer     *cons;
        ICredisConnector    *conn;
        IKeyParser          *pars;
        std::string         id;

    private:
        //don't want these
        RedisManager(const RedisManager&);
        RedisManager& operator=(const RedisManager&);

    };

} //namespace rrns_db

#endif // REDISMANAGER_H
