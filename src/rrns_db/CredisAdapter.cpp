#include "CredisAdapter.h"
#include "glog/logging.h"
#include "IRedisConnector.h"

using namespace rrns_db;

CredisAdapter::CredisAdapter()
{
}

void CredisAdapter::SetConnector(IRedisConnector *connection)
{
    CHECK_NOTNULL(connection);
    rh_ = connection->Handle();
}
void CredisAdapter::ClearConnector()
{
    rh_ = NULL;
}

/* if a function call returns error it is _possible_ that the Redis server
 * replied with an error message. It is returned by this function. */
char* CredisAdapter::errorreply() const { return credis_errorreply(rh_); }

/*
 * Commands operating on all the kind of values
 */

/* returns -1 if the key doesn't exists and 0 if it does */
int CredisAdapter::exists(const char *key) const { return credis_exists(rh_, key); }

/* returns -1 if the key doesn't exists and 0 if it was removed
 * TODO add support to (Redis >= 1.1) remove multiple keys
 */
int CredisAdapter::del(const char *key) const { return credis_del(rh_, key); }

/* returns type, refer to CREDIS_TYPE_* defines */
int CredisAdapter::type(const char *key) const { return credis_type(rh_, key); }

/* returns number of keys returned in vector `keyv' */
int CredisAdapter::keys(const char *pattern, char ***keyv) const { return credis_keys(rh_, pattern, keyv); }

int CredisAdapter::randomkey(char **key) const { return credis_randomkey(rh_, key); }

int CredisAdapter::rename(const char *key, const char *new_key_name) const { return credis_rename(rh_, key, new_key_name); }

/* returns -1 if the key already exists */
int CredisAdapter::renamenx(const char *key, const char *new_key_name) const { return credis_renamenx(rh_, key, new_key_name); }

/* returns size of db */
int CredisAdapter::dbsize() const { return credis_dbsize(rh_); }

/* returns -1 if the timeout was not set; either due to key already has
   an associated timeout or key does not exist */
int CredisAdapter::expire(const char *key, int secs) const { return credis_expire(rh_, key, secs); }

/* returns time to live seconds or -1 if key does not exists or does not
 * have expire set */
int CredisAdapter::ttl(const char *key) const { return credis_ttl(rh_, key); }

int CredisAdapter::select(int index) const { return credis_select(rh_, index); }

/* returns -1 if the key was not moved; already present at target
 * or not found on current db */
int CredisAdapter::move(const char *key, int index) const { return credis_move(rh_, key, index); }

int CredisAdapter::flushdb() const { return credis_flushdb(rh_); }

int CredisAdapter::flushall() const { return credis_flushall(rh_); }


/*
 * Commands operating on string values
 */

int CredisAdapter::set(const char *key, const char *val) const { return credis_set(rh_, key, val); }

/* returns -1 if the key doesn't exists */
int CredisAdapter::get(const char *key, char **val) const { return credis_get(rh_, key, val); }

/* returns -1 if the key doesn't exists */
int CredisAdapter::getset(const char *key, const char *set_val, char **get_val) const { return credis_getset(rh_, key, set_val, get_val); }

/* returns number of values returned in vector `valv'. `keyc' is the number of
 * keys stored in `keyv'. */
int CredisAdapter::mget(int keyc, const char **keyv, char ***valv) const { return credis_mget(rh_, keyc, keyv, valv); }

/* returns -1 if the key already exists and hence not set */
int CredisAdapter::setnx(const char *key, const char *val) const { return credis_setnx(rh_, key, val); }

/* TODO
 * SETEX key time value Set+Expire combo command
 * MSET key1 value1 key2 value2 ... keyN valueN set a multiple keys to multiple values in a single atomic operation
 * MSETNX key1 value1 key2 value2 ... keyN valueN set a multiple keys to multiple values in a single atomic operation if none of
 */

/* if `new_val' is not NULL it will return the value after the increment was performed */
int CredisAdapter::incr(const char *key, int *new_val) const { return credis_incr(rh_, key, new_val); }

/* if `new_val' is not NULL it will return the value after the increment was performed */
int CredisAdapter::incrby(const char *key, int incr_val, int *new_val) const { return credis_incrby(rh_, key, incr_val, new_val); }

/* if `new_val' is not NULL it will return the value after the decrement was performed */
int CredisAdapter::decr(const char *key, int *new_val) const { return credis_decr(rh_, key, new_val); }

/* if `new_val' is not NULL it will return the value after the decrement was performed */
int CredisAdapter::decrby(const char *key, int decr_val, int *new_val) const { return credis_decrby(rh_, key, decr_val, new_val); }

/* returns new length of string after `val' has been appended */
int CredisAdapter::append(const char *key, const char *val) const { return credis_append(rh_, key, val); }

int CredisAdapter::substr(const char *key, int start, int end, char **substr) const { return credis_substr(rh_, key, start, end, substr); }


/*
 * Commands operating on lists
 */

int CredisAdapter::rpush(const char *key, const char *element) const { return credis_rpush(rh_, key, element); }

int CredisAdapter::lpush(const char *key, const char *element) const { return credis_lpush(rh_, key, element); }

/* returns length of list */
int CredisAdapter::llen(const char *key) const { return credis_llen(rh_, key); }

/* returns number of elements returned in vector `elementv' */
int CredisAdapter::lrange(const char *key, int start, int range, char ***elementv) const { return credis_lrange(rh_, key, start, range, elementv); }

int CredisAdapter::ltrim(const char *key, int start, int end) const { return credis_ltrim(rh_, key, start, end); }

/* returns -1 if the key doesn't exists */
int CredisAdapter::lindex(const char *key, int index, char **element) const { return credis_lindex(rh_, key, index, element); }

int CredisAdapter::lset(const char *key, int index, const char *element) const { return credis_lset(rh_, key, index, element); }

/* returns number of elements removed */
int CredisAdapter::lrem(const char *key, int count, const char *element) const { return credis_lrem(rh_, key, count, element); }

/* returns -1 if the key doesn't exists */
int CredisAdapter::lpop(const char *key, char **val) const { return credis_lpop(rh_, key, val); }

/* returns -1 if the key doesn't exists */
int CredisAdapter::rpop(const char *key, char **val) const { return credis_rpop(rh_, key, val); }

/* TODO
 * BLPOP key1 key2 ... keyN timeout Blocking LPOP
 * BRPOP key1 key2 ... keyN timeout Blocking RPOP
 * RPOPLPUSH srckey dstkey Return and remove (atomically) the last element of the source List stored at _srckey_ and push the same element to the destination List stored at _dstkey_
 */


/*
 * Commands operating on sets
 */

/* returns -1 if the given member was already a member of the set */
int CredisAdapter::sadd(const char *key, const char *member) const { return credis_sadd(rh_, key, member); }

/* returns -1 if the given member is not a member of the set */
int CredisAdapter::srem(const char *key, const char *member) const { return credis_srem(rh_, key, member); }

/* returns -1 if the given key doesn't exists else value is returned in `member' */
int CredisAdapter::spop(const char *key, char **member) const { return credis_spop(rh_, key, member); }

/* returns -1 if the member doesn't exists in the source set */
int CredisAdapter::smove(const char *sourcekey, const char *destkey, const char *member) const { return credis_smove(rh_, sourcekey, destkey, member); }

/* returns cardinality (number of members) or 0 if the given key doesn't exists */
int CredisAdapter::scard(const char *key) const { return credis_scard(rh_, key); }

/* returns -1 if the key doesn't exists and 0 if it does */
int CredisAdapter::sismember(const char *key, const char *member) const { return credis_sismember(rh_, key, member); }

/* returns number of members returned in vector `members'. `keyc' is the number of
 * keys stored in `keyv'. */
int CredisAdapter::sinter(int keyc, const char **keyv, char ***members) const { return credis_sinter(rh_, keyc, keyv, members); }

/* `keyc' is the number of keys stored in `keyv' */
int CredisAdapter::sinterstore(const char *destkey, int keyc, const char **keyv) const { return credis_sinterstore(rh_, destkey, keyc, keyv); }

/* returns number of members returned in vector `members'. `keyc' is the number of
 * keys stored in `keyv'. */
int CredisAdapter::sunion(int keyc, const char **keyv, char ***members) const { return credis_sunion(rh_, keyc, keyv, members); }

/* `keyc' is the number of keys stored in `keyv' */
int CredisAdapter::sunionstore(const char *destkey, int keyc, const char **keyv) const { return credis_sunionstore(rh_, destkey, keyc, keyv); }

/* returns number of members returned in vector `members'. `keyc' is the number of
 * keys stored in `keyv'. */
int CredisAdapter::sdiff(int keyc, const char **keyv, char ***members) const { return credis_sdiff(rh_, keyc, keyv, members); }

/* `keyc' is the number of keys stored in `keyv' */
int CredisAdapter::sdiffstore(const char *destkey, int keyc, const char **keyv) const { return credis_sdiffstore(rh_, destkey, keyc, keyv); }

/* returns number of members returned in vector `members' */
int CredisAdapter::smembers(const char *key, char ***members) const { return credis_smembers(rh_, key, members); }

/* TODO Redis >= 1.1
 * SRANDMEMBER key Return a random member of the Set value at key
 */


/*
 * Commands operating on sorted sets
 */

/* returns -1 if member was already a member of the sorted set and only score was updated,
 * 0 is returned if the new element was added */
int CredisAdapter::zadd(const char *key, double score, const char *member) const { return credis_zadd(rh_, key, score, member); }

/* returns -1 if the member was not a member of the sorted set */
int CredisAdapter::zrem(const char *key, const char *member) const { return credis_zrem(rh_, key, member); }

/* returns -1 if the member was not a member of the sorted set, the score of the member after
 * the increment by `incr_score' is returned by `new_score' */
int CredisAdapter::zincrby(const char *key, double incr_score, const char *member, double *new_score) const { return credis_zincrby(rh_, key, incr_score, member, new_score); }

/* returns the rank of the given member or -1 if the member was not a member of the sorted set */
int CredisAdapter::zrank(const char *key, const char *member) const { return credis_zrank(rh_, key, member); }

/* returns the reverse rank of the given member or -1 if the member was not a member of the sorted set */
int CredisAdapter::zrevrank(const char *key, const char *member) const { return credis_zrevrank(rh_, key, member); }

/* returns number of elements returned in vector `elementv'
 * TODO add support for WITHSCORES */
int CredisAdapter::zrange(const char *key, int start, int end, char ***elementv) const { return credis_zrange(rh_, key, start, end, elementv); }

/* returns number of elements returned in vector `elementv'
 * TODO add support for WITHSCORES */
int CredisAdapter::zrevrange(const char *key, int start, int end, char ***elementv) const { return credis_zrevrange(rh_, key, start, end, elementv); }

/* returns cardinality or -1 if `key' does not exist */
int CredisAdapter::zcard(const char *key) const { return credis_zcard(rh_, key); }

/* returns -1 if the `key' does not exist or the `member' is not in the sorted set,
 * score is returned in `score' */
int CredisAdapter::zscore(const char *key, const char *member, double *score) const { return credis_zscore(rh_, key, member, score); }

/* returns number of elements removed or -1 if key does not exist */
int CredisAdapter::zremrangebyscore(const char *key, double min, double max) const { return credis_zremrangebyscore(rh_, key, min, max); }

/* returns number of elements removed or -1 if key does not exist */
int CredisAdapter::zremrangebyrank(const char *key, int start, int end) const { return credis_zremrangebyrank(rh_, key, start, end); }

/* TODO
 * ZRANGEBYSCORE key min max Return all the elements with score >= min and score <= max (a range query) from the sorted set
 */

//        /* `keyc' is the number of keys stored in `keyv'. `weightv' is optional, if not
//         * NULL, `keyc' is also the number of weights stored in `weightv'. */
//        int zinterstore(const char *destkey, int keyc, const char **keyv,
//                               const int *weightv, REDIS_AGGREGATE aggregate) const {}

//        /* `keyc' is the number of keys stored in `keyv'. `weightv' is optional, if not
//         * NULL, `keyc' is also the number of weights stored in `weightv'. */
//        int zunionstore(const char *destkey, int keyc, const char **keyv,
//                               const int *weightv, REDIS_AGGREGATE aggregate) const {}

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
int CredisAdapter::sort(const char *query, char ***elementv) const { return credis_sort(rh_, query, elementv); }


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
int CredisAdapter::subscribe(const char *channel) const { return credis_subscribe(rh_, channel); }

/* `channel' specifies the channel to unsubscribe from. If set to NULL
 * all channels are unsubscribed from. On success the number of channels
 * we are currently subscribed to is returned. */
int CredisAdapter::unsubscribe(const char *channel) const { return credis_unsubscribe(rh_, channel); }

/* On success the number of channels we are currently subscribed to is
 * returned. */
int CredisAdapter::psubscribe(const char *pattern) const { return credis_psubscribe(rh_, pattern); }

/* `pattern' specifies the channels to unsubscribe from. If set to NULL
 * all are unsubscribed from. On success the number of channels we are
 * currently subscribed to is returned. */
int CredisAdapter::punsubscribe(const char *pattern) const { return credis_punsubscribe(rh_, pattern); }

/* On success the number of clients that received the message is returned */
int CredisAdapter::publish(const char *channel, const char *message) const { return credis_publish(rh_, channel, message); }

/* Listen for messages from channels and/or patterns subscribed to */
int CredisAdapter::listen(char **pattern, char **channel, char **message) const { return credis_listen(rh_, pattern, channel, message); }


/*
 * Persistence control commands
 */

int CredisAdapter::save() const { return credis_save(rh_); }

int CredisAdapter::bgsave() const { return credis_bgsave(rh_); }

/* returns UNIX time stamp of last successfull save to disk */
int CredisAdapter::lastsave() const { return credis_lastsave(rh_); }

int CredisAdapter::shutdown() const { return credis_shutdown(rh_); }

int CredisAdapter::bgrewriteaof() const { return credis_bgrewriteaof(rh_); }


/*
 * Remote server control commands
 */

/* Because the information returned by the Redis changes with virtually every
 * major release, credis tries to parse for as many fields as it is aware of,
 * staying backwards (and forwards) compatible with older (and newer) versions
 * of Redis.
 * Information fields not supported by the Redis server connected to, are set
 * to zero. */
//        int info(REDIS_INFO *info) const {}

int CredisAdapter::monitor() const { return credis_monitor(rh_); }

/* setting host to NULL and/or port to 0 will turn off replication */
int CredisAdapter::slaveof(const char *host, int port) const { return credis_slaveof(rh_, host, port); }
