#include "Consumer.h"
#include "MockICredis.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::Return;
using ::testing::NotNull;
using ::testing::DoAll;
using ::testing::AtLeast;

using ::rrns_db::test::MockICredis;
using ::rrns_db::Consumer;

namespace {

// The fixture for testing class Consumer.
class ConsumerTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  ConsumerTest()
      : key("key")
  {
    // You can do set-up work for each test here.
  }

  virtual ~ConsumerTest() {
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

TEST_F(ConsumerTest, TestCanConsume) {

    MockICredis mock;

    EXPECT_CALL(mock, exists(key.c_str()))
            .WillOnce(Return(0));

    Consumer r;
    ASSERT_TRUE(r.CanConsume(&mock, key));
}

TEST_F(ConsumerTest, TestCannotConsume) {

    MockICredis mock;

    EXPECT_CALL(mock, exists(key.c_str()))
            .WillOnce(Return(-1));

    Consumer r;
    ASSERT_FALSE(r.CanConsume(&mock, key));
}

TEST_F(ConsumerTest, TestCount) {

    MockICredis mock;

    EXPECT_CALL(mock, llen(key.c_str()))
            .Times(1);

    Consumer r;
    r.Count(&mock, key);
}

//templates seem to go crazy and not compile with things like SetArgumentPointee
//so using ACTION* macro
ACTION_P(SetArg1, c){
    *arg1 = c;
};

TEST_F(ConsumerTest, TestGetData) {

    MockICredis mock;
    size_t howMany = 10;

    char c[2] = { '1', '2' };
    ON_CALL(mock, lpop(key.c_str(), NotNull()))
            .WillByDefault(DoAll(
                    SetArg1<char*>(c),
                    Return(0)));

    EXPECT_CALL(mock, lpop(key.c_str(), NotNull()))
            .Times(howMany);

    Consumer r;
    std::vector<double> l(r.GetData(&mock, key, howMany));

    ASSERT_EQ(howMany, l.size());
    for (size_t i(0); i!=l.size(); ++i)
    {
        ASSERT_EQ(12.0, l[i]);
    }

}

TEST_F(ConsumerTest, TestGetData_LotsMoreThanDefaultMax) {

    MockICredis mock;
    size_t howMany = 200; //needs to be bigger than Consumer.cpp::default_max = 100

    char c[2] = { '1', '2' };
    ON_CALL(mock, lpop(key.c_str(), NotNull()))
            .WillByDefault(DoAll(
                    SetArg1<char*>(c),
                    Return(0)));

    EXPECT_CALL(mock, lpop(key.c_str(), NotNull()))
            .Times(howMany);

    Consumer r;
    std::vector<double> l(r.GetData(&mock, key, howMany));

    ASSERT_EQ(howMany, l.size());
    for (size_t i(0); i!=l.size(); ++i)
    {
        ASSERT_EQ(12.0, l[i]);
    }

}

TEST_F(ConsumerTest, TestGetData_CannotPop) {

    MockICredis mock;

    char c[2] = { '1', '2' };
    ON_CALL(mock, lpop(key.c_str(), NotNull()))
            .WillByDefault(DoAll(
                    SetArg1<char*>(c),
                    Return(-1)));

    EXPECT_CALL(mock, lpop(key.c_str(), NotNull()))
            .Times(AtLeast(1));

    Consumer r;
    std::vector<double> l(r.GetData(&mock, key, 10));

    ASSERT_TRUE(l.empty());
}

}  // namespace
