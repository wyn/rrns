#ifndef IREDISMANAGER_H
#define IREDISMANAGER_H

#include <string>
#include <list>

namespace rrns_db {

    class IRedisManager
    {

    public:

        virtual ~IRedisManager() {} //for mocking

        //Connect/disconnect with db
        virtual void Connect(const std::string &host, int port, int timeout) = 0;
        virtual void Disconnect() = 0;

        //Register/unregister with a RN data stream
        virtual void Register(const std::string &major, const std::string &minor) = 0;
        virtual void Unregister() = 0;

        //readonly class state
        virtual std::string MajorType() const = 0;
        virtual std::string MinorType() const = 0;

        //consuming data
        virtual bool CanConsume() const = 0;
        virtual bool ValidHandle() const = 0;
        virtual std::list<double> GetRandoms(int howMany) const = 0;

    protected:
        virtual void Reset() = 0;
    };

} //namespace rrns_db

#endif // IREDISMANAGER_H
