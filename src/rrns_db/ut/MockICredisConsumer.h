#ifndef MOCKICREDISCONSUMER_H
#define MOCKICREDISCONSUMER_H

#include "ICredisConsumer.h"
#include "gmock/gmock.h"

namespace rrns_db {

    class MockICredisConsumer : public ICredisConsumer
    {
    public:

        MOCK_METHOD0(Init, void());

        MOCK_CONST_METHOD3(GetHandle, REDIS(const std::string &hostname, int port, int timeout));

        MOCK_CONST_METHOD1(IsValidHandle, bool(REDIS h));

        MOCK_CONST_METHOD1(Close, void(REDIS h));

        MOCK_CONST_METHOD1(Quit, void(REDIS h));

        MOCK_CONST_METHOD3(StreamExists, bool(REDIS h, const std::string &major, const std::string &minor));

        MOCK_CONST_METHOD3(GetStreamId, int(REDIS h, const std::string &major, const std::string &minor));

        MOCK_CONST_METHOD3(GetRandoms, std::list<double>(REDIS h, int id, int count));

    };

} //namespace rrns_db

#endif // MOCKICREDISCONSUMER_H
