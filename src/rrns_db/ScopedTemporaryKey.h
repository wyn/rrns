#ifndef SCOPEDTEMPORARYKEY_H
#define SCOPEDTEMPORARYKEY_H

#include "ICredis.h"
#include "glog/logging.h"

namespace rrns_db
{
    class ScopedTemporaryKey
    {

    public:

        ScopedTemporaryKey(const char *key, const ICredis *credis)
            : key_(CHECK_NOTNULL(key))
            , credis_(CHECK_NOTNULL(credis))
        {
            DLOG(INFO) << "Scoping the key " << key_ << " for a set type";
            if (0 != credis_->sadd(key_, NULL))
                DLOG(ERROR) << "Could not create temp key " << key_;
        }

        virtual ~ScopedTemporaryKey()
        {
            //no throw here
            if (0 != credis_->del(key_))
                DLOG(ERROR) << "Could not delete temp key " << key_;
        }

        const char* Key() const { return key_; }

        bool Exists() const { return credis_->exists(key_); }

    private:
        const char *key_;
        const ICredis *credis_;

    };

} //namespace rrns_db

#endif // SCOPEDTEMPORARYKEY_H
