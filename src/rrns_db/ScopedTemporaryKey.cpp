#include "ScopedTemporaryKey.h"
#include "ICredis.h"
#include "glog/logging.h"

using namespace rrns_db;

ScopedTemporaryKey::ScopedTemporaryKey(const char *key, const ICredis *credis)
    : key_(CHECK_NOTNULL(key))
    , credis_(CHECK_NOTNULL(credis))
{
    DLOG(INFO) << "Scoping the key " << key_ << " for a set type";
    if (0 != credis_->sadd(key_, NULL))
        DLOG(ERROR) << "Could not create temp key " << key_;
}

ScopedTemporaryKey::~ScopedTemporaryKey()
{
    //no throw here
    if (0 != credis_->del(key_))
        DLOG(ERROR) << "Could not delete temp key " << key_;
}

const char* ScopedTemporaryKey::Key() const
{
    return key_;
}

bool ScopedTemporaryKey::Exists() const
{
    return credis_->exists(key_);
}
