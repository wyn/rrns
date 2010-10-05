#include "RedisConsumer.h"
#include "credis.h"
#include "gtest/gtest.h"
#include <stdio.h>

namespace {

// The fixture for testing class RedisConsumer.
class RedisConsumerTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  RedisConsumerTest() {
    // You can do set-up work for each test here.
  }

  virtual ~RedisConsumerTest() {
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
};

TEST_F(RedisConsumerTest, Playing_GrabListRange) {

    REDIS rh = credis_connect("localhost", 6379, 2000);
    credis_flushdb(rh);

    for (int i(0); i != 10; i++)
    {
        double d = i*1.0000001;
        char c[22];
        sprintf(c, "%20.10e", d);
        credis_rpush(rh, "test1", c);
    }

    for (int i(0); i != 10; i++)
    {
        char *c;
        credis_lpop(rh, "test1", &c);
        double d(strtod(c, NULL));
        std::cout << "Popping back out: " << d*1.0e10 << std::endl;
    }

    credis_close(rh);

}

}  // namespace
