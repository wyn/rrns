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

    class RedisKey : public IKey
    {
    public:
        RedisKey() : family(""), member(""), entity("")
        {}

        virtual std::string Family() const { return family; }
        virtual void SetFamily(const std::string &in) { family = in; }

        virtual std::string Member() const { return member; }
        virtual void SetMember(const std::string &in) { member = in; }

        virtual std::string Entity() const { return entity; }
        virtual void SetEntity(const std::string &in) { entity = in; }

    private:
        std::string family;
        std::string member;
        std::string entity;

    private:
        RedisKey(const RedisKey&);
        RedisKey& operator=(const RedisKey&);
    };

} //namespace rrns_db

#endif // IKEY_H
