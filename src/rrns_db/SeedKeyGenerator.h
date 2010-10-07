#ifndef SEEDKEYGENERATOR_H
#define SEEDKEYGENERATOR_H

#include "IKeyGenerator.h"

namespace rrns_db
{

    class SeedKeyGenerator : public IKeyGenerator
    {
    public:
        SeedKeyGenerator();

        virtual boost::shared_ptr<IKey> ScalarKey(const std::string &member) const;
        virtual boost::shared_ptr<IKey> CollectionKey(const std::string &member) const;

    };

}// namespace rrns_db

#endif // SEEDKEYGENERATOR_H
