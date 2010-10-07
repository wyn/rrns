#include "KeyParser.h"
#include "MockIKey.h"
#include "Key.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;

using ::rrns_db::KeyParser;
using ::rrns_db::IKey;
using ::rrns_db::Key;
using ::rrns_db::test::MockIKey;

namespace {

// The fixture for testing class KeyParserTest.
class KeyParserTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  KeyParserTest()
  {
    // You can do set-up work for each test here.
  }

  virtual ~KeyParserTest() {
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

TEST_F(KeyParserTest, TestCanSerialise) {

    MockIKey key;
    EXPECT_CALL(key, Family())
            .WillOnce(Return("Family"));

    EXPECT_CALL(key, Member())
            .WillOnce(Return("Member"));

    EXPECT_CALL(key, Entity())
            .WillOnce(Return("Entity"));

    KeyParser kp;
    std::string s;

    ASSERT_TRUE(kp.Serialise(&key, s));
    ASSERT_EQ("Family:Member:Entity", s);

}

TEST_F(KeyParserTest, TestCannotSerialise_NullInput) {

    IKey *key = NULL;
    ASSERT_FALSE(key);
    KeyParser kp;
    std::string s("virginial");

    ASSERT_FALSE(kp.Serialise(key, s));
    ASSERT_EQ("virginial", s);

}

TEST_F(KeyParserTest, TestCanDeserialise) {

    KeyParser kp;
    std::string s("Family:Member:Entity");
    IKey *key = new Key("", "", "");

    ASSERT_TRUE(kp.Deserialise(s, key));
    ASSERT_EQ("Family", key->Family());
    ASSERT_EQ("Member", key->Member());
    ASSERT_EQ("Entity", key->Entity());

}

TEST_F(KeyParserTest, TestCannotDeserialise_NullOutput) {

    KeyParser kp;
    std::string s("Family:Member:Entity");
    IKey *key = NULL;

    ASSERT_FALSE(kp.Deserialise(s, key));

}

TEST_F(KeyParserTest, TestCannotDeserialise_ShortString) {

    KeyParser kp;
    std::string s("Family:Member");
    IKey *key = new Key("", "", "");

    ASSERT_FALSE(kp.Deserialise(s, key));
    ASSERT_EQ("", key->Family());
    ASSERT_EQ("", key->Member());
    ASSERT_EQ("", key->Entity());

}

TEST_F(KeyParserTest, TestCannotDeserialise_LongString) {

    KeyParser kp;
    std::string s("Family:Member:Entity:SomethingElse");
    IKey *key = new Key("", "", "");

    ASSERT_FALSE(kp.Deserialise(s, key));
    ASSERT_EQ("", key->Family());
    ASSERT_EQ("", key->Member());
    ASSERT_EQ("", key->Entity());

}

}
