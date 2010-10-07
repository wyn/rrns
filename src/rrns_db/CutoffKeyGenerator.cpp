#include "CutoffKeyGenerator.h"
#include "Key.h"

using namespace rrns_db;

CutoffKeyGenerator::CutoffKeyGenerator()
{
}

boost::shared_ptr<IKey> CutoffKeyGenerator::ScalarKey(const std::string &member) const
{
    boost::shared_ptr<IKey> k(new Key("Ids", member, "Cutoff"));
    return k;
}

boost::shared_ptr<IKey> CutoffKeyGenerator::CollectionKey(const std::string &member) const
{
    boost::shared_ptr<IKey> k(new Key("Cutoffs", member, "Ids"));
    return k;
}
