#ifndef MOCKIKEY_H
#define MOCKIKEY_H

#include "IKey.h"
#include "gmock/gmock.h"

namespace rrns_db
{
    namespace test
    {
        class MockIKey : public IKey
        {
        public:

            MOCK_CONST_METHOD0( Family, std::string() );
            MOCK_METHOD1( SetFamily, void(const std::string &in) );

            MOCK_CONST_METHOD0( Member, std::string() );
            MOCK_METHOD1( SetMember, void(const std::string &in) );

            MOCK_CONST_METHOD0( Entity, std::string() );
            MOCK_METHOD1( SetEntity, void(const std::string &in) );
        };

    } //namespace test

} //namespace rrns_db

#endif // MOCKIKEY_H
