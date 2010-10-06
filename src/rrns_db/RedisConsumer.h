#ifndef RedisConsumer_H
#define RedisConsumer_H

#include "IRedisConsumer.h"

namespace rrns_db
{

    class RedisConsumer : public IRedisConsumer
    {

    public:

        RedisConsumer();

        virtual bool CanConsume(ICredis *rh, const std::string &dataKey) const;

        virtual std::vector<double> GetRandoms(ICredis *rh,  const std::string &dataKey, int count) const;

    private:
        //don't want these
        RedisConsumer(const RedisConsumer&);
        RedisConsumer& operator=(const RedisConsumer&);

    };

} //rrns_db

#endif // RedisConsumer_H
