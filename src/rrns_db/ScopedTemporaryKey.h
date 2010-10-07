#ifndef SCOPEDTEMPORARYKEY_H
#define SCOPEDTEMPORARYKEY_H

namespace rrns_db
{
    class ICredis;

    class ScopedTemporaryKey
    {

    public:

        ScopedTemporaryKey(const char *key, const ICredis *credis);

        virtual ~ScopedTemporaryKey();

        const char* Key() const;

        bool Exists() const;

    private:
        const char *key_;
        const ICredis *credis_;

    };

} //namespace rrns_db

#endif // SCOPEDTEMPORARYKEY_H
