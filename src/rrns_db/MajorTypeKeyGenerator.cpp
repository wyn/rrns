#include "MajorTypeKeyGenerator.h"
#include "Key.h"

using namespace rrns_db;

MajorTypeKeyGenerator::MajorTypeKeyGenerator()
{
}

boost::shared_ptr<IKey> MajorTypeKeyGenerator::ScalarKey(const std::string &member) const
{
    boost::shared_ptr<IKey> k(new Key("Ids", member, "MajorType"));
    return k;
}

boost::shared_ptr<IKey> MajorTypeKeyGenerator::CollectionKey(const std::string &member) const
{
    boost::shared_ptr<IKey> k(new Key("MajorTypes", member, "Ids"));
    return k;
}
