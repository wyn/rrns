#include "MockICredis.h"
#include "MockIRedisConsumer.h"
#include "MockIRedisConnector.h"
#include "MockIKey.h"
#include "MockIKeyParser.h"
#include "MockIKeyGenerator.h"
#include "RedisManager.h"
#include "Key.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::SetArgReferee;
using ::testing::NotNull;
using ::testing::DoAll;

using ::rrns_db::test::MockICredis;
using ::rrns_db::test::MockIRedisConsumer;
using ::rrns_db::test::MockIRedisConnector;
using ::rrns_db::test::MockIKey;
using ::rrns_db::test::MockIKeyParser;
using ::rrns_db::test::MockIKeyGenerator;

using ::rrns_db::IKey;
using ::rrns_db::Key;
using ::rrns_db::RedisManager;

namespace {

// The fixture for testing class RedisManager.
class RedisManagerTest : public ::testing::Test {

 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  RedisManagerTest()
      : host("localhost")
      , port(6379)
      , timeout(2000)
      , major("test_major")
      , minor("test_minor") {

      // You can do set-up work for each test here.

  }

  virtual ~RedisManagerTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
  const std::string host;
  const int port;
  const int timeout;

  const std::string major;
  const std::string minor;

};

TEST_F(RedisManagerTest, CanConnect) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    EXPECT_CALL(conn, Connect(host, port, timeout))
            .Times(1);

    EXPECT_CALL(cred, SetConnector(&conn))
            .Times(1);

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.Connect(host, port, timeout);

}

TEST_F(RedisManagerTest, CanDisconnect) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    EXPECT_CALL(conn, Disconnect())
            .Times(1);

    EXPECT_CALL(cred, ClearConnector())
            .Times(1);

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.Disconnect();
}

//templates seem to go crazy and not compile with things like SetArgumentPointee
//so using ACTION* macro
ACTION_P(SetArg1, c){
    *arg1 = c;
};

TEST_F(RedisManagerTest, CanRegister) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    ON_CALL(conn, IsValidHandle())
            .WillByDefault(Return(true));

    EXPECT_CALL(conn, IsValidHandle())
            .Times(AtLeast(1));

    //need to make the id data key
    //assumes that you give minor and major id keys
    //use these to get the intersection of the 2 sets
    //then pull out a random entry of the intersection

    //adds an empty set to start
    EXPECT_CALL(cred, sadd(NotNull(), NULL))
            .WillOnce(Return(0));

    EXPECT_CALL(cred, exists(_))
            .WillOnce(Return(true));

    //expect the intersection of two sets
    EXPECT_CALL(cred, sinterstore(_, 2, _))
            .WillOnce(Return(4));

    char c[2] = { '1', '2' };
    EXPECT_CALL(cred, spop(NotNull(), NotNull()))
            .WillOnce(DoAll(
                    SetArg1<char*>(c),
                    Return(0)));

    boost::shared_ptr<IKey> key(new Key("Ids","12","Data"));
    EXPECT_CALL(gen, ScalarKey(_))
            .WillOnce(Return(key));

    EXPECT_CALL(p, Serialise(_, _))
            .WillOnce(DoAll(
                    SetArgReferee<1>("Ids:12:Data"),
                    Return(true)));

    //should auto delete when coming out of scope
    EXPECT_CALL(cred, del(_))
            .WillOnce(Return(0));

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.Register(major, minor);

}

TEST_F(RedisManagerTest, CanNotRegister_InvalidHandle) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    //is invalid handle so just quits after checking
    EXPECT_CALL(conn, IsValidHandle())
            .WillOnce(Return(false));

    EXPECT_CALL(cred, sadd(NotNull(), NULL))
            .Times(0);

    EXPECT_CALL(cred, exists(_))
            .Times(0);

    EXPECT_CALL(cred, sinterstore(_, _, _))
            .Times(0);

    EXPECT_CALL(cred, spop(_, _))
            .Times(0);

    EXPECT_CALL(gen, ScalarKey(_))
            .Times(0);

    EXPECT_CALL(p, Serialise(_, _))
            .Times(0);

    EXPECT_CALL(cred, del(_))
            .Times(0);

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.Register(major, minor);

}

TEST_F(RedisManagerTest, CanNotRegister_CannotAddTmpKey) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    ON_CALL(conn, IsValidHandle())
            .WillByDefault(Return(true));

    EXPECT_CALL(conn, IsValidHandle())
            .Times(AtLeast(1));

    //cannot add the intersection key so just quits after checking
    EXPECT_CALL(cred, sadd(NotNull(), NULL))
            .Times(1);
    EXPECT_CALL(cred, exists(_))
            .WillOnce(Return(false));

    EXPECT_CALL(cred, sinterstore(_, _, _))
            .Times(0);

    EXPECT_CALL(cred, spop(_, _))
            .Times(0);

    EXPECT_CALL(gen, ScalarKey(_))
            .Times(0);

    EXPECT_CALL(p, Serialise(_, _))
            .Times(0);

    //should still try to delete
    EXPECT_CALL(cred, del(_))
            .Times(1);

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.Register(major, minor);

}

TEST_F(RedisManagerTest, CanNotRegister_CannotIntersectSets) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    ON_CALL(conn, IsValidHandle())
            .WillByDefault(Return(true));

    EXPECT_CALL(conn, IsValidHandle())
            .Times(AtLeast(1));

    EXPECT_CALL(cred, sadd(NotNull(), NULL))
            .WillOnce(Return(0));

    EXPECT_CALL(cred, exists(_))
            .WillOnce(Return(true));

    //cannot intersect keys so just quits after checking
    EXPECT_CALL(cred, sinterstore(_, _, _))
            .WillOnce(Return(-1));

    EXPECT_CALL(cred, spop(_, _))
            .Times(0);

    EXPECT_CALL(gen, ScalarKey(_))
            .Times(0);

    EXPECT_CALL(p, Serialise(_, _))
            .Times(0);

    //should still get deleted
    EXPECT_CALL(cred, del(_))
            .Times(1);

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.Register(major, minor);

}

TEST_F(RedisManagerTest, CanNotRegister_CannotPopFromTempSet) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    ON_CALL(conn, IsValidHandle())
            .WillByDefault(Return(true));

    EXPECT_CALL(conn, IsValidHandle())
            .Times(AtLeast(1));

    EXPECT_CALL(cred, sadd(NotNull(), NULL))
            .WillOnce(Return(0));

    EXPECT_CALL(cred, exists(_))
            .WillOnce(Return(true));

    EXPECT_CALL(cred, sinterstore(_, _, _))
            .WillOnce(Return(4));

    EXPECT_CALL(cred, spop(_, _))
            .WillOnce(Return(-1));

    EXPECT_CALL(gen, ScalarKey(_))
            .Times(0);

    EXPECT_CALL(p, Serialise(_, _))
            .Times(0);

    //should still get deleted
    EXPECT_CALL(cred, del(_))
            .Times(1);

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.Register(major, minor);

}

TEST_F(RedisManagerTest, CanNotRegister_CannotCreateIdKey) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    ON_CALL(conn, IsValidHandle())
            .WillByDefault(Return(true));

    EXPECT_CALL(conn, IsValidHandle())
            .Times(AtLeast(1));

    EXPECT_CALL(cred, sadd(NotNull(), NULL))
            .WillOnce(Return(0));

    EXPECT_CALL(cred, exists(_))
            .WillOnce(Return(true));

    EXPECT_CALL(cred, sinterstore(_, _, _))
            .WillOnce(Return(4));

    char c[2] = { '1', '2' };
    EXPECT_CALL(cred, spop(NotNull(), NotNull()))
            .WillOnce(DoAll(
                    SetArg1<char*>(c),
                    Return(0)));

    boost::shared_ptr<IKey> key;
    EXPECT_CALL(gen, ScalarKey(_))
            .WillOnce(Return(key));

    EXPECT_CALL(p, Serialise(_, _))
            .Times(0);

    //should still get deleted
    EXPECT_CALL(cred, del(_))
            .Times(1);

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.Register(major, minor);

}

TEST_F(RedisManagerTest, CanNotRegister_CannotSerialiseNewIdKey) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    ON_CALL(conn, IsValidHandle())
            .WillByDefault(Return(true));

    EXPECT_CALL(conn, IsValidHandle())
            .Times(AtLeast(1));

    EXPECT_CALL(cred, sadd(NotNull(), NULL))
            .WillOnce(Return(0));

    EXPECT_CALL(cred, exists(_))
            .WillOnce(Return(true));

    EXPECT_CALL(cred, sinterstore(_, _, _))
            .WillOnce(Return(4));

    char c[2] = { '1', '2' };
    EXPECT_CALL(cred, spop(NotNull(), NotNull()))
            .WillOnce(DoAll(
                    SetArg1<char*>(c),
                    Return(0)));

    boost::shared_ptr<IKey> key(new Key("","",""));
    EXPECT_CALL(gen, ScalarKey(_))
            .WillOnce(Return(key));

    EXPECT_CALL(p, Serialise(_, _))
            .WillOnce(Return(false));

    //should still get deleted
    EXPECT_CALL(cred, del(_))
            .Times(1);

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.Register(major, minor);

}

TEST_F(RedisManagerTest, CanUnregister) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    //don't disconnect
    EXPECT_CALL(conn, Disconnect())
            .Times(0);

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.Unregister();

}

TEST_F(RedisManagerTest, TestCanConsume) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    EXPECT_CALL(cons, CanConsume(&cred, _))
            .Times(1);

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.CanConsume();

}

TEST_F(RedisManagerTest, TestGetRandoms) {

    MockICredis cred;
    MockIRedisConsumer cons;
    MockIRedisConnector conn;
    MockIKeyParser p;
    MockIKeyGenerator gen;

    std::vector<double> rs;
    const int howMany = 10;

    EXPECT_CALL(cons, GetRandoms(&cred, _, howMany))
            .WillOnce(Return(rs));

    RedisManager rm(&cred, &conn, &cons, &p, &gen);
    rm.GetRandoms(howMany);

}

} //namespace
