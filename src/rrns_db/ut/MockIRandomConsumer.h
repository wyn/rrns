#ifndef MOCKIRANDOMCONSUMER_H
#define MOCKIRANDOMCONSUMER_H

#include "IRandomConsumer.h"
#include "gmock/gmock.h"

namespace rrns_db
{
    namespace test
    {

        class MockIRandomConsumer : public IRandomConsumer
        {

        public:

            MOCK_METHOD3( Connect, void(const std::string &host, int port, int timeout) );
            MOCK_METHOD0( Disconnect, void() );

            MOCK_METHOD2( Register, void(const std::string &majorKey, const std::string &minorKey) );
            MOCK_METHOD0( Unregister, void() );

            //consuming data
            MOCK_CONST_METHOD0( CanConsume, bool() );
            MOCK_CONST_METHOD0( Count, int() );
            MOCK_CONST_METHOD1( GetRandoms, std::vector<double>(int howMany) );

        };

    } //namespace test

} //namespace rrns_db

#endif // MOCKIRANDOMCONSUMER_H
