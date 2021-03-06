#ifndef IRANDOMCONSUMER_H
#define IRANDOMCONSUMER_H

#include <string>
#include <vector>

namespace rrns_db {

    class IRandomConsumer
    {

    public:

        virtual ~IRandomConsumer() {} //for mocking

        //Connect/disconnect with db
        virtual void Connect(const std::string &host, int port, int timeout) = 0;
        virtual void Disconnect() = 0;

        //Register/unregister with a RN data stream
        virtual void Register(const std::string &majorKey, const std::string &minorKey) = 0;
        virtual void Unregister() = 0;

        //consuming data
        virtual bool CanConsume() const = 0;
        virtual int Count() const = 0;
        virtual std::vector<double> GetRandoms(int howMany) const = 0;

    };

} //namespace rrns_db

#endif // IRANDOMCONSUMER_H
