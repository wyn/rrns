#include "ICredis.h"
#include "gmock/gmock.h"

namespace rrns_db {

namespace test {

class MockICredis : public ICredis {
 public:
  MOCK_METHOD1(SetConnector,
      void(IRedisConnector *connection));
  MOCK_METHOD0(ClearConnector,
      void());
  MOCK_CONST_METHOD0(errorreply,
      char*());
  MOCK_CONST_METHOD1(exists,
      int(const char *key));
  MOCK_CONST_METHOD1(del,
      int(const char *key));
  MOCK_CONST_METHOD1(type,
      int(const char *key));
  MOCK_CONST_METHOD2(keys,
      int(const char *pattern, char ***keyv));
  MOCK_CONST_METHOD1(randomkey,
      int(char **key));
  MOCK_CONST_METHOD2(rename,
      int(const char *key, const char *new_key_name));
  MOCK_CONST_METHOD2(renamenx,
      int(const char *key, const char *new_key_name));
  MOCK_CONST_METHOD0(dbsize,
      int());
  MOCK_CONST_METHOD2(expire,
      int(const char *key, int secs));
  MOCK_CONST_METHOD1(ttl,
      int(const char *key));
  MOCK_CONST_METHOD1(select,
      int(int index));
  MOCK_CONST_METHOD2(move,
      int(const char *key, int index));
  MOCK_CONST_METHOD0(flushdb,
      int());
  MOCK_CONST_METHOD0(flushall,
      int());
  MOCK_CONST_METHOD2(set,
      int(const char *key, const char *val));
  MOCK_CONST_METHOD2(get,
      int(const char *key, char **val));
  MOCK_CONST_METHOD3(getset,
      int(const char *key, const char *set_val, char **get_val));
  MOCK_CONST_METHOD3(mget,
      int(int keyc, const char **keyv, char ***valv));
  MOCK_CONST_METHOD2(setnx,
      int(const char *key, const char *val));
  MOCK_CONST_METHOD2(incr,
      int(const char *key, int *new_val));
  MOCK_CONST_METHOD3(incrby,
      int(const char *key, int incr_val, int *new_val));
  MOCK_CONST_METHOD2(decr,
      int(const char *key, int *new_val));
  MOCK_CONST_METHOD3(decrby,
      int(const char *key, int decr_val, int *new_val));
  MOCK_CONST_METHOD2(append,
      int(const char *key, const char *val));
  MOCK_CONST_METHOD4(substr,
      int(const char *key, int start, int end, char **substr));
  MOCK_CONST_METHOD2(rpush,
      int(const char *key, const char *element));
  MOCK_CONST_METHOD2(lpush,
      int(const char *key, const char *element));
  MOCK_CONST_METHOD1(llen,
      int(const char *key));
  MOCK_CONST_METHOD4(lrange,
      int(const char *key, int start, int range, char ***elementv));
  MOCK_CONST_METHOD3(ltrim,
      int(const char *key, int start, int end));
  MOCK_CONST_METHOD3(lindex,
      int(const char *key, int index, char **element));
  MOCK_CONST_METHOD3(lset,
      int(const char *key, int index, const char *element));
  MOCK_CONST_METHOD3(lrem,
      int(const char *key, int count, const char *element));
  MOCK_CONST_METHOD2(lpop,
      int(const char *key, char **val));
  MOCK_CONST_METHOD2(rpop,
      int(const char *key, char **val));
  MOCK_CONST_METHOD2(sadd,
      int(const char *key, const char *member));
  MOCK_CONST_METHOD2(srem,
      int(const char *key, const char *member));
  MOCK_CONST_METHOD2(spop,
      int(const char *key, char **member));
  MOCK_CONST_METHOD3(smove,
      int(const char *sourcekey, const char *destkey, const char *member));
  MOCK_CONST_METHOD1(scard,
      int(const char *key));
  MOCK_CONST_METHOD2(sismember,
      int(const char *key, const char *member));
  MOCK_CONST_METHOD3(sinter,
      int(int keyc, const char **keyv, char ***members));
  MOCK_CONST_METHOD3(sinterstore,
      int(const char *destkey, int keyc, const char **keyv));
  MOCK_CONST_METHOD3(sunion,
      int(int keyc, const char **keyv, char ***members));
  MOCK_CONST_METHOD3(sunionstore,
      int(const char *destkey, int keyc, const char **keyv));
  MOCK_CONST_METHOD3(sdiff,
      int(int keyc, const char **keyv, char ***members));
  MOCK_CONST_METHOD3(sdiffstore,
      int(const char *destkey, int keyc, const char **keyv));
  MOCK_CONST_METHOD2(smembers,
      int(const char *key, char ***members));
  MOCK_CONST_METHOD3(zadd,
      int(const char *key, double score, const char *member));
  MOCK_CONST_METHOD2(zrem,
      int(const char *key, const char *member));
  MOCK_CONST_METHOD4(zincrby,
      int(const char *key, double incr_score, const char *member, double *new_score));
  MOCK_CONST_METHOD2(zrank,
      int(const char *key, const char *member));
  MOCK_CONST_METHOD2(zrevrank,
      int(const char *key, const char *member));
  MOCK_CONST_METHOD4(zrange,
      int(const char *key, int start, int end, char ***elementv));
  MOCK_CONST_METHOD4(zrevrange,
      int(const char *key, int start, int end, char ***elementv));
  MOCK_CONST_METHOD1(zcard,
      int(const char *key));
  MOCK_CONST_METHOD3(zscore,
      int(const char *key, const char *member, double *score));
  MOCK_CONST_METHOD3(zremrangebyscore,
      int(const char *key, double min, double max));
  MOCK_CONST_METHOD3(zremrangebyrank,
      int(const char *key, int start, int end));
  MOCK_CONST_METHOD2(sort,
      int(const char *query, char ***elementv));
  MOCK_CONST_METHOD1(subscribe,
      int(const char *channel));
  MOCK_CONST_METHOD1(unsubscribe,
      int(const char *channel));
  MOCK_CONST_METHOD1(psubscribe,
      int(const char *pattern));
  MOCK_CONST_METHOD1(punsubscribe,
      int(const char *pattern));
  MOCK_CONST_METHOD2(publish,
      int(const char *channel, const char *message));
  MOCK_CONST_METHOD3(listen,
      int(char **pattern, char **channel, char **message));
  MOCK_CONST_METHOD0(save,
      int());
  MOCK_CONST_METHOD0(bgsave,
      int());
  MOCK_CONST_METHOD0(lastsave,
      int());
  MOCK_CONST_METHOD0(shutdown,
      int());
  MOCK_CONST_METHOD0(bgrewriteaof,
      int());
  MOCK_CONST_METHOD0(monitor,
      int());
  MOCK_CONST_METHOD2(slaveof,
      int(const char *host, int port));
};

}  //namespace test
}  // namespace rrns_db
