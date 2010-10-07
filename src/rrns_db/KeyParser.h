#ifndef KEYPARSER_H
#define KEYPARSER_H

#include "IKeyParser.h"

namespace rrns_db
{

    class KeyParser : public IKeyParser
    {
    public:
        KeyParser();

        virtual bool Serialise(const IKey *in, std::string &out) const;

        virtual bool Deserialise(const std::string &in, IKey *out) const;

    private:
        static const char delim;

    };

} //namespace rrns_db

#endif // KEYPARSER_H
