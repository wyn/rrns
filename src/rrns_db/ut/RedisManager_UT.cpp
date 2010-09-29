#include "MockICredisConsumer.h"
#include "MockICredisConnector.h"
#include "RedisManager.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AtMost;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Gt;
using ::testing::InSequence;

using ::rrns_db::test::MockICredisConsumer;
using ::rrns_db::test::MockICredisConnector;
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

TEST_F(RedisManagerTest, CanConstruct) {

    MockICredisConsumer cons;
    MockICredisConnector conn;

    EXPECT_CALL(cons, Reset())
            .Times(1);

    RedisManager rm(&cons, &conn);

}

TEST_F(RedisManagerTest, CanConnect) {

    MockICredisConsumer cons;
    MockICredisConnector conn;

    ON_CALL(conn, IsValidHandle())
            .WillByDefault(Return(true));

    InSequence s;

    EXPECT_CALL(conn, Connect(host, port, timeout))
            .Times(1);

    EXPECT_CALL(cons, RegisterConnection(&conn))
            .Times(1);

    RedisManager rm(&cons, &conn);
    rm.Connect(host, port, timeout);

}

TEST_F(RedisManagerTest, CanDisconnect) {

    MockICredisConsumer cons;
    MockICredisConnector conn;

    EXPECT_CALL(cons, Reset())
            .Times(AtLeast(1));

    EXPECT_CALL(conn, Disconnect())
            .Times(1);

    RedisManager rm(&cons, &conn);
    rm.Disconnect();
}

TEST_F(RedisManagerTest, CanRegister) {

    MockICredisConsumer cons;
    MockICredisConnector conn;

    ON_CALL(conn, IsValidHandle())
            .WillByDefault(Return(true));

    ON_CALL(cons, StreamExists(major, minor))
            .WillByDefault(Return(true));

    ON_CALL(cons, CanConsume())
            .WillByDefault(Return(true));

    InSequence s;

    EXPECT_CALL(cons, StreamExists(major, minor))
      .Times(1);

    EXPECT_CALL(cons, RegisterStream(major, minor))
      .Times(1);

    RedisManager rm(&cons, &conn);
    rm.Register(major, minor);

}

TEST_F(RedisManagerTest, CanUnregister) {

    MockICredisConsumer cons;
    MockICredisConnector conn;

    EXPECT_CALL(cons, Reset())
            .Times(AtLeast(1));

    //dont disconnect though
    EXPECT_CALL(conn, Disconnect())
            .Times(0);

    RedisManager rm(&cons, &conn);
    rm.Unregister();

}

TEST_F(RedisManagerTest, TestMajorType) {

    MockICredisConsumer cons;
    MockICredisConnector conn;

    EXPECT_CALL(cons, MajorType())
            .Times(1);

    RedisManager rm(&cons, &conn);
    rm.MajorType();

}

TEST_F(RedisManagerTest, TestMinorType) {

    MockICredisConsumer cons;
    MockICredisConnector conn;

    EXPECT_CALL(cons, MinorType())
            .Times(1);

    RedisManager rm(&cons, &conn);
    rm.MinorType();

}

TEST_F(RedisManagerTest, TestCanConsume) {

    MockICredisConsumer cons;
    MockICredisConnector conn;

    EXPECT_CALL(cons, CanConsume())
            .Times(1);

    RedisManager rm(&cons, &conn);
    rm.CanConsume();

}

TEST_F(RedisManagerTest, TestValidHandle) {

    MockICredisConsumer cons;
    MockICredisConnector conn;

    EXPECT_CALL(conn, IsValidHandle())
            .Times(1);

    RedisManager rm(&cons, &conn);
    rm.ValidHandle();

}

TEST_F(RedisManagerTest, TestGetRandoms) {

    MockICredisConsumer cons;
    MockICredisConnector conn;

    std::list<double> rs;

    ON_CALL(cons, GetRandoms(_))
            .WillByDefault(Return(rs));

    ON_CALL(cons, CanConsume())
            .WillByDefault(Return(true));

    InSequence s;

    EXPECT_CALL(cons, CanConsume())
            .Times(1);

    EXPECT_CALL(cons, GetRandoms(_))
            .Times(1);

    RedisManager rm(&cons, &conn);
    rm.GetRandoms(10);

}

} //namespace
