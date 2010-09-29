#ifndef MOCKICREDISCONNECTOR_H
#define MOCKICREDISCONNECTOR_H

#include "ICredisConnector.h"
#include "gmock/gmock.h"

namespace rrns_db
{
    namespace test
    {

        class MockICredisConnector : public ICredisConnector
        {
        public:

            MOCK_METHOD3( Connect, void(const std::string &hostname, int port, int timeout) );

            MOCK_CONST_METHOD0( IsValidHandle, bool() );

            MOCK_CONST_METHOD0( Handle, REDIS() );

            MOCK_METHOD0( Disconnect, void() );

        };

    } //namespace test

} //namespace rrns_db

#endif // MOCKICREDISCONNECTOR_H
