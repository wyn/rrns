#include "RedisConsumer.h"
#include "gtest/gtest.h"
#include <QtCore>

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

//TEST_F(RedisConsumerTest, CanConstruct) {

//    //default constructor should connect to the local host on port 6379 with 2 sec timeout
//    ::rrns_db::RedisConsumer rdb;
//    ASSERT_TRUE(rdb.ValidHandle()) << "Newly created RedisConsumer should have a valid handle";
//    ASSERT_FALSE(rdb.CanConsume()) << "Newly created RedisConsumer needs to be registered before consuming data";
//}

//TEST_F(RedisConsumerTest, CanConstructOverload) {

//    //overload constructor can also connect to the local host on port 6379 with 2 sec timeout
//    ::rrns_db::RedisConsumer rdb("localhost", 6379, 2000);
//    ASSERT_TRUE(rdb.ValidHandle()) << "Newly created RedisConsumer should have a valid handle";
//    ASSERT_FALSE(rdb.CanConsume()) << "Newly created RedisConsumer needs to be registered before consuming data";
//}

//TEST_F(RedisConsumerTest, CanConstructWithWrongPort) {

//    //checking it doesn't all fall over with a bad handle
//    int port = 1000;
//    ::rrns_db::RedisConsumer rdb("localhost", port, 2000);

//    ASSERT_FALSE(rdb.Register("majorType", "minorType")) << "Should not be able to register with bad construct";
//    ASSERT_FALSE(rdb.Unregister()) << "Should not be able to unregister with bad construct";
//    ASSERT_FALSE(rdb.ValidHandle()) << "Should not have a valid handle for port " << port;
//    ASSERT_EQ(rdb.MajorType().toStdString(), "") << "Incorrect major type after bad construct";
//    ASSERT_EQ(rdb.MinorType().toStdString(), "") << "Incorrect minor type after bad construct";
//    ASSERT_EQ(rdb.Seed(), 0) << "Invalid random seed after bad construct";
//    ASSERT_EQ(rdb.Id(), 0) << "Invalid ID after bad construct";
//    ASSERT_FALSE(rdb.CanConsume()) << "Should not be able to consume after bad construct";
//}

//TEST_F(RedisConsumerTest, CanRegister) {

//    //Registering needs the major and minor types (ie pseudo random normals),
//    //failure to connect will return false, else true and the ID, seed and data is then available to use/consume
//    //failure could be: unsupported major, minor types, fatal db error

//    ::rrns_db::RedisConsumer rdb;
//    QString majorType("pseudo");
//    QString minorType("normal");

//    ASSERT_TRUE(rdb.Register(majorType, minorType)) << "Failed to register";
//    ASSERT_EQ(rdb.MajorType().toStdString(), majorType.toStdString()) << "Incorrect major type";
//    ASSERT_EQ(rdb.MinorType().toStdString(), minorType.toStdString()) << "Incorrect minor type";
//    ASSERT_GT(rdb.Seed(), 0) << "Invalid random seed after successful registration";
//    ASSERT_GT(rdb.Id(), 0) << "Invalid ID after successful registration";
//    ASSERT_TRUE(rdb.CanConsume()) << "Cannot consume after successful registration";
//}

//TEST_F(RedisConsumerTest, CanUnregister) {

//    //When no longer want to consume data you unregister

//    ::rrns_db::RedisConsumer rdb;
//    rdb.Register("pseudo", "normal");

//    ASSERT_TRUE(rdb.Unregister()) << "Failed to unregister";
//    ASSERT_EQ(rdb.MajorType().toStdString(), "") << "Incorrect major type after unregister";
//    ASSERT_EQ(rdb.MinorType().toStdString(), "") << "Incorrect minor type after unregister";
//    ASSERT_EQ(rdb.Seed(), 0) << "Invalid random seed after unregister";
//    ASSERT_EQ(rdb.Id(), 0) << "Invalid ID after unregister";
//    ASSERT_FALSE(rdb.CanConsume()) << "Should not be able to consume after successful unregistration";
//}

}  // namespace
