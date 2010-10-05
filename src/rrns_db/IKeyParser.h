#ifndef IKEYPARSER_H
#define IKEYPARSER_H

#include <string>

namespace rrns_db
{
    class IKey;

    class IKeyParser
    {
    public:

        virtual ~IKeyParser() {}

        virtual bool Serialise(const IKey *in, std::string &out) const =0;

        virtual bool Deserialise(const std::string &in, IKey *out) const =0;
    };

} //namespace rrns_db

#endif // IKEYPARSER_H
