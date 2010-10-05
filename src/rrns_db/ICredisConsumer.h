#ifndef ICREDISCONSUMER_H
#define ICREDISCONSUMER_H

#include <string>
#include <list>

//want this interface to take care of our general Redis needs for listening to a stream of rands (using numeric types)
namespace rrns_db {

    class ICredis;

    class ICredisConsumer
    {
    public:

        virtual ~ICredisConsumer() {}

        virtual bool CanConsume(ICredis *rh, const std::string &dataKey) const = 0;

        virtual std::list<double> GetRandoms(ICredis *rh,  const std::string &dataKey, int count) const = 0;

    };

} //namespace rrns_db

#endif // ICREDISCONSUMER_H
