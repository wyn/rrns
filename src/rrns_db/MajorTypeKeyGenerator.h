#ifndef MAJORTYPEKEYGENERATOR_H
#define MAJORTYPEKEYGENERATOR_H

#include "IKeyGenerator.h"

namespace rrns_db
{
    class MajorTypeKeyGenerator : public IKeyGenerator
    {
    public:
        MajorTypeKeyGenerator();

        virtual boost::shared_ptr<IKey> ScalarKey(const std::string &member) const;
        virtual boost::shared_ptr<IKey> CollectionKey(const std::string &member) const;

    };

} //namespace rrns_db

#endif // MAJORTYPEKEYGENERATOR_H
