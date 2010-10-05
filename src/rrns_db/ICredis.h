#ifndef ICREDIS_H
#define ICREDIS_H

//c++ interface for the redis/credis functions that we need
//mainly to simplify and help with testing/mocking

namespace rrns_db
{
    class ICredisConnector;

    class ICredis
    {
    public:

        virtual ~ICredis() {}

        virtual void SetConnector(ICredisConnector *connection) =0;
        virtual void ClearConnector() =0;

        /* if a function call returns error it is _possible_ that the Redis server
         * replied with an error message. It is returned by this function. */
        virtual char* errorreply() =0;

        /*
         * Commands operating on all the kind of values
         */

        /* returns -1 if the key doesn't exists and 0 if it does */
        virtual int exists(const char *key) =0;

        /* returns -1 if the key doesn't exists and 0 if it was removed
         * TODO add support to (Redis >= 1.1) remove multiple keys
         */
        virtual int del(const char *key) =0;

        /* returns type, refer to CREDIS_TYPE_* defines */
        virtual int type(const char *key) =0;

        /* returns number of keys returned in vector `keyv' */
        virtual int keys(const char *pattern, char ***keyv) =0;

        virtual int randomkey(char **key) =0;

        virtual int rename(const char *key, const char *new_key_name) =0;

        /* returns -1 if the key already exists */
        virtual int renamenx(const char *key, const char *new_key_name) =0;

        /* returns size of db */
        virtual int dbsize() =0;

        /* returns -1 if the timeout was not set; either due to key already has
           an associated timeout or key does not exist */
        virtual int expire(const char *key, int secs) =0;

        /* returns time to live seconds or -1 if key does not exists or does not
         * have expire set */
        virtual int ttl(const char *key) =0;

        virtual int select(int index) =0;

        /* returns -1 if the key was not moved; already present at target
         * or not found on current db */
        virtual int move(const char *key, int index) =0;

        virtual int flushdb() =0;

        virtual int flushall() =0;


        /*
         * Commands operating on string values
         */

        virtual int set(const char *key, const char *val) =0;

        /* returns -1 if the key doesn't exists */
        virtual int get(const char *key, char **val) =0;

        /* returns -1 if the key doesn't exists */
        virtual int getset(const char *key, const char *set_val, char **get_val) =0;

        /* returns number of values returned in vector `valv'. `keyc' is the number of
         * keys stored in `keyv'. */
        virtual int mget(int keyc, const char **keyv, char ***valv) =0;

        /* returns -1 if the key already exists and hence not set */
        virtual int setnx(const char *key, const char *val) =0;

        /* TODO
         * SETEX key time value Set+Expire combo command
         * MSET key1 value1 key2 value2 ... keyN valueN set a multiple keys to multiple values in a single atomic operation
         * MSETNX key1 value1 key2 value2 ... keyN valueN set a multiple keys to multiple values in a single atomic operation if none of
         */

        /* if `new_val' is not NULL it will return the value after the increment was performed */
        virtual int incr(const char *key, int *new_val) =0;

        /* if `new_val' is not NULL it will return the value after the increment was performed */
        virtual int incrby(const char *key, int incr_val, int *new_val) =0;

        /* if `new_val' is not NULL it will return the value after the decrement was performed */
        virtual int decr(const char *key, int *new_val) =0;

        /* if `new_val' is not NULL it will return the value after the decrement was performed */
        virtual int decrby(const char *key, int decr_val, int *new_val) =0;

        /* returns new length of string after `val' has been appended */
        virtual int append(const char *key, const char *val) =0;

        virtual int substr(const char *key, int start, int end, char **substr) =0;


        /*
         * Commands operating on lists
         */

        virtual int rpush(const char *key, const char *element) =0;

        virtual int lpush(const char *key, const char *element) =0;

        /* returns length of list */
        virtual int llen(const char *key) =0;

        /* returns number of elements returned in vector `elementv' */
        virtual int lrange(const char *key, int start, int range, char ***elementv) =0;

        virtual int ltrim(const char *key, int start, int end) =0;

        /* returns -1 if the key doesn't exists */
        virtual int lindex(const char *key, int index, char **element) =0;

        virtual int lset(const char *key, int index, const char *element) =0;

        /* returns number of elements removed */
        virtual int lrem(const char *key, int count, const char *element) =0;

        /* returns -1 if the key doesn't exists */
        virtual int lpop(const char *key, char **val) =0;

        /* returns -1 if the key doesn't exists */
        virtual int rpop(const char *key, char **val) =0;

        /* TODO
         * BLPOP key1 key2 ... keyN timeout Blocking LPOP
         * BRPOP key1 key2 ... keyN timeout Blocking RPOP
         * RPOPLPUSH srckey dstkey Return and remove (atomically) the last element of the source List stored at _srckey_ and push the same element to the destination List stored at _dstkey_
         */


        /*
         * Commands operating on sets
         */

        /* returns -1 if the given member was already a member of the set */
        virtual int sadd(const char *key, const char *member) =0;

        /* returns -1 if the given member is not a member of the set */
        virtual int srem(const char *key, const char *member) =0;

        /* returns -1 if the given key doesn't exists else value is returned in `member' */
        virtual int spop(const char *key, char **member) =0;

        /* returns -1 if the member doesn't exists in the source set */
        virtual int smove(const char *sourcekey, const char *destkey,
                         const char *member) =0;

        /* returns cardinality (number of members) or 0 if the given key doesn't exists */
        virtual int scard(const char *key) =0;

        /* returns -1 if the key doesn't exists and 0 if it does */
        virtual int sismember(const char *key, const char *member) =0;

        /* returns number of members returned in vector `members'. `keyc' is the number of
         * keys stored in `keyv'. */
        virtual int sinter(int keyc, const char **keyv, char ***members) =0;

        /* `keyc' is the number of keys stored in `keyv' */
        virtual int sinterstore(const char *destkey, int keyc, const char **keyv) =0;

        /* returns number of members returned in vector `members'. `keyc' is the number of
         * keys stored in `keyv'. */
        virtual int sunion(int keyc, const char **keyv, char ***members) =0;

        /* `keyc' is the number of keys stored in `keyv' */
        virtual int sunionstore(const char *destkey, int keyc, const char **keyv) =0;

        /* returns number of members returned in vector `members'. `keyc' is the number of
         * keys stored in `keyv'. */
        virtual int sdiff(int keyc, const char **keyv, char ***members) =0;

        /* `keyc' is the number of keys stored in `keyv' */
        virtual int sdiffstore(const char *destkey, int keyc, const char **keyv) =0;

        /* returns number of members returned in vector `members' */
        virtual int smembers(const char *key, char ***members) =0;

        /* TODO Redis >= 1.1
         * SRANDMEMBER key Return a random member of the Set value at key
         */


        /*
         * Commands operating on sorted sets
         */

        /* returns -1 if member was already a member of the sorted set and only score was updated,
         * 0 is returned if the new element was added */
        virtual int zadd(const char *key, double score, const char *member) =0;

        /* returns -1 if the member was not a member of the sorted set */
        virtual int zrem(const char *key, const char *member) =0;

        /* returns -1 if the member was not a member of the sorted set, the score of the member after
         * the increment by `incr_score' is returned by `new_score' */
        virtual int zincrby(const char *key, double incr_score, const char *member, double *new_score) =0;

        /* returns the rank of the given member or -1 if the member was not a member of the sorted set */
        virtual int zrank(const char *key, const char *member) =0;

        /* returns the reverse rank of the given member or -1 if the member was not a member of the sorted set */
        virtual int zrevrank(const char *key, const char *member) =0;

        /* returns number of elements returned in vector `elementv'
         * TODO add support for WITHSCORES */
        virtual int zrange(const char *key, int start, int end, char ***elementv) =0;

        /* returns number of elements returned in vector `elementv'
         * TODO add support for WITHSCORES */
        virtual int zrevrange(const char *key, int start, int end, char ***elementv) =0;

        /* returns cardinality or -1 if `key' does not exist */
        virtual int zcard(const char *key) =0;

        /* returns -1 if the `key' does not exist or the `member' is not in the sorted set,
         * score is returned in `score' */
        virtual int zscore(const char *key, const char *member, double *score) =0;

        /* returns number of elements removed or -1 if key does not exist */
        virtual int zremrangebyscore(const char *key, double min, double max) =0;

        /* returns number of elements removed or -1 if key does not exist */
        virtual int zremrangebyrank(const char *key, int start, int end) =0;

        /* TODO
         * ZRANGEBYSCORE key min max Return all the elements with score >= min and score <= max (a range query) from the sorted set
         */

//        /* `keyc' is the number of keys stored in `keyv'. `weightv' is optional, if not
//         * NULL, `keyc' is also the number of weights stored in `weightv'. */
//        virtual int zinterstore(const char *destkey, int keyc, const char **keyv,
//                               const int *weightv, REDIS_AGGREGATE aggregate) =0;

//        /* `keyc' is the number of keys stored in `keyv'. `weightv' is optional, if not
//         * NULL, `keyc' is also the number of weights stored in `weightv'. */
//        virtual int zunionstore(const char *destkey, int keyc, const char **keyv,
//                               const int *weightv, REDIS_AGGREGATE aggregate) =0;

        /*
         * Commands operating on hashes
         */

        /* TODO
         * HSET key field value Set the hash field to the specified value. Creates the hash if needed.
         * HGET key field Retrieve the value of the specified hash field.
         * HMSET key field1 value1 ... fieldN valueN Set the hash fields to their respective values.
         * HINCRBY key field integer Increment the integer value of the hash at _key_ on _field_ with _integer_.
         * HEXISTS key field Test for existence of a specified field in a hash
         * HDEL key field Remove the specified field from a hash
         * HLEN key Return the number of items in a hash.
         * HKEYS key Return all the fields in a hash.
         * HVALS key Return all the values in a hash.
         * HGETALL key Return all the fields and associated values in a hash.
         */


        /*
         * Sorting
         */

        /* returns number of elements returned in vector `elementv' */
        virtual int sort(const char *query, char ***elementv) =0;


        /*
         * Transactions
         */

        /* TODO
         * MULTI/EXEC/DISCARD Redis atomic transactions
         */


        /*
         * Publish/Subscribe
         *
         * !!EXPERIMENTAL!! Expect API and implementation to change until these
         * lines are removed.
         *
         * The nature of the publish/subscribe messaging paradigm differs from the
         * rest of Redis, the main difference being messages are pushed to subscribing
         * clients. Credis tries to hide some of this de-coupling in order to make life
         * easier for application programmers. All subscribe, unsubscribe and publish
         * function calls will return when an acknowledgement has been received or on
         * error (including timeout), just as all other Credis function calls that map
         * to Redis commands. If a message is pushed to the client while waiting for
         * an acknowledgement, to for instance a new subscription, that message is
         * stored on an internal FIFO. When the client is ready to receive messages a
         * call to listen function is made and if there is a message in the FIFO it is
         * immediately returned else Credis waits for a message being pushed from Redis.
         *
         * IMPORTANT! Note that while subscribing to one or more channels (or patterns)
         * the client is in a publish/subscribe state in which is not allowed to perform
         * other commands.
         */

        /* On success the number of channels we are currently subscribed to is
         * returned. */
        virtual int subscribe(const char *channel) =0;

        /* `channel' specifies the channel to unsubscribe from. If set to NULL
         * all channels are unsubscribed from. On success the number of channels
         * we are currently subscribed to is returned. */
        virtual int unsubscribe(const char *channel) =0;

        /* On success the number of channels we are currently subscribed to is
         * returned. */
        virtual int psubscribe(const char *pattern) =0;

        /* `pattern' specifies the channels to unsubscribe from. If set to NULL
         * all are unsubscribed from. On success the number of channels we are
         * currently subscribed to is returned. */
        virtual int punsubscribe(const char *pattern) =0;

        /* On success the number of clients that received the message is returned */
        virtual int publish(const char *channel, const char *message) =0;

        /* Listen for messages from channels and/or patterns subscribed to */
        virtual int listen(char **pattern, char **channel, char **message) =0;


        /*
         * Persistence control commands
         */

        virtual int save() =0;

        virtual int bgsave() =0;

        /* returns UNIX time stamp of last successfull save to disk */
        virtual int lastsave() =0;

        virtual int shutdown() =0;

        virtual int bgrewriteaof() =0;


        /*
         * Remote server control commands
         */

        /* Because the information returned by the Redis changes with virtually every
         * major release, credis tries to parse for as many fields as it is aware of,
         * staying backwards (and forwards) compatible with older (and newer) versions
         * of Redis.
         * Information fields not supported by the Redis server connected to, are set
         * to zero. */
//        virtual int info(REDIS_INFO *info) =0;

        virtual int monitor() =0;

        /* setting host to NULL and/or port to 0 will turn off replication */
        virtual int slaveof(const char *host, int port) =0;

        /* TODO
         * CONFIG Configure a Redis server at runtime
         */
    };

} //namespace rrns_db

#endif // ICREDIS_H
