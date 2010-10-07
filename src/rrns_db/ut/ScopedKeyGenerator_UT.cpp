#include "ScopedTemporaryKey.h"
#include "MockICredis.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;

using ::rrns_db::ScopedTemporaryKey;
using ::rrns_db::test::MockICredis;

namespace {

// The fixture for testing class ScopedTemporaryKeyTest.
class ScopedTemporaryKeyTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  ScopedTemporaryKeyTest()
      :key("key1")
  {
    // You can do set-up work for each test here.
  }

  virtual ~ScopedTemporaryKeyTest() {
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
  const std::string key;
};

TEST_F(ScopedTemporaryKeyTest, TestCanConstructDestruct) {

    MockICredis cred;
    EXPECT_CALL(cred, sadd(key.c_str(), NULL))
            .WillOnce(Return(0));

    //when it goes out of scope it will delete the key
    EXPECT_CALL(cred, del(key.c_str()))
            .WillOnce(Return(0));

    ScopedTemporaryKey k(key.c_str(), &cred);
}

TEST_F(ScopedTemporaryKeyTest, TestKey) {

    MockICredis cred;
    ON_CALL(cred, sadd(key.c_str(), NULL))
            .WillByDefault(Return(0));

    ON_CALL(cred, del(key.c_str()))
            .WillByDefault(Return(0));

    ScopedTemporaryKey k(key.c_str(), &cred);
    ASSERT_EQ(key.c_str(), k.Key());
}

TEST_F(ScopedTemporaryKeyTest, TestExists) {

    MockICredis cred;
    ON_CALL(cred, sadd(key.c_str(), NULL))
            .WillByDefault(Return(0));

    ON_CALL(cred, del(key.c_str()))
            .WillByDefault(Return(0));

    EXPECT_CALL(cred, exists(key.c_str()))
            .WillOnce(Return(true));

    ScopedTemporaryKey k(key.c_str(), &cred);
    ASSERT_TRUE(k.Exists());
}

}
