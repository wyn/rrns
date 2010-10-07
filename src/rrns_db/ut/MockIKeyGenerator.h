#ifndef MOCKIKEYGENERATOR_H
#define MOCKIKEYGENERATOR_H

#include "IKeyGenerator.h"
#include "gmock/gmock.h"

namespace rrns_db
{
    namespace test
    {
        class MockIKeyGenerator : public IKeyGenerator
        {
        public:

            MOCK_CONST_METHOD1( ScalarKey, boost::shared_ptr<IKey>(const std::string &member) );
            MOCK_CONST_METHOD1( CollectionKey, boost::shared_ptr<IKey>(const std::string &member) );

        };

    } //namespace test

} //namespace rrns_db

#endif // MOCKIKEYGENERATOR_H
