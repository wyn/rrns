#ifndef REDISCONSUMER_H
#define REDISCONSUMER_H

#include "IRedisConsumer.h"

namespace rrns_db
{

    class RedisConsumer : public IRedisConsumer
    {

    public:

        RedisConsumer();

        virtual bool CanConsume(const ICredis *rh, const std::string &dataKey) const;

        virtual int Count(const ICredis *rh, const std::string &dataKey) const;

        virtual std::vector<double> GetData(const ICredis *rh,  const std::string &dataKey, int count) const;

    private:
        static const int default_max;
        static const int default_max_factor;

    private:
        //don't want these
        RedisConsumer(const RedisConsumer&);
        RedisConsumer& operator=(const RedisConsumer&);

    };

} //rrns_db

#endif // REDISCONSUMER_H
