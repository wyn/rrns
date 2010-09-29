#ifndef REDISMANAGER_H
#define REDISMANAGER_H

#include "IRedisManager.h"

namespace rrns_db {

    //forwards
    class ICredisConsumer;
    class ICredisConnector;

    class RedisManager : public IRedisManager
    {

    public:

        //construct/destruct
        RedisManager(ICredisConsumer *consumer, ICredisConnector *connector);
        virtual ~RedisManager();

        //Connect/disconnect with db
        virtual void Connect(const std::string &host, int port, int timeout);
        virtual void Disconnect();

        //Register/unregister with a RN data stream
        virtual void Register(const std::string &major, const std::string &minor);
        virtual void Unregister();

        //readonly class state
        virtual std::string MajorType() const;
        virtual std::string MinorType() const;

        //consuming data
        virtual bool CanConsume() const;
        virtual bool ValidHandle() const;
        virtual std::list<double> GetRandoms(int howMany) const;

    protected:
        virtual void Reset();

    private:

        //Redis stuff
        ICredisConsumer *cons;
        ICredisConnector *conn;

    private:
        //don't want these
        RedisManager(const RedisManager&);
        RedisManager& operator=(const RedisManager&);


    };

} //namespace rrns_db

#endif // REDISMANAGER_H
