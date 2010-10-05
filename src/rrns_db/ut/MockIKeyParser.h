#ifndef MOCKIKEYPARSER_H
#define MOCKIKEYPARSER_H

#include "IKeyParser.h"
#include "gmock/gmock.h"

namespace rrns_db
{
    namespace test
    {
        class MockIKeyParser : public IKeyParser
        {
        public:

            MOCK_CONST_METHOD2( Serialise, bool(const IKey *in, std::string &out) );

            MOCK_CONST_METHOD2( Deserialise, bool(const std::string &in, IKey *out) );
        };

    } //namespace test

} //namespace rrns_db

#endif // MOCKIKEYPARSER_H
