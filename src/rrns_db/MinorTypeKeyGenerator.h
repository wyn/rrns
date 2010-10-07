#ifndef MINORTYPEKEYGENERATOR_H
#define MINORTYPEKEYGENERATOR_H

#include "IKeyGenerator.h"

namespace rrns_db
{
    class MinorTypeKeyGenerator : public IKeyGenerator
    {
    public:
        MinorTypeKeyGenerator();

        virtual boost::shared_ptr<IKey> ScalarKey(const std::string &member) const;
        virtual boost::shared_ptr<IKey> CollectionKey(const std::string &member) const;

    };

} //namespace rrns_db

#endif // MINORTYPEKEYGENERATOR_H
