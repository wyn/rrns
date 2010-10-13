#include "Consumer.h"
#include "glog/logging.h"
#include "ICredis.h"
#include "IRedisConnector.h"

#include <sstream>

using namespace rrns_db;

const int Consumer::default_max = 100;
const int Consumer::default_max_factor = 3;

Consumer::Consumer()
{
}

bool Consumer::CanConsume(const ICredis *rh, const std::string &dataKey) const
{
    CHECK_NOTNULL(rh);
    DLOG(INFO) << "CanConsume";

    return (0 == rh->exists(dataKey.c_str()));
}

int Consumer::Count(const ICredis *rh, const std::string &dataKey) const
{
    CHECK_NOTNULL(rh);
    DLOG(INFO) << "Count";

    return rh->llen(dataKey.c_str());
}

std::vector<double> Consumer::GetData(const ICredis *rh, const std::string &dataKey, int count) const
{
    CHECK_NOTNULL(rh);
    DLOG(INFO) << "GetRandoms";

    //get count x rands for id member
    std::vector<double> l;
    l.reserve(count);
    const int max_try = std::max(default_max, count*default_max_factor);
    int i = 0; //for counting how many successful pops we do
    int j = 0; //for counting up to a max_try before giving up
    char* el;
    const char* key = dataKey.c_str();
    while (i != count)
    {
        if (max_try < j++)
        {
            LOG(ERROR) << "Reached maximum " << max_try << " tries for " << dataKey;
            LOG(ERROR) << "Giving up and returning result so far";
            break;
        }

        if (0 == rh->lpop(key, &el))
        {
            l.push_back(strtod(el, NULL));
            i++;
        }
    }

    return l;
}
