#include "DataKeyGenerator.h"
#include "Key.h"
#include "glog/logging.h"

using namespace rrns_db;

DataKeyGenerator::DataKeyGenerator()
{
}

boost::shared_ptr<IKey> DataKeyGenerator::ScalarKey(const std::string &member) const
{
    boost::shared_ptr<IKey> k(new Key("Ids", member, "Data"));
    return k;
}

boost::shared_ptr<IKey> DataKeyGenerator::CollectionKey(const std::string &member) const
{
    DLOG(INFO) << "No Collection key for Data with " << member;
    return boost::shared_ptr<IKey>();
}
