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

            MOCK_CONST_METHOD2( CanConsume, bool(ICredis *rh, const std::string &dataKey) );

            MOCK_CONST_METHOD3( GetRandoms, std::list<double>(ICredis *rh,  const std::string &dataKey, int count) );

        };

    } //namespace test

} //namespace rrns_db

#endif // MOCKICREDISCONSUMER_H
