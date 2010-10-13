#ifndef CONSUMER_H
#define CONSUMER_H

#include "IConsumer.h"

namespace rrns_db
{

    class Consumer : public IConsumer
    {

    public:

        Consumer();

        virtual bool CanConsume(const ICredis *rh, const std::string &dataKey) const;

        virtual int Count(const ICredis *rh, const std::string &dataKey) const;

        virtual std::vector<double> GetData(const ICredis *rh,  const std::string &dataKey, int count) const;

    private:
        static const int default_max;
        static const int default_max_factor;

    private:
        //don't want these
        Consumer(const Consumer&);
        Consumer& operator=(const Consumer&);

    };

} //rrns_db

#endif // CONSUMER_H
