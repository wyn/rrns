#include "SeedKeyGenerator.h"
#include "Key.h"

using namespace rrns_db;

SeedKeyGenerator::SeedKeyGenerator()
{
}

boost::shared_ptr<IKey> SeedKeyGenerator::ScalarKey(const std::string &member) const
{
    boost::shared_ptr<IKey> k(new Key("Ids", member, "Seed"));
    return k;
}

boost::shared_ptr<IKey> SeedKeyGenerator::CollectionKey(const std::string &member) const
{
    boost::shared_ptr<IKey> k(new Key("Seeds", member, "Ids"));
    return k;
}
