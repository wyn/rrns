#ifndef CUTOFFKEYGENERATOR_H
#define CUTOFFKEYGENERATOR_H

#include "IKeyGenerator.h"

namespace rrns_db
{

    class CutoffKeyGenerator : public IKeyGenerator
    {
    public:
        CutoffKeyGenerator();

        virtual boost::shared_ptr<IKey> ScalarKey(const std::string &member) const;
        virtual boost::shared_ptr<IKey> CollectionKey(const std::string &member) const;

    };

}// namespace rrns_db

#endif // CUTOFFKEYGENERATOR_H
