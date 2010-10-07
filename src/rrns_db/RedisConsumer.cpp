#include "RedisConsumer.h"
#include "glog/logging.h"
#include "ICredis.h"
#include "IRedisConnector.h"

#include <sstream>

using namespace rrns_db;

const int RedisConsumer::default_max = 100;
const int RedisConsumer::default_max_factor = 3;

RedisConsumer::RedisConsumer()
{
}

bool RedisConsumer::CanConsume(const ICredis *rh, const std::string &dataKey) const
{
    CHECK_NOTNULL(rh);
    DLOG(INFO) << "CanConsume";

    return (0 == rh->exists(dataKey.c_str()));
}

std::vector<double> RedisConsumer::GetRandoms(const ICredis *rh, const std::string &dataKey, int count) const
{
    CHECK_NOTNULL(rh);
    DLOG(INFO) << "GetRandoms";

    if (!CanConsume(rh, dataKey))
    {
        DLOG(ERROR) << "Cannot consume data for " << dataKey;
        return std::vector<double>();
    }

    //get count x rands for id member
    std::vector<double> l;
    l.reserve(count);
    const int max_try = std::max(default_max, count*default_max_factor);
    int i = 0; //for counting how many successful pops we do
    int j = 0; //for counting up to a max_try before giving up
    char* el;
    while (i != count)
    {
        if (max_try < j++)
        {
            LOG(ERROR) << "Reached maximum " << max_try << " tries for " << dataKey;
            LOG(ERROR) << "Giving up and returning result so far";
            break;
        }

        if (0 == rh->lpop(dataKey.c_str(), &el))
        {
            l.push_back(strtod(el, NULL));
            i++;
        }
    }

    return l;
}
