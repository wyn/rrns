#ifndef REDISMANAGER_H
#define REDISMANAGER_H

#include <string>
#include "credis.h"

namespace rrns_db {

    //forwards
    class ICredisConsumer;

    class RedisManager
    {

    public:
        RedisManager(ICredisConsumer *consumer);

        //Connect/disconnect with db
        void Connect(const std::string &host, int port, int timeout);
        void Disconnect();

        //Register/unregister with a RN data stream
        void Register(const std::string &major, const std::string &minor);
        void Unregister();

        //readonly class state
        std::string MajorType() const {return majorType;}
        std::string MinorType() const {return minorType;}
        int Id() const {return id;}

        //consuming data
        bool CanConsume() const;
        bool ValidHandle() const;

    private:

        //Redis stuff
        REDIS dbHandle;
        ICredisConsumer *cons;

        //useful state for random number server
        std::string majorType;
        std::string minorType;
        int id;

    private:
        //don't want these
        RedisManager(const RedisManager&);
        RedisManager& operator=(const RedisManager&);


    };

} //namespace rrns_db

#endif // REDISMANAGER_H
