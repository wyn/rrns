#ifndef ICREDISCONNECTOR_H
#define ICREDISCONNECTOR_H

#include "credis.h"
#include <string>

//want this interface to take care of our general needs for connecting to a REDIS db
namespace rrns_db {

    class ICredisConnector
    {
    public:

        virtual ~ICredisConnector() {}

        virtual void Connect(const std::string &hostname, int port, int timeout) = 0;

        virtual bool IsValidHandle() const = 0;

        virtual REDIS Handle() const = 0;

        virtual void Disconnect() = 0;

    };

} //namespace rrns_db

#endif // ICREDISCONNECTOR_H
