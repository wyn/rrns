#include "MinorTypeKeyGenerator.h"
#include "Key.h"

using namespace rrns_db;

MinorTypeKeyGenerator::MinorTypeKeyGenerator()
{
}

boost::shared_ptr<IKey> MinorTypeKeyGenerator::ScalarKey(const std::string &member) const
{
    boost::shared_ptr<IKey> k(new Key("Ids", member, "MinorType"));
    return k;
}

boost::shared_ptr<IKey> MinorTypeKeyGenerator::CollectionKey(const std::string &member) const
{
    boost::shared_ptr<IKey> k(new Key("MinorTypes", member, "Ids"));
    return k;
}
