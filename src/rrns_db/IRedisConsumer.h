#ifndef IREDISCONSUMER_H
#define IREDISCONSUMER_H

#include <string>
#include <vector>

//want this interface to take care of our general Redis needs for listening to a stream of data (using numeric types)
namespace rrns_db {

    class ICredis;

    class IRedisConsumer
    {
    public:

        virtual ~IRedisConsumer() {}

        virtual bool CanConsume(const ICredis *rh, const std::string &dataKey) const = 0;

        virtual int Count(const ICredis *rh, const std::string &dataKey) const = 0;

        virtual std::vector<double> GetData(const ICredis *rh,  const std::string &dataKey, int count) const = 0;

    };

} //namespace rrns_db

#endif // IREDISCONSUMER_H
