#include "MockICredisConsumer.h"
#include "RedisManager.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AtMost;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Gt;

using ::rrns_db::MockICredisConsumer;
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

    MockICredisConsumer mock;

    EXPECT_CALL(mock, Init())
            .Times(1);

    EXPECT_CALL(mock, GetHandle(_,_,_))
            .Times(0);

    RedisManager rm(&mock);

}

TEST_F(RedisManagerTest, CanConnect) {

    MockICredisConsumer mock;

    //make sure the db handle is not null
    REDIS r;
    ON_CALL(mock, GetHandle(host, port, timeout))
            .WillByDefault(Return(r));

    EXPECT_CALL(mock, GetHandle(host, port, timeout))
            .Times(1);

    RedisManager rm(&mock);
    rm.Connect(host, port, timeout);

}

TEST_F(RedisManagerTest, CanDisconnect) {

    MockICredisConsumer mock;

    EXPECT_CALL(mock, Close(_))
            .Times(1);

    RedisManager rm(&mock);
    rm.Disconnect();
}

TEST_F(RedisManagerTest, CanRegister) {

    MockICredisConsumer mock;

    ON_CALL(mock, IsValidHandle(_))
            .WillByDefault(Return(true));

    ON_CALL(mock, StreamExists(_, major, minor))
            .WillByDefault(Return(true));

    ON_CALL(mock, GetStreamId(_, major, minor))
            .WillByDefault(Return(1));

    EXPECT_CALL(mock, IsValidHandle(_))
      .Times(AtLeast(1));

    EXPECT_CALL(mock, StreamExists(_, major, minor))
      .Times(AtLeast(1));

    EXPECT_CALL(mock, GetStreamId(_, major, minor))
      .Times(AtLeast(1));

    RedisManager rm(&mock);
    rm.Register(major, minor);
    ASSERT_EQ(major, rm.MajorType());
    ASSERT_EQ(minor, rm.MinorType());
    ASSERT_LT(0, rm.Id());

}

TEST_F(RedisManagerTest, CanUnregister) {

    MockICredisConsumer mock;

    EXPECT_CALL(mock, Init())
      .Times(1);

    RedisManager rm(&mock);
    rm.Disconnect();

}

} //namespace
