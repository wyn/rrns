#ifndef MOCKICREDISCONSUMER_H
#define MOCKICREDISCONSUMER_H

#include "IRedisConsumer.h"
#include "gmock/gmock.h"

namespace rrns_db
{
    namespace test
    {

        class MockIRedisConsumer : public IRedisConsumer
        {
        public:

            MOCK_CONST_METHOD2( CanConsume, bool(const ICredis *rh, const std::string &dataKey) );

            MOCK_CONST_METHOD3( GetRandoms, std::vector<double>(const ICredis *rh,  const std::string &dataKey, int count) );

        };

    } //namespace test

} //namespace rrns_db

#endif // MOCKICREDISCONSUMER_H
