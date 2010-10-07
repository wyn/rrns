#ifndef KEY_H
#define KEY_H

#include "IKey.h"

namespace rrns_db
{
    class Key : public IKey
    {
    public:
        Key(const std::string &family, const std::string &member, const std::string &entity)
            : family_(family), member_(member), entity_(entity)
        {}

        virtual std::string Family() const { return family_; }
        virtual void SetFamily(const std::string &in) { family_ = in; }

        virtual std::string Member() const { return member_; }
        virtual void SetMember(const std::string &in) { member_ = in; }

        virtual std::string Entity() const { return entity_; }
        virtual void SetEntity(const std::string &in) { entity_ = in; }

    private:
        std::string family_;
        std::string member_;
        std::string entity_;

    private:
        Key(const Key&);
        Key& operator=(const Key&);
    };

} //namespace rrns_db

#endif // KEY_H
