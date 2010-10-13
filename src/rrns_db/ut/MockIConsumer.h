#ifndef MOCKICONSUMER_H
#define MOCKICONSUMER_H

#include "IConsumer.h"
#include "gmock/gmock.h"

namespace rrns_db
{
    namespace test
    {

        class MockIConsumer : public IConsumer
        {
        public:

            MOCK_CONST_METHOD2( CanConsume, bool(const ICredis *rh, const std::string &dataKey) );

            MOCK_CONST_METHOD2( Count, int(const ICredis *rh, const std::string &dataKey) );

            MOCK_CONST_METHOD3( GetData, std::vector<double>(const ICredis *rh,  const std::string &dataKey, int count) );

        };

    } //namespace test

} //namespace rrns_db

#endif // MOCKICONSUMER_H
