#ifndef REDISMANAGER_H
#define REDISMANAGER_H

#include "IRedisManager.h"

namespace rrns_db {

    //forwards
    class ICredis;
    class IRedisConnector;
    class IConsumer;
    class IKeyParser;
    class IKeyGenerator;

    class RedisManager : public IRedisManager
    {

    public:

        //construct/destruct
        RedisManager(ICredis *credis,
                     IRedisConnector *connector,
                     const IConsumer *consumer,
                     const IKeyParser *parser,
                     const IKeyGenerator *dataKeyGenerator);

        //Connect/disconnect with db
        virtual void Connect(const std::string &host, int port, int timeout);
        virtual void Disconnect();

        //Register/unregister with a RN data stream
        virtual void Register(const std::string &majorKey, const std::string &minorKey);
        virtual void Unregister();

        //consuming data
        virtual bool CanConsume() const;
        virtual int Count() const;
        virtual std::vector<double> GetRandoms(int howMany) const;

    private:

        static const std::string unknown_id;

        //Redis stuff
        std::string      id_;
        ICredis         *credis_;
        IRedisConnector *connector_;

        const IConsumer    *consumer_;
        const IKeyParser        *parser_;
        const IKeyGenerator     *dataKeyGenerator_;

    private:
        //don't want these
        RedisManager(const RedisManager&);
        RedisManager& operator=(const RedisManager&);

    };

} //namespace rrns_db

#endif // REDISMANAGER_H
