#ifndef IKEY_H
#define IKEY_H

#include <string>

namespace rrns_db
{
    class IKey
    {

    public:

        virtual ~IKey() {}

        virtual std::string Family() const =0;
        virtual void SetFamily(const std::string &in) =0;

        virtual std::string Member() const =0;
        virtual void SetMember(const std::string &in) =0;

        virtual std::string Entity() const =0;
        virtual void SetEntity(const std::string &in) =0;
    };

} //namespace rrns_db

#endif // IKEY_H
