#ifndef IKEYGENERATOR_H
#define IKEYGENERATOR_H

#include <string>
#include "boost/shared_ptr.hpp"

namespace rrns_db
{
    class IKey;

    class IKeyGenerator
    {
    public:
        virtual ~IKeyGenerator() {}

        virtual boost::shared_ptr<IKey> ScalarKey(const std::string &member) const =0;
        virtual boost::shared_ptr<IKey> CollectionKey(const std::string &member) const =0;
    };

} //namespace rrns_db

#endif // IKEYGENERATOR_H
