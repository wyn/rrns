#ifndef ICREDISCONSUMER_H
#define ICREDISCONSUMER_H

#include "credis.h"
#include <string>
#include <list>

//want this interface to take care of our general Redis needs for listening to a stream of rands (using numeric types)
namespace rrns_db {

    class ICredisConsumer
    {
    public:

        virtual ~ICredisConsumer() {}

        virtual void Init() = 0;

        virtual REDIS GetHandle(const std::string &hostname, int port, int timeout) const = 0;

        virtual bool IsValidHandle(REDIS h) const = 0;

        virtual void Close(REDIS h) const = 0;

        virtual void Quit(REDIS h) const = 0;

        virtual bool StreamExists(REDIS h, const std::string &major, const std::string &minor) const = 0 ;

        virtual int GetStreamId(REDIS h, const std::string &major, const std::string &minor) const = 0;

        virtual std::list<double> GetRandoms(REDIS h, int id, int count) const = 0;
    };

} //namespace rrns_db

#endif // ICREDISCONSUMER_H
