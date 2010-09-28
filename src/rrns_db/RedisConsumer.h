#ifndef RedisConsumer_H
#define RedisConsumer_H

#include <QtCore>
#include "credis.h"

namespace rrns_db {

    class RedisConsumer {

    public:

        RedisConsumer();
        RedisConsumer(const QString &hostname, int port, int timeout);
        virtual ~RedisConsumer();

        //Register/unregister with a RN data stream
        bool Register(const QString &major, const QString &minor);
        bool Unregister();

        //readonly class state
        QString MajorType() const {return majorType;}
        QString MinorType() const {return minorType;}
        int Seed() const {return seed;}
        int Id() const {return id;}

        //consuming data
        bool CanConsume() const;
        bool ValidHandle() const;

    private:

        //Redis stuff
        REDIS dbHandle;

        //useful state for random number server
        QString majorType;
        QString minorType;
        int seed;
        int id;

    private:
        //don't want these
        RedisConsumer(const RedisConsumer&);
        RedisConsumer& operator=(const RedisConsumer&);


    };

} //rrns_db

#endif // RedisConsumer_H
