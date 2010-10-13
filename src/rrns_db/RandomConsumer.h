#ifndef RANDOMCONSUMER_H
#define RANDOMCONSUMER_H

#include "IRandomConsumer.h"

namespace rrns_db {

    //forwards
    class ICredis;
    class IRedisConnector;
    class IRedisConsumer;
    class IKeyParser;
    class IKeyGenerator;

    class RandomConsumer : public IRandomConsumer
    {

    public:

        //construct/destruct
        RandomConsumer(ICredis *credis,
                     IRedisConnector *connector,
                     const IRedisConsumer *consumer,
                     const IKeyParser *parser,
                     const IKeyGenerator *dataKeyGenerator);

        //Connect/disconnect with db
        virtual void Connect(const std::string &host, int port, int timeout);
        virtual void Disconnect();

        //Register/unregister with a RN data stream
        virtual void Register(const std::string &majorKey, const std::string &minorKey);
        virtual void Unregister();

        //consuming data
        virtual bool CanConsume() const;
        virtual int Count() const;
        virtual std::vector<double> GetRandoms(int howMany) const;

    private:

        static const std::string unknown_id;

        //Redis stuff
        std::string id_;
        ICredis *credis_;
        IRedisConnector *connector_;

        const IRedisConsumer *consumer_;
        const IKeyParser *parser_;
        const IKeyGenerator *dataKeyGenerator_;

    private:
        //don't want these
        RandomConsumer(const RandomConsumer&);
        RandomConsumer& operator=(const RandomConsumer&);

    };

} //namespace rrns_db

#endif // RANDOMCONSUMER_H
