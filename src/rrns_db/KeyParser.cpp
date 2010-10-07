#include "KeyParser.h"
#include "IKey.h"
#include "glog/logging.h"
#include <sstream>

using namespace rrns_db;

const char KeyParser::delim(':');

KeyParser::KeyParser()
{
}

bool KeyParser::Serialise(const IKey *in, std::string &out) const
{
    if (!in)
    {
        DLOG(ERROR) << "Cannot serialise with NULL IKey";
        return false;
    }

    const std::string d(&delim);
    out = in->Family() + d + in->Member() + d + in->Entity();
    return true;

}

bool KeyParser::Deserialise(const std::string &in, IKey *out) const
{
    if (!out)
    {
        DLOG(ERROR) << "Cannot deserialise to NULL IKey";
        return false;
    }

    std::vector<std::string> bits;
    std::string s;
    std::stringstream ss(in);
    while (std::getline(ss, s, delim))
    {
        bits.push_back(s);
    }

    if (3 != bits.size())
    {
        DLOG(ERROR) << "Cannot deserialise - invalid input: " << in;
        return false;
    }

    out->SetFamily(bits[0]);
    out->SetMember(bits[1]);
    out->SetEntity(bits[2]);
    return true;

}
