#ifndef ICREDISCONSUMER_H
#define ICREDISCONSUMER_H

#include "credis.h"
#include <string>
#include <list>

//want this interface to take care of our general Redis needs for listening to a stream of rands (using numeric types)
namespace rrns_db {

    class ICredisConnector;

    class ICredisConsumer
    {
    public:

        virtual ~ICredisConsumer() {}

        virtual void RegisterConnection(ICredisConnector *conn) = 0;

        virtual bool StreamExists(const std::string &major, const std::string &minor) const = 0 ;

        virtual void RegisterStream(const std::string &major, const std::string &minor) = 0;

        virtual bool CanConsume() const = 0;

        virtual std::list<double> GetRandoms(int count) const = 0;

        virtual void Reset() = 0;

        virtual std::string MajorType() const = 0;

        virtual std::string MinorType() const = 0;
    };

} //namespace rrns_db

#endif // ICREDISCONSUMER_H
