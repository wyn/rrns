#ifndef MOCKICREDISCONSUMER_H
#define MOCKICREDISCONSUMER_H

#include "ICredisConsumer.h"
#include "gmock/gmock.h"

namespace rrns_db
{
    namespace test
    {

        class MockICredisConsumer : public ICredisConsumer
        {
        public:

            MOCK_METHOD1( RegisterConnection, void(ICredisConnector *conn) );

            MOCK_CONST_METHOD2( StreamExists, bool(const std::string &major, const std::string &minor) );

            MOCK_METHOD2( RegisterStream, void(const std::string &major, const std::string &minor) );

            MOCK_CONST_METHOD0( CanConsume, bool() );

            MOCK_CONST_METHOD1( GetRandoms, std::list<double>(int count) );

            MOCK_METHOD0( Reset, void() );

            MOCK_CONST_METHOD0( MajorType, std::string() );

            MOCK_CONST_METHOD0( MinorType, std::string() );
        };

    } //namespace test

} //namespace rrns_db

#endif // MOCKICREDISCONSUMER_H
