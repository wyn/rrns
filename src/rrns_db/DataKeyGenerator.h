#ifndef DATAKEYGENERATOR_H
#define DATAKEYGENERATOR_H

#include "IKeyGenerator.h"

namespace rrns_db
{

    class DataKeyGenerator : public IKeyGenerator
    {
    public:
        DataKeyGenerator();

        virtual boost::shared_ptr<IKey> ScalarKey(const std::string &member) const;
        virtual boost::shared_ptr<IKey> CollectionKey(const std::string &member) const;

    };

}// namespace rrns_db

#endif // DATAKEYGENERATOR_H
