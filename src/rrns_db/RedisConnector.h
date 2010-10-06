#ifndef REDISCONNECTOR_H
#define REDISCONNECTOR_H

#include "IRedisConnector.h"

namespace rrns_db
{
    class RedisConnector : public IRedisConnector
    {
    public:
        RedisConnector();

        virtual void Connect(const std::string &hostname, int port, int timeout);

        virtual bool IsValidHandle() const;

        virtual REDIS Handle() const;

        virtual void Disconnect();

    private:

        REDIS rh_;

    };

} //namespace rrns_db

#endif // REDISCONNECTOR_H
